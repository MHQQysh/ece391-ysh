# ECE391 环境安装步骤

## 当前状态
✅ WSL2 已安装 (Ubuntu 22.04)
✅ WSL 网络已修复 (改为NAT模式)
✅ GCC 已安装
❌ QEMU 需要安装
❌ NASM 需要安装
❌ 其他工具需要安装

## 手动安装步骤（推荐）

### 1. 打开 WSL Ubuntu 终端

在 PowerShell 中运行：
```powershell
wsl -d Ubuntu-22.04
```

或者从开始菜单搜索 "Ubuntu" 并打开。

### 2. 更新包管理器

```bash
sudo apt update
```

### 3. 安装所有开发工具（一条命令）

```bash
sudo apt install -y build-essential qemu-system-x86 gdb nasm gcc-multilib g++-multilib git
```

这个命令会安装：
- `build-essential`: GCC编译器和基本工具
- `qemu-system-x86`: QEMU虚拟机（用于运行操作系统）
- `gdb`: GNU调试器
- `nasm`: 汇编器
- `gcc-multilib`, `g++-multilib`: 32位编译支持
- `git`: 版本控制

**预计时间**: 5-10分钟（取决于网速）

### 4. 验证安装

安装完成后，运行验证脚本：

```bash
cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa
bash verify_environment.sh
```

应该看到所有工具都显示 ✅

### 5. 测试 QEMU GUI

```bash
qemu-system-i386 -display gtk
```

**预期结果**: 应该弹出一个QEMU窗口（黑屏或BIOS信息）

如果看到窗口 = 成功！按 Ctrl+Alt+Q 退出。

### 6. 运行你的操作系统！

```bash
cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa
bash run_os.sh
```

或者手动运行：

```bash
cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa/uiuc-ece391-mp3/student-distrib
qemu-system-i386 -hda mp3.img -m 512 -vga std
```

**预期结果**:
- 弹出 QEMU 窗口
- 看到操作系统启动画面
- 可以输入命令：`ls`, `cat`, `help`
- 看到彩色界面和中文字符支持

## 常见问题

### Q: apt install 卡住不动？

A: 按 Ctrl+C 取消，然后重试：
```bash
sudo killall apt apt-get
sudo rm /var/lib/dpkg/lock-frontend
sudo apt install -y qemu-system-x86 nasm gdb gcc-multilib g++-multilib
```

### Q: QEMU 窗口不弹出？

A: 检查 DISPLAY 环境变量：
```bash
echo $DISPLAY
```

如果为空，重启 WSL：
```powershell
# 在 PowerShell 中运行
wsl --shutdown
wsl
```

### Q: 编译错误 "cannot find -lc"？

A: 安装 32 位库：
```bash
sudo apt install gcc-multilib g++-multilib
```

## 快速命令参考

```bash
# 进入项目目录
cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa/uiuc-ece391-mp3/student-distrib

# 编译项目（如果需要修改代码）
make clean
make dep
make

# 运行操作系统
qemu-system-i386 -hda mp3.img -m 512 -vga std

# 带调试运行
qemu-system-i386 -hda mp3.img -m 512 -vga std -gdb tcp::1234 -S
# 在另一个终端运行: gdb
```

## 成功标志

✅ 所有命令都能找到（which qemu-system-i386 等）
✅ QEMU 能弹出窗口
✅ 能看到操作系统界面
✅ 能用键盘输入命令并看到响应

完成这些步骤后，你的环境就完全配置好了！
