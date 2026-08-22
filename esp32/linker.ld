ENTRY( call_start_cpu0 );

/* Specify main memory areas */
MEMORY
{
  iram_seg ( RWX )       : ORIGIN = 0x40080000, len = 128k /*these segs are loaded automatically into RAM by stage 1 bootloader*/
  dram_seg ( RW )       : ORIGIN = 0x3FFE0000, len = 128k
}

/* Define output sections */
SECTIONS 
{
  /DISCARD/ : {
    *(.eh_frame)
    *(.eh_frame_hdr)
    *(.comment)
    *(.xt*)
  }
  .iram.text : ALIGN(4)
  {
    . = ALIGN(16);
    KEEP(*(.entry.text))
    *(.text)
    *(.text*)
    KEEP (*(.init))
    KEEP (*(.fini))
    
    *(.literal .text .literal.* .text.*)

    . = ALIGN(4);
    _etext = .;
  } >iram_seg

  _sidata = .;
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;
    PROVIDE(_sdata = .);
    *(.data)
    *(.data*)

    *(.rodata)
    *(.rodata*)
    
    . = ALIGN(4);
    _edata = .;
    PROVIDE(_edata = .);
  } >dram_seg

  /* Uninitialized data also goes into Data RAM */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;
    PROVIDE(_ebss = .);
  } >dram_seg

  .init_section : ALIGN(4)
  {
    . = ALIGN(4);
    __init_array_start = .;
    KEEP (*(.init))
    KEEP(*(.init_array))
    KEEP(*(.init_array.*))
    KEEP(*(.ctors))
    KEEP(*(.ctors.*))
    __init_array_end = .;
  } >dram_seg

  . = ALIGN(4);
  PROVIDE ( end = . );
  PROVIDE ( _end = . );
}