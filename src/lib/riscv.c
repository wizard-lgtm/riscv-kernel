#include <stdint.h>
#include "riscv.h"
#include "uart.h"
#include "util.h"
uint64_t read_sstatus(void) {
    uint64_t value;
    asm volatile ("csrr %0, sstatus" : "=r"(value));
    return value;
}

void write_sstatus(uint64_t value) {
    asm volatile ("csrw sstatus, %0" :: "r"(value));
}



uint64_t csr_read(Csr csr) {
    uint64_t value;
    switch (csr) {
        case CSR_SSTATUS:
            asm volatile("csrr %0, sstatus" : "=r"(value));
            break;
        case CSR_SIE:
            asm volatile("csrr %0, sie" : "=r"(value));
            break;
        case CSR_STVEC:
            asm volatile("csrr %0, stvec" : "=r"(value));
            break;
        case CSR_SCOUNTEREN:
            asm volatile("csrr %0, scounteren" : "=r"(value));
            break;
        case CSR_SSCRATCH:
            asm volatile("csrr %0, sscratch" : "=r"(value));
            break;
        case CSR_SEPC:
            asm volatile("csrr %0, sepc" : "=r"(value));
            break;
        case CSR_SCAUSE:
            asm volatile("csrr %0, scause" : "=r"(value));
            break;
        case CSR_STVAL:
            asm volatile("csrr %0, stval" : "=r"(value));
            break;
        case CSR_SIP:
            asm volatile("csrr %0, sip" : "=r"(value));
            break;
        case CSR_SATP:
            asm volatile("csrr %0, satp" : "=r"(value));
            break;
        default:
            value = 0;
            break;
    }
    return value;
}

void csr_write(Csr csr, uint64_t value) {
    switch (csr) {
        case CSR_SSTATUS:
            asm volatile("csrw sstatus, %0" : : "r"(value));
            break;
        case CSR_SIE:
            asm volatile("csrw sie, %0" : : "r"(value));
            break;
        case CSR_STVEC:
            asm volatile("csrw stvec, %0" : : "r"(value));
            break;
        case CSR_SCOUNTEREN:
            asm volatile("csrw scounteren, %0" : : "r"(value));
            break;
        case CSR_SSCRATCH:
            asm volatile("csrw sscratch, %0" : : "r"(value));
            break;
        case CSR_SEPC:
            asm volatile("csrw sepc, %0" : : "r"(value));
            break;
        case CSR_SCAUSE:
            asm volatile("csrw scause, %0" : : "r"(value));
            break;
        case CSR_STVAL:
            asm volatile("csrw stval, %0" : : "r"(value));
            break;
        case CSR_SIP:
            asm volatile("csrw sip, %0" : : "r"(value));
            break;
        case CSR_SATP:
            asm volatile("csrw satp, %0" : : "r"(value));
            break;
        default:
            break;
    }
}

void csr_print_as_binary(Csr csr){
    char buf[19];
    uint64_t csr_val = csr_read(csr);
    u64_to_binary(csr_val, buf);
    uart_print(buf); 
}