#!/bin/bash
# 自动安装ECE391开发工具

set -e  # 遇到错误立即退出

echo "========================================="
echo "ECE391 开发工具自动安装"
echo "========================================="
echo ""

# 1. 配置dpkg
echo "1. 配置包管理器..."
sudo dpkg --configure -a
echo "✓ dpkg配置完成"
echo ""

# 2. 更新包列表
echo "2. 更新包列表..."
sudo apt update
echo "✓ 包列表更新完成"
echo ""

# 3. 安装工具
echo "3. 安装开发工具（这可能需要5-10分钟）..."
echo "   - QEMU虚拟机"
echo "   - NASM汇编器"
echo "   - GDB调试器"
echo "   - 32位编译支持"
echo ""

sudo apt install -y \
    qemu-system-x86 \
    nasm \
    gdb \
    gcc-multilib \
    g++-multilib

echo ""
echo "✓ 所有工具安装完成"
echo ""

# 4. 验证安装
echo "4. 验证安装..."
echo ""

echo -n "   QEMU: "
qemu-system-i386 --version | head -1

echo -n "   NASM: "
nasm -version

echo -n "   GDB: "
gdb --version | head -1

echo -n "   GCC: "
gcc --version | head -1

echo ""
echo "========================================="
echo "✅ 安装成功！"
echo "========================================="
echo ""
echo "下一步："
echo "  cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa"
echo "  bash run_os.sh"
echo ""
