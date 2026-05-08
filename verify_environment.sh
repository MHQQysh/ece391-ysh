#!/bin/bash
# ECE391 环境验证脚本

echo "========================================="
echo "ECE391 开发环境验证"
echo "========================================="
echo ""

# 检查工具版本
echo "1. 检查工具安装..."
echo ""

echo -n "GCC: "
if command -v gcc &> /dev/null; then
    gcc --version | head -1
else
    echo "❌ 未安装"
    exit 1
fi

echo -n "NASM: "
if command -v nasm &> /dev/null; then
    nasm -version
else
    echo "❌ 未安装"
    exit 1
fi

echo -n "GDB: "
if command -v gdb &> /dev/null; then
    gdb --version | head -1
else
    echo "❌ 未安装"
    exit 1
fi

echo -n "QEMU: "
if command -v qemu-system-i386 &> /dev/null; then
    qemu-system-i386 --version | head -1
else
    echo "❌ 未安装"
    exit 1
fi

echo ""
echo "2. 检查32位库支持..."
echo ""

if [ -f /usr/lib32/libc.so.6 ] || [ -f /usr/lib/i386-linux-gnu/libc.so.6 ]; then
    echo "✅ 32位库已安装"
else
    echo "❌ 32位库未安装"
    exit 1
fi

echo ""
echo "3. 检查DISPLAY环境变量（GUI支持）..."
echo ""

if [ -n "$DISPLAY" ]; then
    echo "✅ DISPLAY = $DISPLAY"
else
    echo "⚠️  DISPLAY未设置，QEMU可能无法显示窗口"
fi

echo ""
echo "========================================="
echo "✅ 所有工具已正确安装！"
echo "========================================="
echo ""
echo "下一步："
echo "1. 进入项目目录: cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa/uiuc-ece391-mp3/student-distrib"
echo "2. 编译项目: make"
echo "3. 运行QEMU: qemu-system-i386 -hda mp3.img -m 512"
echo ""
