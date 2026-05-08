# ECE391 快速参考指南

## 项目结构

```
ECE391_UIUC22fa/
├── mp0/              # Machine Problem 0
├── mp1/              # Machine Problem 1 - Missile Command游戏
├── mp2/              # Machine Problem 2
├── mp3/              # Machine Problem 3 - 基础OS
├── uiuc-ece391-mp3/  # 完整的操作系统项目（主要项目）
│   └── student-distrib/
│       ├── mp3.img   # 操作系统镜像（8MB）
│       └── Makefile  # 编译配置
├── ps1/              # Problem Set 1
└── ps2/              # Problem Set 2
```

## 常用命令

### 启动操作系统
```bash
cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa
bash run_os.sh
```

或者手动：
```bash
cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa/uiuc-ece391-mp3/student-distrib
qemu-system-i386 -hda mp3.img -m 512 -vga std
```

### 编译项目（如果修改了代码）
```bash
cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa/uiuc-ece391-mp3/student-distrib
make clean
make dep
make
```

### 调试模式
```bash
# 终端1：启动QEMU并等待GDB连接
qemu-system-i386 -hda mp3.img -m 512 -vga std -gdb tcp::1234 -S

# 终端2：启动GDB
gdb
(gdb) target remote :1234
(gdb) continue
```

## 操作系统功能

这个操作系统支持以下功能：

### 基础功能
- `ls` - 列出文件
- `cat <filename>` - 显示文件内容
- `help` - 显示帮助信息
- `exit` - 退出程序

### 特色功能
- `cat chinese.txt` - 显示中文字符（UTF-8支持）
- `play halloffame.wav` - 播放音频（Sound Blaster 16）
- `cat cpuinfo` - 显示CPU信息
- `cat date` - 显示日期时间
- `shutdown` - 关机（ACPI支持）
- `reboot` - 重启
- `tuxtest` - Tux控制器测试
- `missile` - Missile Command游戏（支持鼠标）

### 图形界面
- 16/32位色彩支持
- 状态栏显示
- 中文拼音输入法
- 图片显示

## 退出QEMU

- **图形模式**: `Ctrl + Alt + Q`
- **或者**: 在操作系统中输入 `shutdown`

## 工具版本检查

```bash
qemu-system-i386 --version
gcc --version
nasm --version
gdb --version
```

## 故障排除

### QEMU窗口不弹出
```bash
# 检查DISPLAY
echo $DISPLAY

# 重启WSL
wsl --shutdown
wsl
```

### 编译错误
```bash
# 确保32位库已安装
sudo apt install gcc-multilib g++-multilib

# 清理并重新编译
make clean
make dep
make
```

### 网络问题
```bash
# 测试网络
ping -c 2 8.8.8.8

# 如果失败，检查 ~/.wslconfig
```

## 学习资源

- **课程网站**: ECE391 @ UIUC
- **讲师**: Steven Lumetta, Zbigniew Kalbarczyk
- **项目作者**: Ziyuan Chen (ziyuanc3@illinois.edu)

## 注意事项

⚠️ **学术诚信**: 如果你是ECE391的学生，请不要直接复制这些代码。这违反学术诚信政策。

✅ **引用**: 如果需要参考代码，请正确引用：
```
This portion of code is written by Ziyuan Chen 
(https://github.com/AllenHeartcore/ECE391_UIUC22fa)
```

## 快速测试流程

1. 打开WSL: `wsl`
2. 进入目录: `cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa`
3. 运行OS: `bash run_os.sh`
4. 在QEMU窗口中输入命令测试
5. 退出: `Ctrl+Alt+Q` 或输入 `shutdown`

祝你学习愉快！🎓
