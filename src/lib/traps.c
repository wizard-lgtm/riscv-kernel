#include "traps.h"
#include "riscv.h"
#include "uart.h"
#include "util.h"


void enable_supervisor_interrupts(void) {
    uint64_t sstatus = read_sstatus();
    sstatus |= (1 << 1);  // Set SIE bit
    write_sstatus(sstatus);
}

void trap_handler(){
    uart_print("TRAP!");

    uint64_t scause = csr_read(CSR_SCAUSE);  // Get cause of the trap
    uint64_t sepc = csr_read(CSR_SEPC);      // Get the program counter (PC) where the trap occurred

    // The highest (MSB) bit of scause indicates interrupt (1) or exception (0)
    int is_interrupt = (scause >> 63) != 0;

    // The lower bits [62:0] hold the interrupt or exception code
    uint64_t code = scause & 0x7FFFFFFFFFFFFFFF;

    // Handling the interrupt (if it's an interrupt)
    if (is_interrupt) {
        switch ((SupervisorInterruptCode)code) {
            case INTERRUPT_STI:
                // Handle timer interrupt
                break;
            case INTERRUPT_SEI:
                // Handle external interrupt
                break;
            default:
                // Unknown interrupt
                break;
        }
    } 
    // Handling the exception (if it's an exception)
    else {
        switch ((SupervisorExceptionCode)code) {
            case EXCEPTION_ILLEGAL_INSTRUCTION:
                // Handle illegal instruction
                break;
            // other exceptions...
            default:
                // Unknown exception
                break;
        }
    }

    // To avoid infinite loops, increment SEPC by 4 (the size of an instruction)
csr_write(CSR_SEPC, sepc + 4);
    // Return from trap handler (this will restore the program counter)
    // This will resume execution from the next instruction after the trap
    // (you might need to use `mret` or a similar instruction depending on your implementation)
    asm volatile("sret");
}


void sstatus_analyze() {
    const uint64_t SD_MASK    = 1ULL << 63;
    const uint64_t UXL_MASK   = 3ULL << 32; // bits 33:32
    const uint64_t SPP_MASK   = 1ULL << 8;
    const uint64_t SPIE_MASK  = 1ULL << 5;
    const uint64_t SIE_MASK   = 1ULL << 1;

    uint64_t sstatus = csr_read(CSR_SSTATUS);

    int sd   = (sstatus & SD_MASK) ? 1 : 0;
    int uxl  = (int)((sstatus & UXL_MASK) >> 32);
    int spp  = (sstatus & SPP_MASK) ? 1 : 0;
    int spie = (sstatus & SPIE_MASK) ? 1 : 0;
    int sie  = (sstatus & SIE_MASK) ? 1 : 0;

    char buf[19];

    u64_to_binary(sstatus, buf);

    uart_print("sstatus binary: ");
    uart_print(buf);
    uart_print("\n");

    uart_print("sstatus analysis:\n");
    print_bit("SD (bit 63)          ", sd);
    print_uxl(uxl);
    print_bit("SPP (bit 8)          ", spp);
    uart_print(" 0=User mode, 1=Supervisor mode\n");
    print_bit("SPIE (bit 5)         ", spie);
    uart_print(" Interrupts enabled before trap\n");
    print_bit("SIE (bit 1)          ", sie);
    uart_print(" Current supervisor interrupt enable\n");
}


void set_trap_handler_function(void* handler){
    // Convert function address to 32-bit pointer first
    uint32_t handler_addr_32 = (uint32_t)(uintptr_t)handler;
    
    // Ensure the address is aligned to 4 bytes (clear bottom 2 bits)
    handler_addr_32 &= ~0x3U;
    
    // Convert back to 64-bit for stvec register
    uint64_t handler_addr = (uint64_t)handler_addr_32;
    
    // Set MODE field to 0 (Direct mode) - bottom 2 bits should be 00
    // The address should already have bottom 2 bits clear from alignment
    uint64_t stvec_value = handler_addr;  // MODE = 00 (Direct) already set by alignment
    
    // Write to stvec register
    csr_write(CSR_STVEC, stvec_value);
    
    uart_print("Stvec address setted!\n");
    uart_print("Stvec:");
    csr_print_as_binary(CSR_STVEC);
    uart_print("\n");

}
