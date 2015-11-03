
_STACKSIZE = 1024;
_HEAPSIZE = 256;

MEMORY
{
  /* Define each memory region */
  MFlash512 (rx) : ORIGIN = 0x0, LENGTH = 0x80000 /* 512K bytes */
  RamLoc64 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x10000 /* 64K bytes */
  RamPeriph32 (rwx) : ORIGIN = 0x20000000, LENGTH = 0x8000 /* 32K bytes */
  SPIFI (rwx) : ORIGIN = 0x28000000, LENGTH = 0x1000000 /* 16M bytes */
}

  /* Define a symbol for the top of each memory region */
  __top_MFlash512 = 0x0 + 0x80000;
  __top_RamLoc64 = 0x10000000 + 0x10000;
  __top_RamPeriph32 = 0x20000000 + 0x8000;
  __top_SPIFI = 0x28000000 + 0x1000000;


ENTRY(ResetISR)

SECTIONS
{

    /* MAIN TEXT SECTION */
    .text : ALIGN(4)
    {
        FILL(0xff)
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))

        CREATE_OBJECT_SYMBOLS
        *(.text .text.*)
        *(.gnu.linkonce.t.*)
        *(.glue_7t) *(.glue_7) *(.vfp11_veneer)
        KEEP(*(.fini))
        *(.gcc_except_table)

        /* Global Section Table */
        . = ALIGN(4) ;
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG(    ADDR(.data));
        LONG(  SIZEOF(.data));
        LONG(LOADADDR(.data_RAM2));
        LONG(    ADDR(.data_RAM2));
        LONG(  SIZEOF(.data_RAM2));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
        LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        __bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */


        *(.after_vectors*)

    } >MFlash512

    /* .ctors .dtors are used for c++ constructors/destructors */

    .ctors : ALIGN(4)
    {
        PROVIDE(__ctors_start__ = .);
        KEEP(*(SORT(.ctors.*)))
        KEEP(*(.ctors))
        PROVIDE(__ctors_end__ = .);
    } >MFlash512

    .dtors : ALIGN(4)
    {
        PROVIDE(__dtors_start__ = .);
        KEEP(*(SORT(.dtors.*)))
        KEEP(*(.dtors))
        PROVIDE(__dtors_end__ = .);
    } >MFlash512

    .text : ALIGN(4)
    {
        *(.text*)
        *(.rodata .rodata.* .constdata .constdata.*)
        *(.gnu.linkonce.r.*)
        . = ALIGN(4);

    } > MFlash512

    .init_array :
    {
        *(.init)
        *(.fini)
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        PROVIDE_HIDDEN (__init_array_end = .);
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        PROVIDE_HIDDEN (__fini_array_end = .);
    } >MFlash512

    . = ALIGN(4);


    /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this.
     */
    .ARM.extab : ALIGN(4)
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > MFlash512
    __exidx_start = .;

    .ARM.exidx : ALIGN(4)
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > MFlash512
    __exidx_end = .;

    _etext = .;


    /* DATA section for RamPeriph32 */
    .data_RAM2 : ALIGN(4)
    {
       FILL(0xff)
       PROVIDE(__start_data_RAM2 = .) ;
       *(.ramfunc.$RAM2)
       *(.ramfunc.$RamPeriph32)
        *(.data.$RAM2*)
        *(.data.$RamPeriph32*)
       . = ALIGN(4) ;
       PROVIDE(__end_data_RAM2 = .) ;
    } > RamPeriph32 AT>MFlash512

    /* MAIN DATA SECTION */


    .uninit_RESERVED : ALIGN(4)
    {
        KEEP(*(.bss.$RESERVED*))
        . = ALIGN(4) ;
        _end_uninit_RESERVED = .;
    } > RamLoc64


    /* Main DATA section (RamLoc64) */
    .data : ALIGN(4)
    {
       FILL(0xff)
       _data = . ;
       *(vtable)
       *(.ramfunc*)
       *(.data*)
        *(.data .data.*)
        *(.gnu.linkonce.d.*)
        SORT(CONSTRUCTORS)
       . = ALIGN(4) ;
        *(.fastrun .fastrun.*)
       . = ALIGN(4) ;
       _edata = . ;
    } > RamLoc64 AT>MFlash512

    /* BSS section for RamPeriph32 */
    .bss_RAM2 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM2 = .) ;
        *(.bss.$RAM2*)
        *(.bss.$RamPeriph32*)
       . = ALIGN(4) ;
       PROVIDE(__end_bss_RAM2 = .) ;
    } > RamPeriph32

    /* MAIN BSS SECTION */
    .bss : ALIGN(4)
    {
        _bss = .;
        *(.bss*)
        *(.gnu.linkonce.b.*)
        *(COMMON)
        . = ALIGN(4) ;
        _ebss = .;
        PROVIDE(end = .);
    } > RamLoc64

    /* .heap section which is used for memory allocation */
    .heap (NOLOAD) :
    {
        __heap_start__ = .;
        *(.heap*)
        . = MAX(__heap_start__ + _HEAPSIZE , .);
    } > RamLoc64
    __heap_end__ = __heap_start__ + SIZEOF(.heap);

    /* .stack section - user mode stack */
    .stack (__heap_end__ + 3) / 4 * 4 (NOLOAD) :
    {
        . = ALIGN(8);
        __stack_start__ = .;
        *(.stack)
        . = ALIGN(8);
        . = MAX(__stack_start__ + _STACKSIZE , .);
    } >RamLoc64
    __stack_end__ = __stack_start__ + SIZEOF(.stack);

    /* NOINIT section for RamPeriph32 */
    .noinit_RAM2 (NOLOAD) : ALIGN(4)
    {
        *(.noinit.$RAM2*)
        *(.noinit.$RamPeriph32*)
       . = ALIGN(4) ;
    } > RamPeriph32

    /* DEFAULT NOINIT SECTION */
    .noinit (NOLOAD): ALIGN(4)
    {
        _noinit = .;
        *(.noinit*)
         . = ALIGN(4) ;
        _end_noinit = .;
    } > RamLoc64

    PROVIDE(_pvHeapStart = DEFINED(__user_heap_base) ? __user_heap_base : .);
    PROVIDE(_vStackTop = DEFINED(__user_stack_top) ? __user_stack_top : __top_RamLoc64 - 0);

    ExtFlashSection :
    {
        *(ExtFlashSection ExtFlashSection.*)
        *(.gnu.linkonce.r.*)
    } >SPIFI
}
