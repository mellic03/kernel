#!/bin/bash

file="${1::-4}"

g++ -nostartfiles -nodefaultlibs -fPIC -ffreestanding -o "$file" "${file}.cpp"
objcopy -O binary "$file" "${file}.bin"

