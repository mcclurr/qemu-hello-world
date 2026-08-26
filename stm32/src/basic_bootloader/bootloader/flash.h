#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>

int flash_erase_application(void);
int flash_program_word(uint32_t address, uint32_t data);

#endif          