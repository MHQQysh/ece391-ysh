/* kernel.c - 内核主文件（CP1版本）
 * 这是内核的C语言入口点
 */

#include "multiboot.h"
#include "lib.h"
#include "paging.h"
#include "idt.h"

/* entry - 内核入口函数
 * @magic: Multiboot魔数
 * @addr: Multiboot信息结构地址
 */
void entry(unsigned long magic, unsigned long addr) {
    multiboot_info_t *mbi;

    /* 清屏 */
    clear();

    /* 显示欢迎信息 */
    printf("========================================\n");
    printf("   ECE391 Operating System - CP1\n");
    printf("========================================\n");
    printf("\n");

    /* 检查Multiboot魔数 */
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("ERROR: Invalid magic number: 0x%x\n", (unsigned)magic);
        printf("Expected: 0x%x\n", MULTIBOOT_BOOTLOADER_MAGIC);
        while(1);
    }
    printf("Multiboot magic number verified!\n");

    /* 获取Multiboot信息 */
    mbi = (multiboot_info_t *)addr;

    /* 显示内存信息 */
    if (mbi->flags & 0x01) {
        printf("Memory: Lower=%dKB, Upper=%dKB\n",
               mbi->mem_lower, mbi->mem_upper);
    }

    /* 初始化IDT */
    printf("\nInitializing IDT...\n");
    idt_init();

    /* 初始化分页 */
    printf("Initializing paging...\n");
    init_paging();

    /* 完成初始化 */
    printf("\n========================================\n");
    printf("Kernel initialization complete!\n");
    printf("========================================\n");
    printf("\n");

    /* 测试：故意触发除零异常（可选） */
    printf("System is running...\n");
    printf("Press Ctrl+Alt+Q to exit QEMU\n");
    printf("\n");

    /* 可以取消注释下面这行来测试异常处理 */
    /* int x = 1 / 0; */

    /* 进入空闲循环 */
    while(1) {
        asm volatile("hlt");  /* 停止CPU直到下一个中断 */
    }
}
