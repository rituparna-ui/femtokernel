ENTRY(_start)

SECTIONS
{
    . = 0x80000;

    .text : {
        *(.text.boot)
        *(.text)
    }

    .bss : {
        *(.bss)
    }
}
