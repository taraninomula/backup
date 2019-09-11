#!/bin/sh

device="ioctl"
module="MyCharDevice"
/sbin/insmod ./$device.ko || exit 1

rm -f /dev/${device}[0-3]

major=$(awk '$2=="MyCharDevice" {print $1}' /proc/devices)



mknod /dev/${device} c $major 0 --mode=777
#mknod /dev/${device}1 c $major 1 --mode=777
#mknod /dev/${device}2 c $major 2 --mode=777
#mknod /dev/${device}3 c $major 3 --mode=777
