#include <stdint.h>

/* 一个简单的环形缓冲，先用它演示 git 的提交与分支 */
#define BUF_SIZE 64

static uint8_t buf[BUF_SIZE];
static uint16_t head = 0;
static uint16_t tail = 0;

void buf_put(uint8_t c)
{
    buf[head] = c;
    head = (head + 1) % BUF_SIZE;
}

int buf_get(uint8_t *c)
{
    if (head == tail) return 0;      /* 空 */
    *c = buf[tail];
    tail = (tail + 1) % BUF_SIZE;
    return 1;
}

int buf_empty(void)
{
    return (head == tail);
}
