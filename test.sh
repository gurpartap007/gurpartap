#! /bin/bash
ci initial.c
ci cleanup.c
ci header.h
ci declarations.h
ci file_operations.h
ci scull_open.c
ci scull_read.c
ci scull_write.c
ci scull_lseek.c
ci scull_release.c
read v
co -l initial.c
co -l cleanup.c
co -l header.h
co -l declarations.h
co -l file_operations.h
co -l scull_lseek.c
co -l scull_open.c
co -l scull_write.c
co -l scull_read.c
co -l scull_release.c
read v
#ifndef DEBUG
#DEFINE DEBUG
#endif
make 
read v

insmod ./modules/gill.ko
dmesg 
read v
lsmod | head -2
read v

gcc -o writer1 writer1.c
./writer1
dmesg 
rmmod gill
dmesg | tail -2
read v
dmesg -c | tail -0
rm -rf  writer1 scull_lseek.c initial.c scull_read.c cleanup.c header.h declarations.h file_operations.h scull_open.c scull_write.c scull_release.c modules.order modules Module.symvers
