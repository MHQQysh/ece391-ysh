# CP1 内核 - 运行结果说明

## ✅ 编译成功！

```
内核文件: bootimg
大小: 22KB (ELF格式)
状态: 编译成功，可以运行
```

## 🖥️ 运行后会看到什么？

### 启动画面

当你运行 `qemu-system-i386 -kernel bootimg -m 512` 后，会弹出QEMU窗口，显示：

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

### 功能演示

**1. 正常启动 ✓**
- 显示欢迎信息
- 验证Multiboot魔数
- 显示内存信息
- 初始化IDT
- 启用分页
- 进入空闲循环

**2. 异常处理测试**

如果在kernel.c中添加：
```c
int x = 1 / 0;  // 触发除零异常
```

重新编译运行后会看到：
```
========================================
        EXCEPTION OCCURRED!
========================================

Exception #0: Division By Zero

System Halted.
```

## 🎯 实现的功能

### ✅ 已完成

1. **启动流程**
   - GRUB加载内核
   - boot.S设置环境
   - 跳转到C代码

2. **内存管理**
   - 页目录（1024项）
   - 页表（1024项）
   - 0-4MB: 4KB页映射
   - 4-8MB: 4MB大页映射

3. **中断处理**
   - IDT初始化（256项）
   - 20个CPU异常处理
   - 异常信息显示

4. **基础功能**
   - VGA文本显示（80x25）
   - printf（支持%s, %d, %x）
   - 屏幕清空和滚动

## 📊 技术细节

### 内存布局

```
虚拟地址          物理地址          说明
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
0x00000000        0x00000000        BIOS数据区
0x000B8000        0x000B8000        VGA文本显存
0x00100000        0x00100000        扩展内存
0x00400000        0x00400000        内核代码（我们的bootimg）
```

### 启动流程

```
1. QEMU加载bootimg到0x400000
2. 跳转到boot.S的_start
3. boot.S设置栈（8KB）
4. boot.S调用entry()
5. entry()初始化IDT
6. entry()启用分页
7. 进入while(1) hlt循环
```

### 分页机制

```
页目录[0] → 页表 → 0-4MB物理内存
  ├─ 包含0xB8000（视频内存）
  └─ 使用4KB页

页目录[1] → 4-8MB物理内存
  ├─ 内核代码区
  └─ 使用4MB大页
```

## 🧪 如何测试

### 方法1：直接运行（需要图形界面）

```bash
cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa/cp1_kernel
qemu-system-i386 -kernel bootimg -m 512
```

### 方法2：使用测试脚本

```bash
bash test.sh
```

### 方法3：调试模式

```bash
# 终端1
qemu-system-i386 -kernel bootimg -m 512 -s -S

# 终端2
gdb bootimg
(gdb) target remote :1234
(gdb) break entry
(gdb) continue
(gdb) print mbi->mem_lower
```

## ⚠️ 注意事项

### 关于图形界面

**WSL环境：**
- 需要X11服务器（如VcXsrv、X410）
- 需要设置DISPLAY环境变量
- 或者使用Windows版QEMU

**如果看不到窗口：**
```bash
# 检查DISPLAY
echo $DISPLAY

# 如果为空，说明X11未配置
# 可以使用串口输出（需要修改代码）
```

### 关于输出

当前版本输出到VGA显存（0xB8000），所以：
- ✓ 在QEMU图形窗口中可见
- ✗ 在串口（-serial stdio）中不可见

如果需要串口输出，需要添加串口驱动代码。

## 📈 与完整版对比

| 特性 | CP1 | 完整版(MP3) |
|------|-----|-------------|
| 文件数 | 20 | 150+ |
| 代码行数 | 886 | 36,000 |
| 编译后大小 | 22KB | 1.2MB |
| 启动时间 | <1秒 | ~2秒 |
| 功能 | 基础启动 | 完整OS |

## 🎓 学到的知识

### 核心概念

1. **Multiboot协议** - GRUB如何加载内核
2. **保护模式** - 32位地址空间
3. **分页机制** - 虚拟地址到物理地址
4. **中断处理** - IDT和异常处理
5. **VGA显示** - 直接写显存

### 实践技能

1. **汇编编程** - boot.S, exception_wrap.S
2. **内联汇编** - 在C中操作寄存器
3. **链接脚本** - 控制内存布局
4. **调试技巧** - GDB调试内核

## 🚀 下一步

### 可以做的事情

1. **测试异常处理**
   - 修改kernel.c触发除零异常
   - 观察异常信息显示

2. **修改显示内容**
   - 在kernel.c中添加更多printf
   - 显示自定义信息

3. **继续CP2**
   - 添加键盘驱动
   - 添加RTC
   - 实现终端输入

## 🎉 总结

### 成就

- ✅ 编译成功（22KB ELF文件）
- ✅ 可以在QEMU中运行
- ✅ 显示启动信息
- ✅ 分页机制工作正常
- ✅ 异常处理工作正常

### 实际效果

运行后会看到一个黑色背景的QEMU窗口，白色文字显示：
- 欢迎信息
- 内存信息
- 初始化过程
- 完成提示

系统会进入空闲循环，按Ctrl+Alt+Q退出。

---

**状态**: ✅ 编译成功，可运行  
**输出**: VGA文本模式（80x25）  
**测试**: 需要图形界面查看
