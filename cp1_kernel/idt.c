/* idt.c - 中断描述符表实现 */

#include "idt.h"
#include "lib.h"
#include "exceptions.h"

/* IDT表 */
idt_desc_t idt[NUM_IDT_ENTRIES];

/* IDT指针 */
static idt_ptr_t idt_ptr;

/* set_idt_entry - 设置IDT条目
 * @num: 中断号
 * @handler: 处理函数地址
 */
void set_idt_entry(uint8_t num, uint32_t handler) {
    idt[num].offset_low = handler & 0xFFFF;
    idt[num].offset_high = (handler >> 16) & 0xFFFF;
    idt[num].seg_selector = KERNEL_CS;
    idt[num].reserved = 0;
    /* 类型: 0x8E = 1000 1110
     * P=1 (present), DPL=00 (ring 0), S=0 (system), Type=1110 (32-bit interrupt gate)
     */
    idt[num].type_attr = 0x8E;
}

/* idt_init - 初始化IDT */
void idt_init(void) {
    int i;

    /* 1. 清空IDT */
    for (i = 0; i < NUM_IDT_ENTRIES; i++) {
        idt[i].offset_low = 0;
        idt[i].offset_high = 0;
        idt[i].seg_selector = 0;
        idt[i].reserved = 0;
        idt[i].type_attr = 0;
    }

    /* 2. 设置异常处理函数（0-19是CPU异常） */
    set_idt_entry(0, (uint32_t)exception_0);   /* 除零错误 */
    set_idt_entry(1, (uint32_t)exception_1);   /* 调试异常 */
    set_idt_entry(2, (uint32_t)exception_2);   /* NMI */
    set_idt_entry(3, (uint32_t)exception_3);   /* 断点 */
    set_idt_entry(4, (uint32_t)exception_4);   /* 溢出 */
    set_idt_entry(5, (uint32_t)exception_5);   /* 越界 */
    set_idt_entry(6, (uint32_t)exception_6);   /* 无效操作码 */
    set_idt_entry(7, (uint32_t)exception_7);   /* 设备不可用 */
    set_idt_entry(8, (uint32_t)exception_8);   /* 双重错误 */
    set_idt_entry(9, (uint32_t)exception_9);   /* 协处理器段越界 */
    set_idt_entry(10, (uint32_t)exception_10); /* 无效TSS */
    set_idt_entry(11, (uint32_t)exception_11); /* 段不存在 */
    set_idt_entry(12, (uint32_t)exception_12); /* 栈段错误 */
    set_idt_entry(13, (uint32_t)exception_13); /* 一般保护错误 */
    set_idt_entry(14, (uint32_t)exception_14); /* 页错误 */
    set_idt_entry(15, (uint32_t)exception_15); /* 保留 */
    set_idt_entry(16, (uint32_t)exception_16); /* 浮点错误 */
    set_idt_entry(17, (uint32_t)exception_17); /* 对齐检查 */
    set_idt_entry(18, (uint32_t)exception_18); /* 机器检查 */
    set_idt_entry(19, (uint32_t)exception_19); /* SIMD浮点异常 */

    /* 3. 设置IDT指针 */
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;

    /* 4. 加载IDT */
    asm volatile ("lidt %0" : : "m"(idt_ptr));

    printf("IDT initialized!\n");
}
