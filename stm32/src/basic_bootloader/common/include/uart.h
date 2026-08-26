#ifndef UART_H
#define UART_H

#include <stdint.h>

uint32_t uart_get_u32(void);

void uart_puthex32(uint32_t value);

void uart_init(void);

void uart_putchar(char c);

void uart_puts(const char *s);

char uart_getchar(void);

#endif