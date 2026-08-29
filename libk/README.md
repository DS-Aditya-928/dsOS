What this is: a bastardized kernel level libc (libk?) implementation that steals bits from the esp32's ROM (and adds the ABI0 conversion when needed) and implements the rest from scratch when necessary.

Eventually we're doing usermode/kernelmode so some will need to be rewirtten to do the interrupts for calls like sbrk and such but for now we can just wing it.