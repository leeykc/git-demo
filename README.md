# UART 环形缓冲与串口收发

STM32F103 上用 C 实现的串口基础模块，最初作为 MPU6050 姿态采集项目的底层。

## 文件

| 文件 | 内容 |
|---|---|
| `main.c` | 环形缓冲：`buf_put` 写入、`buf_get` 读取、`buf_empty` 判空 |
| `uart.c` | 串口发送：`uart_putc` 单字节（轮询 TXE）、`uart_puts` 字符串 |

## 为什么用环形缓冲

串口中断里只做一件事：把收到的字节塞进缓冲。主循环再从缓冲里取出来处理。

这样中断执行时间恒定（几个时钟周期），不会因为上层处理慢而丢数据。

## 接口

```c
void buf_put(uint8_t c);          /* 写入一个字节 */
int  buf_get(uint8_t *c);         /* 读出一个字节，返回 1 成功 / 0 空 */
int  buf_empty(void);             /* 判空 */

void uart_putc(uint8_t c);        /* 轮询等待 TXE 后发送 */
void uart_puts(const char *s);    /* 发送字符串 */
```

## 已知限制

- `uart_putc` 是**轮询**方式，等 TXE 时 CPU 空转；发长字符串会占住主循环
- 环形缓冲**没有满判断**，写入速度超过读取速度时会覆盖未读数据
- 未做 DMA、未做中断接收

## 后续计划

- [ ] 发送改为 DMA，释放 CPU（见 `uart.c` 中的 TODO）
- [ ] 环形缓冲加满判断与丢弃计数
- [ ] 接收改为中断 + 空闲中断判帧尾

## 环境

STM32F103C8T6 / Keil MDK / 纯 C99，除 HAL 外不依赖第三方库。
