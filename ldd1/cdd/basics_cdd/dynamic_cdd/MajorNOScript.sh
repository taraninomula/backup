#!/bin/sh

device="CharDriver"

/sbin/insmod ./$device.ko || exit 1

/bin/rm -f /dev/${device}

major=$(awk '$2=="MyCharDevice" {print $1}' /proc/devices)

echo $major

/bin/mknod /dev/${device} c $major 0 --mode=777
