/* paging.c - 分页机制实现 */

#include "paging.h"
#include "lib.h"

/* 页目录 - 必须4KB对齐 */
pde_t page_directory[NUM_PDE] __attribute__((aligned(PAGE_SIZE)));

/* 页表 - 用于映射前4MB内存（包含视频内存） */
pte_t page_table[NUM_PTE] __attribute__((aligned(PAGE_SIZE)));

/* init_paging - 初始化分页机制
 *
 * 内存布局：
 * 0-4MB:    使用4KB页表映射（包含视频内存0xB8000）
 * 4-8MB:    使用4MB大页直接映射（内核代码）
 * 其他:     未映射
 */
void init_paging(void) {
    int i;

    /* 1. 初始化页目录 - 全部清零 */
    for (i = 0; i < NUM_PDE; i++) {
        page_directory[i].present = 0;
        page_directory[i].read_write = 0;
        page_directory[i].user_supervisor = 0;
        page_directory[i].write_through = 0;
        page_directory[i].cache_disabled = 0;
        page_directory[i].accessed = 0;
        page_directory[i].reserved = 0;
        page_directory[i].page_size = 0;
        page_directory[i].global = 0;
        page_directory[i].available = 0;
        page_directory[i].page_table_addr = 0;
    }

    /* 2. 初始化页表 - 映射前4MB内存 */
    for (i = 0; i < NUM_PTE; i++) {
        page_table[i].present = 1;              /* 页存在 */
        page_table[i].read_write = 1;           /* 可读写 */
        page_table[i].user_supervisor = 0;      /* 内核模式 */
        page_table[i].write_through = 0;
        page_table[i].cache_disabled = 0;
        page_table[i].accessed = 0;
        page_table[i].dirty = 0;
        page_table[i].page_attr = 0;
        page_table[i].global = 0;
        page_table[i].available = 0;
        page_table[i].page_base_addr = i;       /* 物理地址 = i * 4KB */
    }

    /* 3. 设置页目录第0项 - 指向页表（映射0-4MB） */
    page_directory[0].present = 1;
    page_directory[0].read_write = 1;
    page_directory[0].user_supervisor = 0;
    page_directory[0].page_size = 0;            /* 使用4KB页 */
    page_directory[0].page_table_addr = ((uint32_t)page_table) >> 12;

    /* 4. 设置页目录第1项 - 4MB大页映射内核（4-8MB） */
    page_directory[1].present = 1;
    page_directory[1].read_write = 1;
    page_directory[1].user_supervisor = 0;
    page_directory[1].page_size = 1;            /* 使用4MB大页 */
    page_directory[1].page_table_addr = KERNEL_MEM >> 12;

    /* 5. 加载页目录到CR3寄存器 */
    asm volatile (
        "movl %0, %%eax         \n"
        "movl %%eax, %%cr3      \n"
        : : "r"(page_directory)
        : "eax"
    );

    /* 6. 启用分页 - 设置CR0的PG位 */
    asm volatile (
        "movl %%cr0, %%eax      \n"
        "orl $0x80000000, %%eax \n"  /* 设置PG位（第31位） */
        "movl %%eax, %%cr0      \n"
        : : : "eax"
    );

    printf("Paging enabled!\n");
}
