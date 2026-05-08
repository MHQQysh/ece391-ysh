/* boot.S - 内核启动代码（修复版）
 * 这是GRUB加载内核后第一个执行的代码
 */

#define ASM     1
#include "multiboot.h"

/* Multiboot头 - 必须在文件开头的前8KB内 */
.section .multiboot
.align 4
multiboot_header:
    .long MULTIBOOT_HEADER_MAGIC    /* 魔数 */
    .long MULTIBOOT_HEADER_FLAGS    /* 标志 */
    .long -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)  /* 校验和 */




/* 内核入口点 */
.section .text
.globl _start
_start:
    /* 禁用中断 */
    cli

    /* 设置栈指针 - 内核需要栈来调用C函数 */
    movl $kernel_stack_top, %esp
    movl $kernel_stack_top, %ebp

    /* 重置EFLAGS寄存器 */
    pushl $0
    popf

    /* 将Multiboot信息传递给C代码 */
    /* EAX = 魔数, EBX = Multiboot信息结构地址 */
    pushl %ebx      /* 参数2: Multiboot信息地址 */
    pushl %eax      /* 参数1: 魔数 */

    /* 调用C语言的entry函数 */
    call entry

    /* 如果entry返回（不应该发生），进入死循环 */
halt:
    cli
    hlt
    jmp halt

/* 内核栈 - 16KB大小 */
.section .bss
.align 16
kernel_stack_bottom:
    .skip 16384     /* 16KB栈空间 */
kernel_stack_top:
