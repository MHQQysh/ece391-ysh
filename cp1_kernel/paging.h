/* paging.h - 分页机制定义 */

#ifndef _PAGING_H
#define _PAGING_H

#include "types.h"

/* 页大小 */
#define PAGE_SIZE       4096        /* 4KB */
#define PAGE_SIZE_4MB   0x400000    /* 4MB */

/* 页表/页目录条目数 */
#define NUM_PDE         1024        /* 页目录条目数 */
#define NUM_PTE         1024        /* 页表条目数 */

/* 内存地址 */
#define KERNEL_MEM      0x400000    /* 内核起始地址 4MB */
#define VIDEO_MEM_ADDR  0xB8000     /* 视频内存地址 */

/* 页目录条目（Page Directory Entry） */
typedef struct pde {
    uint32_t present        : 1;    /* 是否存在 */
    uint32_t read_write     : 1;    /* 读写权限 */
    uint32_t user_supervisor: 1;    /* 用户/内核 */
    uint32_t write_through  : 1;    /* 写穿透 */
    uint32_t cache_disabled : 1;    /* 禁用缓存 */
    uint32_t accessed       : 1;    /* 已访问 */
    uint32_t reserved       : 1;    /* 保留 */
    uint32_t page_size      : 1;    /* 页大小（0=4KB, 1=4MB） */
    uint32_t global         : 1;    /* 全局页 */
    uint32_t available      : 3;    /* 可用位 */
    uint32_t page_table_addr: 20;   /* 页表基地址（高20位） */
} __attribute__((packed)) pde_t;

/* 页表条目（Page Table Entry） */
typedef struct pte {
    uint32_t present        : 1;    /* 是否存在 */
    uint32_t read_write     : 1;    /* 读写权限 */
    uint32_t user_supervisor: 1;    /* 用户/内核 */
    uint32_t write_through  : 1;    /* 写穿透 */
    uint32_t cache_disabled : 1;    /* 禁用缓存 */
    uint32_t accessed       : 1;    /* 已访问 */
    uint32_t dirty          : 1;    /* 脏页 */
    uint32_t page_attr      : 1;    /* 页属性 */
    uint32_t global         : 1;    /* 全局页 */
    uint32_t available      : 3;    /* 可用位 */
    uint32_t page_base_addr : 20;   /* 页基地址（高20位） */
} __attribute__((packed)) pte_t;

/* 初始化分页 */
void init_paging(void);

/* 页目录和页表（在paging.c中定义） */
extern pde_t page_directory[NUM_PDE] __attribute__((aligned(PAGE_SIZE)));
extern pte_t page_table[NUM_PTE] __attribute__((aligned(PAGE_SIZE)));

#endif /* _PAGING_H */
