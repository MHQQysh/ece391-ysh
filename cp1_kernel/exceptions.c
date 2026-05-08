/* exceptions.c - 异常处理实现 */

#include "exceptions.h"
#include "lib.h"

/* 异常名称 */
static const char* exception_names[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception"
};

/* handle_exception - 处理异常
 * @exception_num: 异常号
 */
void handle_exception(int exception_num) {
    /* 清屏并显示异常信息 */
    clear();
    printf("\n");
    printf("========================================\n");
    printf("        EXCEPTION OCCURRED!\n");
    printf("========================================\n");
    printf("\n");

    if (exception_num >= 0 && exception_num < 20) {
        printf("Exception #%d: %s\n", exception_num, exception_names[exception_num]);
    } else {
        printf("Unknown Exception #%d\n", exception_num);
    }

    printf("\n");
    printf("System Halted.\n");

    /* 停止系统 */
    while(1) {
        asm volatile("hlt");
    }
}
