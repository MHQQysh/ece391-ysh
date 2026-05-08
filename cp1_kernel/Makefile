# Makefile for CP1 Kernel

# 编译器和标志
CC = gcc
AS = gcc
LD = ld

# 32位编译标志
CFLAGS = -m32 -Wall -fno-builtin -fno-stack-protector -nostdlib -nostdinc -fno-pic -g
ASFLAGS = -m32
LDFLAGS = -melf_i386 -T linker.ld

# 源文件
C_SOURCES = kernel.c lib.c paging.c idt.c exceptions.c
ASM_SOURCES = boot.S x86_desc.S exception_wrap.S

# 目标文件
C_OBJS = $(C_SOURCES:.c=.o)
ASM_OBJS = $(ASM_SOURCES:.S=.o)
OBJS = $(ASM_OBJS) $(C_OBJS)

# 最终内核文件
KERNEL = bootimg

# 默认目标
all: $(KERNEL)

# 链接生成内核
$(KERNEL): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^
	@echo "Kernel built successfully!"
	@ls -lh $(KERNEL)

# 编译C文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 编译汇编文件
%.o: %.S
	$(AS) $(ASFLAGS) -c $< -o $@

# 清理
clean:
	rm -f $(OBJS) $(KERNEL)
	@echo "Cleaned!"

# 运行（需要QEMU）
run: $(KERNEL)
	qemu-system-i386 -kernel $(KERNEL) -m 512

# 调试
debug: $(KERNEL)
	qemu-system-i386 -kernel $(KERNEL) -m 512 -s -S

.PHONY: all clean run debug
