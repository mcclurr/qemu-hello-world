#include <stdint.h>

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

static void uart_init(void)
{
    RCC_AHB1ENR |= (1U << 0);
    RCC_APB1ENR |= (1U << 17);

    GPIOA_MODER &= ~(3U << (2 * 2));
    GPIOA_MODER |=  (2U << (2 * 2));

    GPIOA_AFRL &= ~(0xFU << (2 * 4));
    GPIOA_AFRL |=  (7U   << (2 * 4));

    USART2_BRR = 0x008B;
    USART2_CR1 |= (1U << 3);
    USART2_CR1 |= (1U << 13);
}

static void uart_putchar(char c)
{
    while (!(USART2_SR & (1U << 7))) {
    }
    USART2_DR = (uint8_t)c;
}

static void uart_puts(const char *s)
{
    while (*s) {
        uart_putchar(*s++);
    }
}

int main(void)
{
    uart_init();
    uart_puts("Hello from application!\r\n");

    while (1) {
    }
}
