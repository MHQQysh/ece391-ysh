/* lib.h - 基础库函数声明 */

#ifndef _LIB_H
#define _LIB_H

#include "types.h"

/* VGA文本模式显示 */
#define VIDEO_MEM       0xB8000     /* VGA文本模式显存地址 */
#define NUM_COLS        80          /* 屏幕列数 */
#define NUM_ROWS        25          /* 屏幕行数 */

/* 颜色定义 */
#define ATTRIB          0x7         /* 白字黑底 */

/* 屏幕操作 */
void clear(void);
void puts(const char* s);
int32_t printf(const char* format, ...);

/* 字符串操作 */
int32_t strlen(const char* s);
void* memset(void* s, int32_t c, uint32_t n);
void* memcpy(void* dest, const void* src, uint32_t n);

/* 端口I/O */
static inline void outb(uint16_t port, uint8_t val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* 中断控制 */
static inline void cli(void) {
    asm volatile("cli");
}

static inline void sti(void) {
    asm volatile("sti");
}

#endif /* _LIB_H */
