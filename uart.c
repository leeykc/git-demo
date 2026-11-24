#include <stdint.h>

/* UART 发送单字节（轮询方式） */
void uart_putc(uint8_t c)
{
    while (!(USART1->SR & (1 << 7))) { __NOP(); }   /* 空转时插空操作，降低总线争用 */
    USART1->DR = c;
}

void uart_puts(const char *s)
{
    while (*s) {
        uart_putc((uint8_t)*s);
        s++;
    }
}
/* TODO: 改成 DMA 发送 */
