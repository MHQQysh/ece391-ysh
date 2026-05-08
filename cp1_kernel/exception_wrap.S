/* exception_wrap.S - 异常处理包装（汇编）
 * 这些函数是IDT中注册的处理函数
 * 它们保存寄存器，调用C函数，然后恢复寄存器
 */

.text

/* 宏：定义异常处理函数 */
#define EXCEPTION_HANDLER(num) \
.globl exception_##num;        \
exception_##num:               \
    pushl $##num;              \
    jmp exception_common

/* 定义所有异常处理函数 */
EXCEPTION_HANDLER(0)
EXCEPTION_HANDLER(1)
EXCEPTION_HANDLER(2)
EXCEPTION_HANDLER(3)
EXCEPTION_HANDLER(4)
EXCEPTION_HANDLER(5)
EXCEPTION_HANDLER(6)
EXCEPTION_HANDLER(7)
EXCEPTION_HANDLER(8)
EXCEPTION_HANDLER(9)
EXCEPTION_HANDLER(10)
EXCEPTION_HANDLER(11)
EXCEPTION_HANDLER(12)
EXCEPTION_HANDLER(13)
EXCEPTION_HANDLER(14)
EXCEPTION_HANDLER(15)
EXCEPTION_HANDLER(16)
EXCEPTION_HANDLER(17)
EXCEPTION_HANDLER(18)
EXCEPTION_HANDLER(19)

/* 通用异常处理 */
exception_common:
    /* 保存所有寄存器 */
    pushl %eax
    pushl %ecx
    pushl %edx
    pushl %ebx
    pushl %esp
    pushl %ebp
    pushl %esi
    pushl %edi

    /* 调用C函数 handle_exception */
    /* 异常号已经在栈上了 */
    call handle_exception

    /* 恢复寄存器（实际上不会执行到这里，因为handle_exception会halt） */
    popl %edi
    popl %esi
    popl %ebp
    popl %esp
    popl %ebx
    popl %edx
    popl %ecx
    popl %eax

    /* 弹出异常号 */
    addl $4, %esp

    /* 返回 */
    iret
