riscv64-linux-gnu-gcc -c -nostdlib -nostartfiles -ffreestanding -o kmain.o kmain.c
riscv64-linux-gnu-as -o kernel.o kernel.s
riscv64-linux-gnu-ld -T link.ld -o kernel.elf kernel.o kmain.o
riscv64-linux-gnu-ld -T link.ld -o kernel.elf kernel.o kmain.o
qemu-system-riscv64 -nographic -machine virt -kernel kernel.elf