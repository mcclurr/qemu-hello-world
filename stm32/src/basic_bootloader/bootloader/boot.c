#include <stdint.h>

#include "boot.h"

#define RAM_START   0x20000000UL
#define RAM_END     0x20020000UL

#define FLASH_END   0x08080000UL

#define SCB_VTOR    (*(volatile uint32_t *)0xE000ED08UL)

uint32_t boot_get_app_stack(void)
{
    return *(volatile uint32_t *)(APP_ADDR + 0U);
}

uint32_t boot_get_app_reset(void)
{
    return *(volatile uint32_t *)(APP_ADDR + 4U);
}

int boot_application_is_valid(void)
{
    uint32_t app_stack = boot_get_app_stack();
    uint32_t app_reset = boot_get_app_reset();

    if (app_stack < RAM_START || app_stack > RAM_END) {
        return 0;
    }

    if (app_reset < APP_ADDR || app_reset >= FLASH_END) {
        return 0;
    }

    if ((app_reset & 1U) == 0U) {
        return 0;
    }

    return 1;
}

void jump_to_application(void)
{
    uint32_t app_stack = boot_get_app_stack();
    uint32_t app_reset = boot_get_app_reset();

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