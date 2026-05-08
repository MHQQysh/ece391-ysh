#!/bin/bash
# 运行已验证可工作的ECE391操作系统

cd /mnt/c/Users/13613/Desktop/ECE391_UIUC22fa/uiuc-ece391-mp3/student-distrib

echo "启动ECE391操作系统..."
echo "使用已编译好的版本（uiuc-ece391-mp3）"
echo ""

qemu-system-i386 -drive file=mp3.img,format=raw -m 512

echo ""
echo "操作系统已退出"
