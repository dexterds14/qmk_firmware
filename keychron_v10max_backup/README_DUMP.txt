Keychron V10 Max flash dump
Date: 2026-09-11T00:48:38Z
Method: dfu-util 0.11, ROM DFU 0483:df11, reset button under spacebar (not Esc), switch on Cable
DFU serial: 204C33753632
Alt0: @Internal Flash  /0x08000000/04*016Kg,01*064Kg,01*128Kg (256 KB, STM32F401xC)
Option bytes: ef aa 10 55 ... (RDP=0xAA level 0)
Files: dump_a.bin/dump_c.bin = two full 0x40000 reads (identical); dump_b.bin = segment-limited read of first 64 KB
Image: SP 0x20000400, reset 0x0800811D, zero 0x200-0x3FFF, EEPROM backing at 0x4000-0x4FFF, code 0x8000-0x17F04 (98052 B)
Strings: "Keychron V10 Max", build date 2024-07-09-13:57:36, newlib path ../../../../../../newlib/libc/stdlib/rand.c
