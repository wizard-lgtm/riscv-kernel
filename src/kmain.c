#include "traps.h"
#include "riscv.h"
#include "util.h"
#include <stdint.h>
#include "uart.h"

void test_ecall() {
    uart_print("Testing ecall...\n");
    
    // Execute ecall instruction - will trigger environment call exception
    asm volatile("ecall");
    
    uart_print("Returned from ecall trap\n");
}

void test_illegal_instruction() {
    uart_print("Testing illegal instruction...\n");
    
    // Execute an illegal/undefined instruction
    // This will cause an illegal instruction exception
    asm volatile(".word 0x00000000");  // All zeros = illegal instruction
    
    uart_print("Returned from illegal instruction trap\n");
}


void kmain() {
    uart_print("Hello from our RISC-V kernel!\n");

    enable_supervisor_interrupts();

    sstatus_analyze();

    set_trap_handler_function(trap_handler);

    test_ecall();

    while (1) { }
}