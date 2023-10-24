#!/bin/sh
#UTF8

# stm32flash loader

# stm32flash bin
Bin="/usr/local/bin/stm32flash"

# COM-port
Com="/dev/ttyUSB0"

# COM-port baudrate (speed)
#Spd=57600
Spd=115200

# Start execution at specified address (0 = flash start)
# =address
g=0x0

# Specify start address and optionally length in bytes for read/write/erase operations
# =address[:length]
S=0x08000000

# Path to HEX-file to load
#Hex="Release/stm32f411-hal-baremetal-led.hex"
Hex="Release/stm32f411-hal-baremetal-led.hex"


if [ ! -f $Bin ]; then
    echo "Error $Bin!"
    exit
fi

if [ ! -e $Com ]; then
    echo "Error $Com!"
    exit
fi

if [ ! -f $Hex ]; then
    echo "Error $Hex!"
    exit
fi

echo "$Bin -w $Hex -v -g $g -S $S -b $Spd $Com"
$Bin -w $Hex -v -g $g -S $S -b $Spd $Com
# $Bin -w $Hex -v -g $g -S $S $Com
