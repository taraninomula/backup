#!/bin/sh

module="CalculatorDriver"
/sbin/insmod ./$module.ko || exit 1

/bin/rm -f /dev/add
/bin/rm -f /dev/sub
/bin/rm -f /dev/mul
/bin/rm -f /dev/div

major=$(awk '$2=="MyCharDevice" {print $1}' /proc/devices)
echo major:$major


/bin/mknod /dev/add c $major 0 --mode=777
/bin/mknod /dev/sub c $major 1 --mode=777
/bin/mknod /dev/mul c $major 2 --mode=777
/bin/mknod /dev/div c $major 3 --mode=777
