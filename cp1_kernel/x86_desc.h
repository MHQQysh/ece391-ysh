/* x86_desc.h - x86描述符表定义
 * 包含GDT（全局描述符表）的定义
 */

#ifndef _X86_DESC_H
#define _X86_DESC_H

#include "types.h"

/* GDT条目结构 */
typedef struct gdt_desc {
    uint16_t limit_low;         /* 段界限低16位 */
    uint16_t base_low;          /* 基地址低16位 */
    uint8_t  base_mid;          /* 基地址中8位 */
    uint8_t  access;            /* 访问权限 */
    uint8_t  granularity;       /* 粒度和段界限高4位 */
    uint8_t  base_high;         /* 基地址高8位 */
} __attribute__((packed)) gdt_desc_t;

/* GDT指针结构 */
typedef struct gdt_ptr {
    uint16_t limit;             /* GDT大小-1 */
    uint32_t base;              /* GDT基地址 */
} __attribute__((packed)) gdt_ptr_t;

/* GDT表（在x86_desc.S中定义） */
extern gdt_desc_t gdt[];
extern gdt_ptr_t gdt_ptr;

/* 加载GDT（在x86_desc.S中定义） */
extern void load_gdt(void);

#endif /* _X86_DESC_H */
