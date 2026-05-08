# 最简单的安装方法

## 问题分析

自动安装脚本在后台运行时可能会卡在需要交互的步骤上。最可靠的方法是在交互式终端中手动运行命令。

## 推荐方法：手动安装（5分钟）

### 步骤1：打开WSL终端

在PowerShell中运行：
```powershell
wsl -d Ubuntu-22.04
```

或者从Windows开始菜单搜索"Ubuntu"并打开。

### 步骤2：运行一条命令安装所有工具

在WSL终端中复制粘贴这条命令：

```bash
sudo apt update && sudo apt install -y qemu-system-x86 nasm gdb gcc-multilib g++-multilib
```

**说明**：
- 这会更新包列表并安装所有需要的工具
- 可能需要输入你的Ubuntu密码
- 安装过程需要5-10分钟，你会看到实时进度
- 如果提示确认，输入 `Y` 并回车

### 步骤3：验证安装

安装完成后，运行：

```bash
qemu-system-i386 --version
```

如果看到版本号（例如 "QEMU emulator version 6.2.0"），说明安装成功！

### 步骤4：运行你的操作系统

```bash
cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa/uiuc-ece391-mp3/student-distrib
qemu-system-i386 -hda mp3.img -m 512 -vga std
```

**预期结果**：
- 弹出QEMU窗口
- 看到操作系统启动画面
- 可以输入命令测试（`ls`, `cat`, `help`）
- 按 `Ctrl+Alt+Q` 退出

## 如果遇到问题

### 问题1：apt被锁定

```bash
sudo killall apt apt-get dpkg
sudo rm /var/lib/dpkg/lock-frontend
sudo apt update
```

### 问题2：dpkg配置卡住

```bash
# 跳过配置，直接安装
sudo apt install -y --fix-broken qemu-system-x86
```

### 问题3：网络问题

```bash
# 测试网络
ping -c 2 8.8.8.8

# 如果失败，在PowerShell中重启WSL
wsl --shutdown
wsl
```

## 快速测试命令

安装完成后，用这个命令快速测试：

```bash
cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa
bash run_os.sh
```

## 为什么手动安装更好？

1. ✅ 可以看到实时进度
2. ✅ 可以处理交互提示
3. ✅ 可以立即看到错误信息
4. ✅ 不会因为后台运行而卡住

## 需要帮助？

如果安装过程中遇到任何错误信息，把错误信息发给我，我会帮你解决！

---

**预计总时间**：5-10分钟
**难度**：⭐ 非常简单（只需要复制粘贴一条命令）
