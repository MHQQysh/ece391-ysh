# ECE 391 环境搭建与验证指南

## 第一步：安装WSL2（如果还没装）

在PowerShell（管理员模式）中运行：

```powershell
# 安装WSL2和Ubuntu
wsl --install -d Ubuntu-22.04

# 重启电脑后，设置Ubuntu用户名和密码
```

## 第二步：在WSL中安装开发工具

打开Ubuntu（从开始菜单或运行`wsl`命令），然后执行：

```bash
# 更新包管理器
sudo apt update && sudo apt upgrade -y

# 安装必需工具
sudo apt install -y build-essential
sudo apt install -y qemu-system-x86
sudo apt install -y gdb
sudo apt install -y nasm
sudo apt install -y gcc-multilib g++-multilib
sudo apt install -y git

# 验证安装
qemu-system-i386 --version
gcc --version
nasm --version
```

## 第三步：访问Windows文件系统

在WSL中，你的Windows文件在`/mnt/c/`下：

```bash
# 进入项目目录
cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa
```

## 第四步：验证环境 - 编译MP1

```bash
cd mp1
make clean
make

# 如果编译成功，说明工具链正常
```

## 第五步：验证可视化 - 运行QEMU测试

创建一个简单的测试：

```bash
# 测试QEMU是否能弹出窗口
qemu-system-i386 -display gtk
```

**预期结果：**
- 应该弹出一个QEMU窗口（黑屏或显示BIOS信息）
- 如果看到窗口，说明GUI支持正常！

## 第六步：运行MP3操作系统（终极验证）

```bash
cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa/uiuc-ece391-mp3/student-distrib

# 运行操作系统
qemu-system-i386 -hda mp3.img -m 512 -vga std
```

**预期结果：**
- 弹出QEMU窗口
- 看到操作系统启动画面
- 可以输入命令（如`ls`, `cat`, `help`）
- 能看到彩色界面和中文字符

## 常见问题排查

### 问题1：QEMU窗口不弹出

```bash
# 检查WSLg是否运行
echo $DISPLAY
# 应该输出类似 :0 或 :1

# 如果没有输出，重启WSL
# 在PowerShell中运行：
wsl --shutdown
wsl
```

### 问题2：编译错误 "cannot find -lc"

```bash
# 安装32位库支持
sudo apt install gcc-multilib g++-multilib
```

### 问题3：权限问题

```bash
# 确保文件有执行权限
chmod +x createfs elfconvert
```

## 成功标志

✅ **环境搭建成功的标志：**
1. `make`命令能成功编译代码
2. QEMU能弹出可视化窗口
3. 能在QEMU窗口中看到操作系统界面
4. 能用键盘输入命令并看到响应

## 下一步

环境验证成功后，你可以：
1. 阅读MP0的PDF，了解作业要求
2. 从MP1开始实际编程
3. 使用GDB调试：`qemu-system-i386 -s -S -hda mp3.img`（在另一个终端运行`gdb`连接）
