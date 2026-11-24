#include <stdint.h>

/* UART 发送单字节（轮询方式） */
void uart_putc(uint8_t c)
{
    uint32_t guard = 0;

    while (!(USART1->SR & (1 << 7))) {     /* 等 TXE 置位 */
        __NOP();                            /* 空转插空操作，降低总线争用 */
        if (++guard > 100000u) return;      /* 超时保护：外设异常时不要死等 */
    }
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
