ENTRY( call_start_cpu0 );

/* Specify main memory areas */
MEMORY
{
  iram_seg ( RWX )       : ORIGIN = 0x40080000, len = 128k /*these segs are loaded automatically into RAM by stage 1 bootloader*/
  dram_seg ( RW )       : ORIGIN = 0x3FFE0000, len = 128k
}

EXTERN(windowExceptionHandler)
EXTERN(Level2InterruptHandler)
EXTERN(Level3InterruptHandler)
EXTERN(Level4InterruptHandler)
EXTERN(Level5InterruptHandler)
EXTERN(DebugExceptionHandler)
EXTERN(NMIHandler)
EXTERN(KernelExceptionHandler)
EXTERN(UserExceptionHandler)
EXTERN(DoubleExceptionHandler)

EXTERN(_WindowVectorsStub)
EXTERN(_Level2InterruptStub)
EXTERN(_Level3InterruptStub)
EXTERN(_Level4InterruptStub)
EXTERN(_Level5InterruptStub)
EXTERN(_DebugExceptionStub)
EXTERN(_NMIExceptionStub)
EXTERN(_KernelExceptionStub)
EXTERN(_UserExceptionStub)
EXTERN(_DoubleExceptionStub)

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

    _vecbase_start = ABSOLUTE(.);

    /* 0x000: Window Overflow/Underflow exceptions */
    KEEP(*(.WindowVectors.text)); 
        
    /* 0x140: Level 2 Interrupts */
    . = 0x140; 
    KEEP(*(.Level2InterruptVector.text));
        
    /* 0x180: Level 3 Interrupts */
    . = 0x180; 
    KEEP(*(.Level3InterruptVector.text));
        
    /* 0x1C0: Level 4 Interrupts */
    . = 0x1C0; 
    KEEP(*(.Level4InterruptVector.text));
    
    /* 0x200: Level 5 Interrupts */
    . = 0x200; 
    KEEP(*(.Level5InterruptVector.text));
    
    /* 0x240: Debug Exceptions */
    . = 0x240; 
    KEEP(*(.DebugExceptionVector.text));
    
    /* 0x280: NMI Exceptions (Level 7) */
    . = 0x280; 
    KEEP(*(.NMIExceptionVector.text));
    
    /* 0x2C0: Kernel Exceptions */
    . = 0x2C0; 
    KEEP(*(.KernelExceptionVector.text));
    
    /* 0x340: User Exceptions (Most standard hardware exceptions end up here) */
    . = 0x340; 
    KEEP(*(.UserExceptionVector.text));
    
    /* 0x3C0: Double Exceptions */
    . = 0x3C0; 
    KEEP(*(.DoubleExceptionVector.text));
    
    _vecbase_end = ABSOLUTE(.);

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