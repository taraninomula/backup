#!/bin/sh

device="MySerialDevice"

major=$(awk '$2=="MySerialDevice" {print $1}' /proc/devices)

mknod /dev/$device c $major 0 --mode=777
