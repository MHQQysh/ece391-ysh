/* lib.c - 基础库函数实现 */

#include "lib.h"

/* 屏幕光标位置 */
static int screen_x = 0;
static int screen_y = 0;

/* 视频内存指针 */
static char* video_mem = (char*)VIDEO_MEM;

/* clear - 清空屏幕 */
void clear(void) {
    int32_t i;
    for (i = 0; i < NUM_ROWS * NUM_COLS; i++) {
        *(uint8_t *)(video_mem + (i << 1)) = ' ';
        *(uint8_t *)(video_mem + (i << 1) + 1) = ATTRIB;
    }
    screen_x = 0;
    screen_y = 0;
}

/* putc - 在屏幕上显示一个字符 */
static void putc(char c) {
    if (c == '\n' || c == '\r') {
        screen_x = 0;
        screen_y++;
    } else {
        *(uint8_t *)(video_mem + ((NUM_COLS * screen_y + screen_x) << 1)) = c;
        *(uint8_t *)(video_mem + ((NUM_COLS * screen_y + screen_x) << 1) + 1) = ATTRIB;
        screen_x++;
        if (screen_x >= NUM_COLS) {
            screen_x = 0;
            screen_y++;
        }
    }

    /* 滚屏 */
    if (screen_y >= NUM_ROWS) {
        int32_t i;
        for (i = 0; i < (NUM_ROWS - 1) * NUM_COLS; i++) {
            *(uint8_t *)(video_mem + (i << 1)) =
                *(uint8_t *)(video_mem + ((i + NUM_COLS) << 1));
            *(uint8_t *)(video_mem + (i << 1) + 1) =
                *(uint8_t *)(video_mem + ((i + NUM_COLS) << 1) + 1);
        }
        for (i = (NUM_ROWS - 1) * NUM_COLS; i < NUM_ROWS * NUM_COLS; i++) {
            *(uint8_t *)(video_mem + (i << 1)) = ' ';
            *(uint8_t *)(video_mem + (i << 1) + 1) = ATTRIB;
        }
        screen_y = NUM_ROWS - 1;
    }
}

/* puts - 显示字符串 */
void puts(const char* s) {
    while (*s) {
        putc(*s);
        s++;
    }
}

/* 简化版printf - 只支持 %s, %d, %x */
int32_t printf(const char* format, ...) {
    char buf[1024];
    int32_t* args = (int32_t*)&format + 1;
    int32_t arg_idx = 0;
    int32_t i = 0;

    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 's') {
                /* 字符串 */
                char* s = (char*)args[arg_idx++];
                while (*s) {
                    putc(*s++);
                }
            } else if (*format == 'd') {
                /* 十进制整数 */
                int32_t num = args[arg_idx++];
                if (num < 0) {
                    putc('-');
                    num = -num;
                }
                if (num == 0) {
                    putc('0');
                } else {
                    char digits[16];
                    int32_t idx = 0;
                    while (num > 0) {
                        digits[idx++] = '0' + (num % 10);
                        num /= 10;
                    }
                    while (idx > 0) {
                        putc(digits[--idx]);
                    }
                }
            } else if (*format == 'x') {
                /* 十六进制 */
                uint32_t num = args[arg_idx++];
                char hex[] = "0123456789ABCDEF";
                putc('0');
                putc('x');
                int32_t started = 0;
                int32_t j;
                for (j = 28; j >= 0; j -= 4) {
                    uint8_t digit = (num >> j) & 0xF;
                    if (digit != 0 || started || j == 0) {
                        putc(hex[digit]);
                        started = 1;
                    }
                }
            }
        } else {
            putc(*format);
        }
        format++;
    }
    return 0;
}

/* strlen - 计算字符串长度 */
int32_t strlen(const char* s) {
    int32_t len = 0;
    while (*s++) len++;
    return len;
}

/* memset - 设置内存 */
void* memset(void* s, int32_t c, uint32_t n) {
    uint8_t* p = (uint8_t*)s;
    while (n--) {
        *p++ = (uint8_t)c;
    }
    return s;
}

/* memcpy - 复制内存 */
void* memcpy(void* dest, const void* src, uint32_t n) {
    uint8_t* d = (uint8_t*)dest;
    const uint8_t* s = (const uint8_t*)src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}
