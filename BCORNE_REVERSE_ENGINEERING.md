# Reverse-engineering the bcorne keyboard

This is the story of taking a keyboard that arrived as a sealed box of someone
else's firmware and turning it into something we fully control. That meant recovering
how the hardware is wired without a schematic, and then building a flashing procedure
that works around a bootloader that fights back.

You don't need any embedded or firmware background to follow it. Where a hardware
concept matters, it gets a sentence of explanation. The two halves of the story are
independent detective problems, so they're told separately. First, understanding the
board. Then, programming it.

## The board

The SZRKBD BCORNE is a split ergonomic keyboard. Two separate halves connected by a
cable, 60 keys total, a rotary knob on each side, and an RGB LED under every key. It
runs on an STM32F401 microcontroller with 256 KB of storage.

It shipped with working firmware, a build of Vial (a popular keyboard firmware), but
no source code, no schematic, and no documentation of how anything is wired. The goal
was to replace that firmware with QMK, the open-source keyboard firmware most of the
other boards here run, so the bcorne could share the same keymap conventions and
features.

That turned out to require answering two separate questions the hard way.

1. How is this board actually built? QMK needs to know which physical pins scan the
   keys, which crystal sets the clock, how the two halves talk, and a dozen other
   details. None of it was written down anywhere.
2. How do you get new firmware onto it? The board's method for accepting new firmware
   is subtly non-standard, and on Linux it fails most of the time for a reason that
   has nothing to do with the firmware itself.

## Part 1: reading the hardware out of a binary

The only authoritative description of how the board was wired was the firmware
already running on it. So the starting point was a full 256 KB dump of the chip's
storage, every byte of the stock firmware, pulled off the board and saved as
`stock_bcorne.bin`. The chip maps that storage starting at address `0x08000000`. The
bootloader sits at the very beginning, and the keyboard firmware proper begins 64 KB
in, at `0x08010000`. Knowing that split matters, because every fact recovered later is
quoted as an absolute address in that map, and you have to know where the real firmware
starts to make sense of them.

A raw firmware dump is just machine code, the literal instructions the processor
runs, with no variable names, comments, or structure. To read it, you disassemble it,
translating the machine code back into human-readable processor instructions with a
tool called capstone. Then you read those instructions the way you'd read an
unfamiliar codebase with every helpful name stripped out, hunting for the handful of
spots where the firmware pokes at the hardware: writing to the chip's control
registers, setting up the clock, driving pins high and low.

The discipline that made this reliable was tracing every fact back to a specific
address in the binary rather than guessing. If the notes claim the left knob uses a
particular pin, there's a line of disassembled code at a named address that proves
it. This matters more than it sounds. A plausible guess about a pin will happily
compile into firmware that then does nothing, and you're left unable to tell a wrong
guess from some other bug. Tying each claim to an instruction at an address turns
"I think it's this pin" into "the code at this address configures this pin," which is
checkable. Anything that couldn't be pinned to the binary got verified a different
way, by probing the actual board with a meter, or by building the firmware and watching
what the hardware actually did.

Here's what had to be recovered, and why each one mattered.

### The board looks dead: the wrong crystal

The first attempt at a QMK build did nothing. Plugged in, the board was electrically
alive but the computer never saw it. No keyboard, no error, just silence, exactly as
if it were broken.

The cause was the clock. A microcontroller runs off a clock signal, and everything it
does is timed against that clock. This chip gets its clock from a quartz crystal
soldered to the board, and the firmware multiplies that crystal's frequency up to the
speed the chip runs at. USB is unforgiving here. To talk to a computer at all, the
chip has to produce a clock of exactly 48 MHz. Miss it and USB never starts.

QMK's generic settings for this family of chip assume a crystal of 8 or 25 MHz. The
bcorne uses a 16 MHz crystal. With the wrong assumed frequency, the firmware computes
the wrong multiplier, the clock comes out wrong, USB never initializes, and the board
looks dead. Nothing about the failure points at the clock. A dead-looking board is
what almost any early mistake produces, which is what made this one worth pinning down
precisely rather than guessing at.

The fix came straight from the stock firmware's own clock setup, read out of the
binary. A 16 MHz crystal put through a specific chain of multiply-and-divide factors,
multiplied up by 192 and then divided back down by 4, lands on exactly 48 MHz. Copying
those exact factors, the ones the working stock firmware used, into the QMK build
brought the board to life.

### Scrambled key wiring

A keyboard doesn't have one wire per key. That would need hundreds of pins. Instead
the keys are wired as a grid of rows and columns, and the firmware works out which key
is pressed by energizing one row at a time and checking which columns respond. Each
half of the bcorne is a grid of 5 rows and 7 columns, and QMK needs the exact list of
which chip pins are the rows and which are the columns, for both halves.

Reading these out of the stock firmware produced a working list for the right half
but a scrambled one for the left. The reason was a quirk of how the stock firmware
stored the two lists internally. The two halves keep their pin lists in the same
packed format, but not in the same order. The left half's grid is stored
columns-first, the 7 column pins and then the 5 row pins, while the right half's is
stored rows-first. A single extraction routine that assumed one order therefore read
the left half's rows as columns and its columns as rows, and produced a pin map that
looked reasonable but was wrong.

Nothing in the binary announces which order it used, so the tell was that the right
half worked and the left didn't. Once the different ordering was understood, the left
half's rows and columns were untangled, and then the corrected map was confirmed key
by key on the physical board, pressing each key and checking it registered where the
map said it should. That electrical check is what turned a theory about byte ordering
into a map we could trust.

### Which half is which

On a split keyboard, both halves run identical firmware, so each half has to work out
at power-on whether it's the left or the right. Usually it reads a single pin that's
wired differently on the two sides.

The bcorne uses one pin for this, but with the opposite convention from QMK's default.
The relevant code configures that pin as an input, reads it, and treats a low reading
as "I'm the left half," where QMK assumes low means right. Read the convention
backwards and both halves decide they're the same side, and the split falls apart. The
check was read out of the stock firmware and then inverted in the QMK config, so each
half correctly identifies itself.

### How the halves talk

The two halves are joined by a cable, and only one half plugs into the computer. That
half is the master, and the other has to send its keypresses across the cable. The
disassembly showed the bcorne does this over a standard serial link (a common
two-wire scheme for sending data between chips), driven by one of the chip's built-in
serial peripherals on a specific pair of pins. Two details from the binary mattered.
The link is full-duplex, meaning both pins carry data, one each way, rather than
sharing a single wire. And the two data lines are crossed in the connecting cable, so
one half's transmit pin meets the other half's receive pin. All of that had to be
identified and configured before the second half's keys would register at all.

### The knobs

Each half has a rotary knob, and the knobs were their own small saga. An early guess
in the notes had them pegged as ordinary keys mapped to fake grid positions. The
disassembly proved that wrong. They're true rotary encoders, a knob that reports
rotation as a stream of electrical pulses on two pins, and the firmware counts the
pulses to know how far and which way it turned.

Each half wires its knob to a different pair of pins, and the code makes this explicit.
It loads one default pair, then, only when it has decided it's the right half,
overwrites them with a second pair. So both had to be read out separately. Two more
details only showed up on the real hardware. The firmware had to be told to count the
knob's pulses at twice QMK's default rate, or it would ignore every other click of
rotation. And the two pins of each knob had to be swapped from the order the stock
firmware suggested, or the knobs scrolled backwards.

### The lights

Every key has an addressable RGB LED under it, the kind wired in a single chain where
each LED passes data to the next. The disassembly showed the whole chain is driven
from one pin, and, less obviously, that the firmware doesn't wiggle that pin by hand.
It hands the job to a hardware timer feeding a DMA channel, a setup where the chip
clocks out the precisely-timed LED signal on its own while the processor does other
work. That detail dictated exactly how to configure the same path in QMK.

Recovering which LED is which took a second table out of the binary: a map from each
key's grid position to its place in the LED chain, plus the on-screen coordinates of
every LED, which is what lets lighting effects sweep across the board in the right
physical direction. The chain runs through the left half first and then the right, and
the two knob-press keys have no LED of their own. Both facts had to match the recovered
table exactly, or the colors would land on the wrong keys.

### The payoff

With the clock, the key grid, handedness, the inter-half link, the lights, and the
knobs all recovered and corrected against the physical board, the result was a working
QMK port, verified on the actual hardware rather than just compiled. At that point the
board was fully ours. Any keymap, any feature QMK supports.

## Part 2: the bootloader that wouldn't cooperate

Getting new firmware onto a microcontroller is the job of a small, permanent program
called the bootloader. It's separate from the keyboard firmware, it can't be
overwritten by a normal update, and it's what runs when you put the board into "update
mode." On the bcorne it lives in a protected 64 KB region with the keyboard firmware
above it, which is what makes the board effectively unbrickable. A bad flash can't
damage the thing that does the flashing.

This board's bootloader is a variant called "Plum." It uses a common, pleasant scheme
called UF2. In update mode the board pretends to be a USB flash drive, and you install
firmware by copying a `.uf2` file onto that drive. Simple in principle, and it caused
two separate problems.

### Why the standard tool waits forever

QMK's own `qmk flash` knows how to find a UF2 board and copy firmware to it, but on the
bcorne it hangs forever, never finding the board. The cause is a single filename. A UF2
bootloader puts a small identifying text file on its fake drive, named `INFO_UF2.TXT`
by convention, and that's how tools recognize the drive as a flashable board rather
than an ordinary USB stick. Plum names its file `PLUM_UF2.TXT`, so QMK never sees the
name it's looking for and waits indefinitely.

Two smaller mismatches had to be fixed alongside it, both so the board would accept and
run the file we produced. UF2 files carry a numeric tag saying which chip they're for,
and Plum accepts only one specific value, so the build had to stamp that value on its
output. And the double-tap-reset shortcut for entering update mode relies on the
firmware leaving a magic value at a spot in memory for the bootloader to find on the
next boot. Plum looks in a non-standard spot, so until that was corrected the "reboot
to bootloader" key just restarted the keyboard.

### The real problem: Linux resets the board mid-flash

With those sorted, flashing worked about half the time. On Linux the first attempt
usually failed, leaving the board back in update mode with a half-written firmware, and
a second attempt would go through. `dmesg`, the kernel's running log of hardware
events, showed why, and it's nobody's outright bug, just two reasonable behaviors
colliding. Writing firmware means erasing flash first, and this chip erases in large
chunks that take several seconds, during which Plum stops answering the computer
because it's busy. Linux has a safety mechanism. If a USB storage device goes quiet for
too long, the kernel assumes it's stuck and resets it. So the kernel resets the board
mid-write, the transfer dies, and the board is left with half a firmware.

One early theory is worth recording because it was wrong. The first guess was a
data-ordering problem, the operating system buffering writes and flushing them out of
sequence. The standard fix, forcing each write straight through to the device, was
applied and didn't help, which is exactly what proved the buffering wasn't the cause.
The kernel's reset was.

### The insight that made it reliable

The breakthrough was to stop trusting the copy operation's own report of success. On a
successful flash the board finishes and immediately reboots, so the copy sees the drive
vanish and reports an error. On a failed flash the write also dies partway. Either way
the copy "errors," so its verdict is noise.

What tells the truth is how the board reappears on the USB bus afterward. Every device
announces itself with an ID, and the bootloader and the finished keyboard have
different IDs, so the flasher ignores the copy's result and watches for one of three
things.

- The keyboard's ID appears. It worked, and the flash is done.
- The bootloader's ID reappears as a brand-new connection. The board rebooted itself
  back into update mode, so the flash didn't take. Try again.
- Nothing changes. The bootloader is still there and wedged. The script forcibly
  disconnects and reconnects its drive, the software equivalent of unplugging and
  replugging it, then rewrites.

Telling a genuine reboot from a mid-flash reset is the subtle part, and the trick is
that every USB device gets a connection number that increases on a fresh connect but
survives a kernel reset. A changed number means a real reboot. The same number means
the board was only reset mid-write and is still in the same session.

### What the flasher does today

The current `flash.sh` puts that together.

- It finds the bootloader by its USB identity read straight from the system, not by the
  drive's name or where it's mounted, because a departed board can leave a stale drive
  that fools a name-based search.
- Given administrator rights, it raises the kernel's stuck-device timeout so the erase
  has time to finish. That's why running it under `sudo` helps.
- It writes the firmware in small pieces, so if a stall hits, as little as possible is
  in flight.
- It judges every attempt by re-connection, as above, and retries up to five times.

The result is reliable in practice despite a bootloader that stalls, a kernel that
resets it, and a copy command whose success report can't be believed.

## Where the details live

The precise, addresses-and-pin-numbers version of all this is in the repository.

- `keyboards/szrkbd/bcorne/readme.md` is the board's hardware summary and flashing notes.
- `szrkbd_backup/HARDWARE_NOTES.md` is the full reverse-engineering record, each fact
  tied to the address in the firmware dump it came from.
- `keyboards/szrkbd/bcorne/flash.sh` is the flashing script, heavily commented with the
  failure modes it handles.
- `keyboards/szrkbd/bcorne/keyboard.json` and `config.h` hold the recovered hardware
  configuration as QMK consumes it.
