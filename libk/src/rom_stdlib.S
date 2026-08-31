#include "romfuncs.h"
  
.macro BIND_ROM_FUNC name addr
        .global \name
        .type \name, @function
        .align 4
    
    \name:
        movi    a8, \addr
        j       rom_call_stub
.endm
        
BIND_ROM_FUNC itoa, addr_ITOA 
BIND_ROM_FUNC strlen, addr_STRLEN
BIND_ROM_FUNC abort, addr_ABORT
BIND_ROM_FUNC abs, addr_ABS
BIND_ROM_FUNC atoi, addr_ATOI
BIND_ROM_FUNC atol, addr_ATOL
BIND_ROM_FUNC div, addr_DIV
BIND_ROM_FUNC labs, addr_LABS
BIND_ROM_FUNC ldiv, addr_LDIV
BIND_ROM_FUNC qsort, addr_QSORT
BIND_ROM_FUNC strtol, addr_STRTOL
BIND_ROM_FUNC strtoul, addr_STRTOUL