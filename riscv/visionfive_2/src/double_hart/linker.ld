ENTRY(_start)

SECTIONS
{
    . = 0x42000000;

    .text : {
        *(.text.start)
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data*)
    }

    .bss : {
        *(.bss*)
        *(COMMON)
    }

    . = ALIGN(16);

    /* Hart 1 stack */
    . += 0x4000;
    _stack_top_hart1 = .;

    /* Hart 2 stack */
    . += 0x4000;
    _stack_top_hart2 = .;
}