#ifndef BOOT_H
#define BOOT_H

#include <stdint.h>

#define APP_ADDR 0x08008000UL

uint32_t boot_get_app_stack(void);
uint32_t boot_get_app_reset(void);
int boot_application_is_valid(void);

void jump_to_application(void);

#endif