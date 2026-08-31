#include "romfuncs.h"

.macro BIND_ROM_FUNC name addr
        .global \name
        .type \name, @function
        .align 4

    \name:
        movi    a8, \addr
        j       rom_call_stub
.endm

BIND_ROM_FUNC memcpy, addr_MEMCPY
BIND_ROM_FUNC memmove, addr_MEMMOVE
BIND_ROM_FUNC strcpy, addr_STRCPY
BIND_ROM_FUNC strncpy, addr_STRNCPY
BIND_ROM_FUNC strcat, addr_STRCAT
BIND_ROM_FUNC strncat, addr_STRNCAT
BIND_ROM_FUNC memcmp, addr_MEMCMP
BIND_ROM_FUNC strcmp, addr_STRCMP
BIND_ROM_FUNC strcoll, addr_STRCOLL
BIND_ROM_FUNC strncmp, addr_STRNCMP
BIND_ROM_FUNC memchr, addr_MEMCHR
BIND_ROM_FUNC strchr, addr_STRCHR
BIND_ROM_FUNC strcspn, addr_STRCSPN
BIND_ROM_FUNC strrchr, addr_STRRCHR
BIND_ROM_FUNC strspn, addr_STRSPN
BIND_ROM_FUNC strstr, addr_STRSTR
BIND_ROM_FUNC memset, addr_MEMSET
