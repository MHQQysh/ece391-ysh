#!/bin/bash
# 快速启动ECE391操作系统

cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa/uiuc-ece391-mp3/student-distrib

echo "========================================="
echo "启动ECE391操作系统"
echo "========================================="
echo ""
echo "镜像文件: mp3.img"
echo "内存: 512MB"
echo "显卡: VGA标准模式"
echo ""
echo "启动中..."
echo ""

# 运行QEMU
qemu-system-i386 -hda mp3.img -m 512 -vga std

echo ""
echo "操作系统已退出"
