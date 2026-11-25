all:
	as --32 src/boot/boot.s -o build/boot.o
	gcc -m32 -U__linux__ -c src/kernel/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -fno-pie
	ld -m elf_i386 -T src/kernel/linker.ld -o build/myos.bin build/boot.o build/kernel.o

run: all
	qemu-system-i386 -kernel build/myos.bin

clean:
	rm -rf build/*
