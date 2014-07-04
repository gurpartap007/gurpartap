#! /bin/bash
make
insmod ./modules/gill.ko
gcc -o application application.c
./application
read v
ccache -c
dmesg -c
read v
rmmod gill
rm -rf modules.order modules Module.symvers application
