#include <stdint.h>

#include "boot.h"


#define APP_ADDR    0x08008000UL

#define SCB_VTOR    (*(volatile uint32_t *)0xE000ED08UL)


void jump_to_application(void)
{
    uint32_t app_stack =
        *(volatile uint32_t *)(APP_ADDR + 0U);

    uint32_t app_reset =
        *(volatile uint32_t *)(APP_ADDR + 4U);

    SCB_VTOR = APP_ADDR;

    __asm volatile (
        "msr msp, %0\n"
        "bx %1\n"
        :
        : "r" (app_stack), "r" (app_reset)
        : "memory"
    );

    __builtin_unreachable();
}