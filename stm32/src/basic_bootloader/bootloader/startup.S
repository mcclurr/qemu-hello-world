.syntax unified
.cpu cortex-m4
.thumb

.section .isr_vector, "a", %progbits
.global vector_table

vector_table:
    .word _stack_top
    .word Reset_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word Default_Handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word Default_Handler
    .word Default_Handler
    .word 0
    .word Default_Handler
    .word Default_Handler

.section .text.Reset_Handler, "ax", %progbits
.global Reset_Handler
.type Reset_Handler, %function

Reset_Handler:
    ldr r0, =_data_load
    ldr r1, =_data_start
    ldr r2, =_data_end

copy_data:
    cmp r1, r2
    bcs zero_bss
    ldr r3, [r0], #4
    str r3, [r1], #4
    b copy_data

zero_bss:
    ldr r0, =_bss_start
    ldr r1, =_bss_end
    movs r2, #0

clear_bss:
    cmp r0, r1
    bcs call_main
    str r2, [r0], #4
    b clear_bss

call_main:
    bl main

hang:
    b hang

.size Reset_Handler, . - Reset_Handler

.section .text.Default_Handler, "ax", %progbits
.type Default_Handler, %function
Default_Handler:
    b Default_Handler
.size Default_Handler, . - Default_Handler
