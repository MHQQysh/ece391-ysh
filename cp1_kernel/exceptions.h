/* exceptions.h - 异常处理声明 */

#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

/* 异常处理函数（在exception_wrap.S中定义） */
extern void exception_0(void);   /* 除零错误 */
extern void exception_1(void);   /* 调试异常 */
extern void exception_2(void);   /* NMI */
extern void exception_3(void);   /* 断点 */
extern void exception_4(void);   /* 溢出 */
extern void exception_5(void);   /* 越界 */
extern void exception_6(void);   /* 无效操作码 */
extern void exception_7(void);   /* 设备不可用 */
extern void exception_8(void);   /* 双重错误 */
extern void exception_9(void);   /* 协处理器段越界 */
extern void exception_10(void);  /* 无效TSS */
extern void exception_11(void);  /* 段不存在 */
extern void exception_12(void);  /* 栈段错误 */
extern void exception_13(void);  /* 一般保护错误 */
extern void exception_14(void);  /* 页错误 */
extern void exception_15(void);  /* 保留 */
extern void exception_16(void);  /* 浮点错误 */
extern void exception_17(void);  /* 对齐检查 */
extern void exception_18(void);  /* 机器检查 */
extern void exception_19(void);  /* SIMD浮点异常 */

/* C语言异常处理函数 */
void handle_exception(int exception_num);

#endif /* _EXCEPTIONS_H */
