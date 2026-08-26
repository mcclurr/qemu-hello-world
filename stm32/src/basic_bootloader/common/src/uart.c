#include <stdint.h>

#include "uart.h"


#define RCC_BASE        0x40023800UL
#define GPIOA_BASE      0x40020000UL
#define USART2_BASE     0x40004400UL

#define RCC_AHB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR     (*(volatile uint32_t *)(RCC_BASE + 0x40))

#define GPIOA_MODER     (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRL      (*(volatile uint32_t *)(GPIOA_BASE + 0x20))

#define USART2_SR       (*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_DR       (*(volatile uint32_t *)(USART2_BASE + 0x04))
#define USART2_BRR      (*(volatile uint32_t *)(USART2_BASE + 0x08))
#define USART2_CR1      (*(volatile uint32_t *)(USART2_BASE + 0x0C))


void uart_init(void)
{
    /* Enable GPIOA clock. */
    RCC_AHB1ENR |= (1U << 0);

    /* Enable USART2 clock. */
    RCC_APB1ENR |= (1U << 17);

    /* PA2 = alternate function mode. */
    GPIOA_MODER &= ~(3U << (2 * 2));
    GPIOA_MODER |=  (2U << (2 * 2));

    /* PA2 = AF7 = USART2_TX. */
    GPIOA_AFRL &= ~(0xFU << (2 * 4));
    GPIOA_AFRL |=  (7U   << (2 * 4));

    /* PA3 = alternate function mode. */
    GPIOA_MODER &= ~(3U << (3 * 2));
    GPIOA_MODER |=  (2U << (3 * 2));

    /* PA3 = AF7 = USART2_RX. */
    GPIOA_AFRL &= ~(0xFU << (3 * 4));
    GPIOA_AFRL |=  (7U   << (3 * 4));

    /* 115200 baud with 16 MHz peripheral clock. */
    USART2_BRR = 0x008B;

    /* Enable TX and RX. */
    USART2_CR1 |= (1U << 3);
    USART2_CR1 |= (1U << 2);

    /* Enable USART. */
    USART2_CR1 |= (1U << 13);
}

uint32_t uart_get_u32(void)
{
    uint32_t value = 0;

    value |= (uint32_t)(uint8_t)uart_getchar() << 0;
    value |= (uint32_t)(uint8_t)uart_getchar() << 8;
    value |= (uint32_t)(uint8_t)uart_getchar() << 16;
    value |= (uint32_t)(uint8_t)uart_getchar() << 24;

    return value;
}

void uart_puthex32(uint32_t value)
{
    static const char hex[] = "0123456789ABCDEF";

    uart_puts("0x");

    for (int shift = 28; shift >= 0; shift -= 4) {
        uint32_t digit = (value >> shift) & 0xFU;
        uart_putchar(hex[digit]);
    }
}

void uart_putchar(char c)
{
    while (!(USART2_SR & (1U << 7))) {
    }

    USART2_DR = (uint8_t)c;
}


void uart_puts(const char *s)
{
    while (*s) {
        uart_putchar(*s++);
    }
}


char uart_getchar(void)
{
    while (!(USART2_SR & (1U << 5))) {
    }

    return (char)(USART2_DR & 0xFF);
}