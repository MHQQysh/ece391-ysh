#!/bin/bash
# CP1内核快速编译和运行脚本

cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa/cp1_kernel

echo "========================================="
echo "  CP1 Kernel - Build and Run"
echo "========================================="
echo ""

# 清理旧文件
echo "Cleaning old files..."
make clean

# 编译
echo ""
echo "Compiling kernel..."
make

if [ $? -ne 0 ]; then
    echo ""
    echo "❌ Compilation failed!"
    exit 1
fi

echo ""
echo "✅ Compilation successful!"
echo ""
echo "Kernel size:"
ls -lh bootimg

echo ""
echo "========================================="
echo "  Starting QEMU..."
echo "========================================="
echo ""
echo "Press Ctrl+Alt+Q to exit QEMU"
echo ""

# 运行QEMU
qemu-system-i386 -kernel bootimg -m 512

echo ""
echo "QEMU exited."
