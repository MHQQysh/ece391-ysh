/* linker.ld - 链接脚本（修复版）
 * 确保Multiboot头在正确的位置并被加载
 */

OUTPUT_FORMAT("elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)

SECTIONS
{
    /* 内核加载到1MB地址（Multiboot标准） */
    . = 0x00100000;

    /* Multiboot头和代码段放在一起 */
    .text : ALIGN(4K) {
        *(.multiboot)
        *(.text)
    }

    /* 只读数据段 */
    .rodata : ALIGN(4K) {
        *(.rodata)
    }

    /* 数据段 */
    .data : ALIGN(4K) {
        *(.data)
    }

    /* BSS段（未初始化数据） */
    .bss : ALIGN(4K) {
        *(COMMON)
        *(.bss)
    }
}
