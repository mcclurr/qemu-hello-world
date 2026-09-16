.section .text.start
.globl _start
.globl _secondary_start

_start:
    # We already know the U-Boot boot hart is hart 1.
    la sp, _stack_top_hart1

    call main

1:
    j 1b


_secondary_start:
    # OpenSBI guarantees:
    #   a0 = hart ID
    #   a1 = opaque value
    #
    # We are only starting hart 2 for now,
    # so give it its own stack.

    la sp, _stack_top_hart2

    # a0 still contains the hart ID.
    call secondary_main

2:
    j 2b