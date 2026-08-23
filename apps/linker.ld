SECTIONS 
{
    .text : { *(.text) }

    /DISCARD/ : 
    {
        *(.comment)
        *(.xtensa.info)
        *(.xt.prop)
        *(.xt.lit)
    }
}