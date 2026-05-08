# CP1 - 内核初始化

这是ECE391操作系统课程的Checkpoint 1（CP1）实现，包含了一个能够启动的最小内核。

## 🎯 实现的功能

### ✅ 已完成
1. **启动流程**
   - GRUB引导加载
   - 从boot.S启动
   - 跳转到C语言kernel.c

2. **内存管理**
   - 分页机制（Paging）
   - 页目录和页表设置
   - 0-4MB使用4KB页表
   - 4-8MB使用4MB大页（内核）

3. **中断处理**
   - IDT（中断描述符表）初始化
   - 20个CPU异常处理
   - 异常信息显示

4. **基础功能**
   - VGA文本模式显示
   - printf函数（支持%s, %d, %x）
   - 屏幕清空和滚动

## 📁 文件结构

```
cp1_kernel/
├── boot.S              # 启动代码（汇编）
├── kernel.c            # 内核主文件
├── lib.c/h             # 基础库函数
├── types.h             # 类型定义
├── multiboot.h         # Multiboot规范
├── paging.c/h          # 分页机制
├── idt.c/h             # 中断描述符表
├── exceptions.c/h      # 异常处理
├── exception_wrap.S    # 异常处理包装
├── x86_desc.S/h        # GDT定义
├── Makefile            # 编译配置
└── README.md           # 本文件
```

**总计：15个文件，约1500行代码**

## 🔧 编译和运行

### 前置要求

在WSL中安装：
```bash
sudo apt update
sudo apt install -y gcc-multilib qemu-system-x86
```

### 编译

```bash
cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa/cp1_kernel
make
```

### 运行

```bash
# 方法1：使用Makefile
make run

# 方法2：直接运行QEMU
qemu-system-i386 -kernel bootimg -m 512
```

### 调试

```bash
# 终端1：启动QEMU并等待GDB
make debug

# 终端2：启动GDB
gdb
(gdb) target remote :1234
(gdb) break entry
(gdb) continue
```

## 📚 核心概念详解

### 1. 启动流程

```
开机 → BIOS → GRUB → boot.S → kernel.c
```

**boot.S做了什么？**
1. 设置Multiboot头（让GRUB识别）
2. 设置栈指针（ESP）
3. 传递Multiboot信息给C代码
4. 调用entry()函数

### 2. 分页机制

**为什么需要分页？**
- 保护内核不被破坏
- 每个程序有独立地址空间
- 实现虚拟内存

**内存布局：**
```
虚拟地址          物理地址          映射方式
0x00000000        0x00000000        4KB页表（包含视频内存）
  - 0x003FFFFF
0x00400000        0x00400000        4MB大页（内核代码）
  - 0x007FFFFF
```

**关键代码：**
```c
// 1. 创建页表（映射0-4MB）
for (i = 0; i < 1024; i++) {
    page_table[i].present = 1;
    page_table[i].page_base_addr = i;  // 物理地址 = i * 4KB
}

// 2. 页目录第0项指向页表
page_directory[0].page_table_addr = page_table >> 12;

// 3. 页目录第1项使用4MB大页
page_directory[1].page_size = 1;
page_directory[1].page_table_addr = 0x400000 >> 12;

// 4. 加载页目录到CR3
asm("movl %0, %%cr3" : : "r"(page_directory));

// 5. 启用分页（设置CR0的PG位）
asm("movl %%cr0, %%eax; orl $0x80000000, %%eax; movl %%eax, %%cr0");
```

### 3. 中断描述符表（IDT）

**作用：** 告诉CPU发生异常时跳转到哪里

**IDT条目结构：**
```c
struct idt_desc {
    uint16_t offset_low;    // 处理函数地址低16位
    uint16_t seg_selector;  // 段选择子（0x0010 = 内核代码段）
    uint8_t  reserved;      // 必须为0
    uint8_t  type_attr;     // 0x8E = 中断门
    uint16_t offset_high;   // 处理函数地址高16位
};
```

**异常处理流程：**
```
1. CPU发生异常（如除零）
2. CPU查IDT表，找到对应处理函数
3. 跳转到exception_wrap.S中的exception_0
4. 保存寄存器
5. 调用C函数handle_exception(0)
6. 显示异常信息
7. 停止系统
```

### 4. GDT（全局描述符表）

**作用：** 定义内存段

**段定义：**
- 0x08: 内核代码段
- 0x10: 内核数据段
- 0x18: 用户代码段
- 0x20: 用户数据段

## 🧪 测试

### 测试1：正常启动

运行后应该看到：
```
========================================
   ECE391 Operating System - CP1
========================================

Multiboot magic number verified!
Memory: Lower=639KB, Upper=130048KB

Initializing IDT...
IDT initialized!
Initializing paging...
Paging enabled!

========================================
Kernel initialization complete!
========================================

System is running...
Press Ctrl+Alt+Q to exit QEMU
```

### 测试2：异常处理

在kernel.c中取消注释这行：
```c
int x = 1 / 0;  /* 触发除零异常 */
```

重新编译运行，应该看到：
```
========================================
        EXCEPTION OCCURRED!
========================================

Exception #0: Division By Zero

System Halted.
```

## 📊 代码统计

| 模块 | 文件 | 行数 | 说明 |
|------|------|------|------|
| 启动 | boot.S | ~50 | 汇编启动代码 |
| 内核 | kernel.c | ~80 | 主入口 |
| 库函数 | lib.c/h | ~200 | printf等 |
| 分页 | paging.c/h | ~150 | 内存管理 |
| 中断 | idt.c/h | ~100 | IDT初始化 |
| 异常 | exceptions.c/h | ~80 | 异常处理 |
| 异常包装 | exception_wrap.S | ~60 | 汇编包装 |
| GDT | x86_desc.S/h | ~80 | 段描述符 |
| 其他 | types.h, multiboot.h | ~100 | 定义 |
| **总计** | **15个文件** | **~900行** | |

## 🎓 学习要点

### 关键概念

1. **Multiboot规范**
   - 让GRUB能识别和加载内核
   - 传递内存信息给内核

2. **保护模式**
   - 32位地址空间
   - 分段和分页
   - 特权级别（Ring 0-3）

3. **虚拟内存**
   - 虚拟地址 → 物理地址
   - 页目录 + 页表
   - 4KB页和4MB页

4. **中断机制**
   - IDT表
   - 中断门
   - 异常处理

### 调试技巧

1. **使用printf**
   ```c
   printf("Debug: value = %d\n", x);
   ```

2. **使用GDB**
   ```bash
   make debug
   # 另一个终端
   gdb
   (gdb) target remote :1234
   (gdb) break entry
   (gdb) continue
   (gdb) print mbi->mem_lower
   ```

3. **查看内存**
   ```bash
   (gdb) x/10x 0xB8000  # 查看视频内存
   (gdb) x/10x page_directory  # 查看页目录
   ```

## 🚀 下一步（CP2）

CP1完成后，下一步是：
1. 添加键盘驱动
2. 添加RTC（实时时钟）
3. 添加PIC（中断控制器）
4. 实现基本的设备驱动框架

## ⚠️ 常见问题

### Q1: 编译错误 "cannot find -lgcc"
```bash
sudo apt install gcc-multilib
```

### Q2: QEMU窗口不弹出
```bash
# 检查DISPLAY
echo $DISPLAY
# 如果为空，重启WSL
wsl --shutdown
wsl
```

### Q3: 屏幕显示乱码
- 检查视频内存地址是否正确（0xB8000）
- 检查分页是否正确映射了视频内存

### Q4: 系统立即重启
- 可能是三重错误（Triple Fault）
- 检查IDT是否正确初始化
- 检查分页是否正确设置

## 📖 参考资料

- [OSDev Wiki](https://wiki.osdev.org/)
- [Intel 80386 Programmer's Reference Manual](https://pdos.csail.mit.edu/6.828/2018/readings/i386.pdf)
- [Multiboot Specification](https://www.gnu.org/software/grub/manual/multiboot/multiboot.html)

---

**创建日期**: 2026-05-08  
**状态**: CP1完成，可编译运行  
**下一步**: CP2 - 设备驱动
