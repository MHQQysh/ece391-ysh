/* x86_desc.S - x86描述符表（汇编）
 * 定义GDT（全局描述符表）
 */

.data

/* GDT表 */
.align 4
.globl gdt
gdt:
    /* 空描述符 */
    .quad 0

    /* 内核代码段 (0x08) */
    .word 0xFFFF        /* 段界限 0-15位 */
    .word 0x0000        /* 基地址 0-15位 */
    .byte 0x00          /* 基地址 16-23位 */
    .byte 0x9A          /* 访问权限: P=1, DPL=00, S=1, Type=1010 (代码段) */
    .byte 0xCF          /* 粒度: G=1, D=1, 段界限16-19位=1111 */
    .byte 0x00          /* 基地址 24-31位 */

    /* 内核数据段 (0x10) */
    .word 0xFFFF        /* 段界限 0-15位 */
    .word 0x0000        /* 基地址 0-15位 */
    .byte 0x00          /* 基地址 16-23位 */
    .byte 0x92          /* 访问权限: P=1, DPL=00, S=1, Type=0010 (数据段) */
    .byte 0xCF          /* 粒度: G=1, D=1, 段界限16-19位=1111 */
    .byte 0x00          /* 基地址 24-31位 */

    /* 用户代码段 (0x18) */
    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0xFA          /* 访问权限: P=1, DPL=11, S=1, Type=1010 */
    .byte 0xCF
    .byte 0x00

    /* 用户数据段 (0x20) */
    .word 0xFFFF
    .word 0x0000
    .byte 0x00
    .byte 0xF2          /* 访问权限: P=1, DPL=11, S=1, Type=0010 */
    .byte 0xCF
    .byte 0x00

gdt_end:

/* GDT指针 */
.globl gdt_ptr
gdt_ptr:
    .word gdt_end - gdt - 1     /* GDT大小-1 */
    .long gdt                   /* GDT基地址 */

.text

/* load_gdt - 加载GDT */
.globl load_gdt
load_gdt:
    lgdt gdt_ptr        /* 加载GDT */

    /* 重新加载段寄存器 */
    movw $0x10, %ax     /* 内核数据段选择子 */
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    /* 通过长跳转重新加载CS */
    ljmp $0x08, $reload_cs

reload_cs:
    ret
