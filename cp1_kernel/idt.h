/* idt.h - 中断描述符表定义 */

#ifndef _IDT_H
#define _IDT_H

#include "types.h"

/* IDT条目数 */
#define NUM_IDT_ENTRIES 256

/* 段选择子 */
#define KERNEL_CS       0x0010      /* 内核代码段 */

/* IDT条目结构 */
typedef struct idt_desc {
    uint16_t offset_low;        /* 处理函数地址低16位 */
    uint16_t seg_selector;      /* 段选择子 */
    uint8_t  reserved;          /* 保留（必须为0） */
    uint8_t  type_attr;         /* 类型和属性 */
    uint16_t offset_high;       /* 处理函数地址高16位 */
} __attribute__((packed)) idt_desc_t;

/* IDT指针结构 - 用于LIDT指令 */
typedef struct idt_ptr {
    uint16_t limit;             /* IDT大小-1 */
    uint32_t base;              /* IDT基地址 */
} __attribute__((packed)) idt_ptr_t;

/* 初始化IDT */
void idt_init(void);

/* 设置IDT条目 */
void set_idt_entry(uint8_t num, uint32_t handler);

/* IDT表（在idt.c中定义） */
extern idt_desc_t idt[NUM_IDT_ENTRIES];

#endif /* _IDT_H */
