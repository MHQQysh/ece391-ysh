/* multiboot.h - Multiboot规范定义
 * Multiboot是GRUB使用的标准，用于加载操作系统内核
 */

#ifndef _MULTIBOOT_H
#define _MULTIBOOT_H

/* Multiboot头魔数 */
#define MULTIBOOT_HEADER_MAGIC      0x1BADB002

/* Multiboot头标志 */
#define MULTIBOOT_HEADER_FLAGS      0x00000003

/* Multiboot加载器传递的魔数 */
#define MULTIBOOT_BOOTLOADER_MAGIC  0x2BADB002

#ifndef ASM

/* Multiboot信息结构 */
typedef struct multiboot_info {
    unsigned long flags;        /* 哪些信息有效 */
    unsigned long mem_lower;    /* 低端内存大小（KB） */
    unsigned long mem_upper;    /* 高端内存大小（KB） */
    unsigned long boot_device;  /* 启动设备 */
    unsigned long cmdline;      /* 命令行参数 */
    unsigned long mods_count;   /* 模块数量 */
    unsigned long mods_addr;    /* 模块地址 */
    unsigned long syms[4];      /* 符号表信息 */
    unsigned long mmap_length;  /* 内存映射长度 */
    unsigned long mmap_addr;    /* 内存映射地址 */
} multiboot_info_t;

/* 模块结构 */
typedef struct module {
    unsigned long mod_start;    /* 模块起始地址 */
    unsigned long mod_end;      /* 模块结束地址 */
    unsigned long string;       /* 模块字符串 */
    unsigned long reserved;     /* 保留 */
} module_t;

/* 内存映射条目 */
typedef struct memory_map {
    unsigned long size;         /* 条目大小 */
    unsigned long base_addr_low;    /* 基地址低32位 */
    unsigned long base_addr_high;   /* 基地址高32位 */
    unsigned long length_low;       /* 长度低32位 */
    unsigned long length_high;      /* 长度高32位 */
    unsigned long type;         /* 类型（1=可用，其他=保留） */
} memory_map_t;

#endif /* ASM */

#endif /* _MULTIBOOT_H */
