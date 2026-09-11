// PreSetup.java -- headless PRE-analysis script for the Keychron V10 Max flash dump
// (dump_a.bin imported with BinaryLoader at base 0x08000000, ARM:LE:32:Cortex).
//
// What it does, before auto-analysis runs:
//  1. Splits the single imported flash block into FLASH_hdr (vectors/zero/EEPROM,
//     0x08000000-0x08007FFF), FLASH_text (0x08008000-0x08017FFF, the only executable
//     block) and FLASH_unused (0x08018000-0x0803FFFF, all 0xFF).
//  2. Creates uninitialized blocks for SRAM (0x20000000, 64 KiB on STM32F401xC),
//     the peripheral buses (0x40000000 APB/AHB1, 0x50000000 AHB2/USB OTG FS) and the
//     Cortex-M private peripheral bus (0xE0000000) so pointers into them resolve.
//  3. Labels the vector table, the EEPROM backing store (0x08004000) and the
//     keymaps[6][6][18] table (0x080169B8, 1296 bytes) and types the latter as data.
//  4. Sets TMode=1 (Thumb) over the whole code range and disassembles + creates a
//     function at every odd vector-table entry (0x08000004..0x080001DC) that lands
//     inside 0x08008000..0x08040000, naming them ChibiOS-style (VectorXX_<STM32 IRQ>).
//  5. Optionally (script arg "aggressive=1") enables the "Aggressive Instruction
//     Finder" analyzer; always enables "Decompiler Parameter ID".
//
//@category Keychron
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.ArrayDataType;
import ghidra.program.model.data.DataType;
import ghidra.program.model.data.Pointer32DataType;
import ghidra.program.model.data.UnsignedShortDataType;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.mem.Memory;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.SourceType;

import java.math.BigInteger;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

public class PreSetup extends GhidraScript {

    static final long BASE = 0x08000000L;
    static final long CODE_START = 0x08008000L;   // first byte of code after the EEPROM sector
    static final long CODE_END = 0x08017F04L;     // first 0xFF byte after code+rodata
    static final long TEXT_BLOCK_END = 0x08018000L;
    static final long FLASH_END = 0x08040000L;
    static final long VECTORS_END = 0x1E0L;       // 120 words (offset from BASE)
    static final long EEPROM_BACKING = 0x08004000L;
    static final long KEYMAPS = 0x080169B8L;      // keymaps[6][6][18] u16 LE (1296 bytes)

    // Cortex-M system exception names (slots 0..15)
    static final String[] SYS = { "MasterStackPointer", "Reset", "NMI", "HardFault", "MemManage",
        "BusFault", "UsageFault", "Rsvd7", "Rsvd8", "Rsvd9", "Rsvd10", "SVCall", "DebugMon",
        "Rsvd13", "PendSV", "SysTick" };

    // STM32F401 IRQ names (positions 0..84 of the NVIC table)
    static final String[] IRQ = { "WWDG", "PVD", "TAMP_STAMP", "RTC_WKUP", "FLASH", "RCC",
        "EXTI0", "EXTI1", "EXTI2", "EXTI3", "EXTI4", "DMA1_Stream0", "DMA1_Stream1",
        "DMA1_Stream2", "DMA1_Stream3", "DMA1_Stream4", "DMA1_Stream5", "DMA1_Stream6", "ADC",
        null, null, null, null, "EXTI9_5", "TIM1_BRK_TIM9", "TIM1_UP_TIM10",
        "TIM1_TRG_COM_TIM11", "TIM1_CC", "TIM2", "TIM3", "TIM4", "I2C1_EV", "I2C1_ER",
        "I2C2_EV", "I2C2_ER", "SPI1", "SPI2", "USART1", "USART2", null, "EXTI15_10",
        "RTC_Alarm", "OTG_FS_WKUP", null, null, null, null, "DMA1_Stream7", null, "SDIO",
        "TIM5", "SPI3", null, null, null, null, "DMA2_Stream0", "DMA2_Stream1", "DMA2_Stream2",
        "DMA2_Stream3", "DMA2_Stream4", null, null, null, null, null, null, "OTG_FS",
        "DMA2_Stream5", "DMA2_Stream6", "DMA2_Stream7", "USART6", "I2C3_EV", "I2C3_ER", null,
        null, null, null, null, null, null, "FPU", null, null, "SPI4" };

    @Override
    protected void run() throws Exception {
        boolean aggressive = false;
        for (String a : getScriptArgs()) {
            if (a.equalsIgnoreCase("aggressive=1")) aggressive = true;
        }
        println("PreSetup: program=" + currentProgram.getName() + " lang=" +
            currentProgram.getLanguageID() + " aggressive=" + aggressive);

        setupMemory();
        setupLabels();
        setupVectors();
        setupAnalysisOptions(aggressive);
        println("PreSetup: done");
    }

    // ---------------------------------------------------------------- memory map
    private void setupMemory() throws Exception {
        Memory mem = currentProgram.getMemory();
        MemoryBlock flash = mem.getBlock(toAddr(BASE));
        if (flash == null) throw new Exception("no block at 0x08000000 -- was -loader-baseAddr 0x08000000 given?");
        println("PreSetup: imported block '" + flash.getName() + "' " + flash.getStart() + "-" + flash.getEnd());

        // Split: [hdr][text][unused]
        if (mem.getBlock(toAddr(CODE_START)) == flash) {
            mem.split(flash, toAddr(CODE_START));
        }
        MemoryBlock text = mem.getBlock(toAddr(CODE_START));
        if (text.getEnd().getOffset() >= TEXT_BLOCK_END) {
            mem.split(text, toAddr(TEXT_BLOCK_END));
        }
        MemoryBlock hdr = mem.getBlock(toAddr(BASE));
        text = mem.getBlock(toAddr(CODE_START));
        MemoryBlock unused = mem.getBlock(toAddr(TEXT_BLOCK_END));

        hdr.setName("FLASH_hdr");
        hdr.setRead(true); hdr.setWrite(false); hdr.setExecute(false);
        text.setName("FLASH_text");
        text.setRead(true); text.setWrite(false); text.setExecute(true);
        if (unused != null) {
            unused.setName("FLASH_unused");
            unused.setRead(true); unused.setWrite(false); unused.setExecute(false);
        }

        createUninit(mem, "SRAM", 0x20000000L, 0x10000L, true, false);        // 64 KiB SRAM (F401xC)
        createUninit(mem, "PERIPH_APB_AHB1", 0x40000000L, 0x80000L, true, true);
        createUninit(mem, "PERIPH_AHB2_USB", 0x50000000L, 0x61000L, true, true);
        createUninit(mem, "PPB_SCS", 0xE0000000L, 0x100000L, true, true);      // SysTick/NVIC/SCB/DWT/FPU

        for (MemoryBlock b : mem.getBlocks()) {
            println(String.format("PreSetup: block %-16s %s-%s r=%b w=%b x=%b vol=%b init=%b",
                b.getName(), b.getStart(), b.getEnd(), b.isRead(), b.isWrite(), b.isExecute(),
                b.isVolatile(), b.isInitialized()));
        }
    }

    private void createUninit(Memory mem, String name, long start, long size, boolean write,
            boolean vol) throws Exception {
        if (mem.getBlock(toAddr(start)) != null) return;
        MemoryBlock b = mem.createUninitializedBlock(name, toAddr(start), size, false);
        b.setRead(true);
        b.setWrite(write);
        b.setExecute(false);
        b.setVolatile(vol);
    }

    // ---------------------------------------------------------------- labels/data
    private void setupLabels() throws Exception {
        createLabel(toAddr(BASE), "g_vector_table", true, SourceType.USER_DEFINED);
        createLabel(toAddr(EEPROM_BACKING), "eeprom_backing_store", true, SourceType.USER_DEFINED);

        // keymaps[6][6][18] of uint16_t
        DataType u16 = UnsignedShortDataType.dataType;
        DataType row = new ArrayDataType(u16, 18, 2);
        DataType layer = new ArrayDataType(row, 6, row.getLength());
        DataType all = new ArrayDataType(layer, 6, layer.getLength());
        Address km = toAddr(KEYMAPS);
        if (currentProgram.getListing().isUndefined(km, km.add(all.getLength() - 1))) {
            createData(km, all);
        }
        createLabel(km, "keymaps", true, SourceType.USER_DEFINED);
        println("PreSetup: keymaps typed as " + all.getName() + " (" + all.getLength() + " bytes) at " + km);
    }

    // ---------------------------------------------------------------- vectors
    private void setupVectors() throws Exception {
        Listing lst = currentProgram.getListing();
        Register tmode = currentProgram.getProgramContext().getRegister("TMode");
        // Thumb everywhere in the text block
        currentProgram.getProgramContext().setValue(tmode, toAddr(CODE_START),
            toAddr(TEXT_BLOCK_END - 1), BigInteger.ONE);

        // First pass: count how often each target appears (the shared default handler)
        Map<Long, Integer> count = new HashMap<>();
        for (long off = 4; off < VECTORS_END; off += 4) {
            long v = getInt(toAddr(BASE + off)) & 0xFFFFFFFFL;
            if (isCodeVector(v)) count.merge(v & ~1L, 1, Integer::sum);
        }

        TreeMap<Long, String> created = new TreeMap<>();
        int n = 0;
        for (long off = 0; off < VECTORS_END; off += 4) {
            Address slot = toAddr(BASE + off);
            long v = getInt(slot) & 0xFFFFFFFFL;
            int idx = (int) (off / 4);
            String slotName = idx < 16 ? SYS[idx] : irqName(idx - 16);
            if (lst.isUndefined(slot, slot.add(3))) {
                createData(slot, new Pointer32DataType());
            }
            createLabel(slot, "vec_" + String.format("%02X", off) + "_" + slotName, false,
                SourceType.USER_DEFINED);
            if (off == 0 || !isCodeVector(v)) continue;

            long target = v & ~1L;
            Address ta = toAddr(target);
            String fname;
            if (count.get(target) > 4) {
                fname = "_unhandled_exception";          // ChibiOS default handler
            } else if (idx == 1) {
                fname = "_crt0_entry";                   // ChibiOS reset handler
            } else if (idx < 16) {
                fname = SYS[idx] + "_Handler";
            } else {
                fname = "Vector" + String.format("%02X", off) + "_" + slotName;
            }
            if (lst.getInstructionAt(ta) == null) {
                try {
                    currentProgram.getProgramContext().setValue(tmode, ta, ta, BigInteger.ONE);
                } catch (Exception e) {
                    println("PreSetup: TMode already fixed at " + ta + " (" + e.getMessage() + ")");
                }
            }
            if (lst.isUndefined(ta, ta)) {
                disassemble(ta);
            }
            Function f = lst.getFunctionAt(ta);
            if (f == null) {
                f = createFunction(ta, fname);
                if (f == null) {
                    // fall back to a label; auto-analysis will create the function later
                    createLabel(ta, fname, true, SourceType.USER_DEFINED);
                }
                n++;
            }
            if (!created.containsKey(target)) {
                created.put(target, fname);
            }
        }
        println("PreSetup: vector-table code entry points: " + created.size() + " distinct (" + n + " created)");
        for (Map.Entry<Long, String> e : created.entrySet()) {
            println(String.format("PreSetup:   0x%08X %s", e.getKey(), e.getValue()));
        }
    }

    private static boolean isCodeVector(long v) {
        return (v & 1) == 1 && v >= CODE_START && v < FLASH_END;
    }

    private static String irqName(int irq) {
        if (irq >= 0 && irq < IRQ.length && IRQ[irq] != null) return "IRQ" + irq + "_" + IRQ[irq];
        return "IRQ" + irq;
    }

    // ---------------------------------------------------------------- analysis options
    private void setupAnalysisOptions(boolean aggressive) throws Exception {
        Map<String, String> opts = getCurrentAnalysisOptionsAndValues(currentProgram);
        TreeMap<String, String> sorted = new TreeMap<>(opts);
        for (Map.Entry<String, String> e : sorted.entrySet()) {
            println("PreSetup: analysis option [" + e.getKey() + "] = " + e.getValue());
        }
        for (String key : sorted.keySet()) {
            if (key.indexOf('.') >= 0) continue;           // only analyzer enable flags
            if (key.contains("Aggressive Instruction Finder")) {
                setAnalysisOption(currentProgram, key, aggressive ? "true" : "false");
                println("PreSetup: set [" + key + "] = " + aggressive);
            }
            if (key.equals("Decompiler Parameter ID")) {
                setAnalysisOption(currentProgram, key, "true");
                println("PreSetup: set [" + key + "] = true");
            }
        }
        if (sorted.containsKey("ASCII Strings.Minimum string length")) {
            setAnalysisOption(currentProgram, "ASCII Strings.Minimum string length", "LEN_4");
            println("PreSetup: set [ASCII Strings.Minimum string length] = LEN_4");
        }
    }
}
