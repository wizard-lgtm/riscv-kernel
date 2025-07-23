#include <stdint.h>

typedef enum {
    INTERRUPT_INSTR_ADDR_MISALIGNED = 0, // Not an interrupt, example exception code included by mistake
    INTERRUPT_SSI   = 1,  // Supervisor software interrupt
    INTERRUPT_VSSI  = 2,  // Virtual supervisor software interrupt
    INTERRUPT_MSI   = 3,  // Machine software interrupt
    INTERRUPT_RESERVED_4 = 4,
    INTERRUPT_STI   = 5,  // Supervisor timer interrupt
    INTERRUPT_VSTI  = 6,  // Virtual supervisor timer interrupt
    INTERRUPT_MTI   = 7,  // Machine timer interrupt
    INTERRUPT_RESERVED_8 = 8,
    INTERRUPT_SEI   = 9,  // Supervisor external interrupt
    INTERRUPT_VSEI  = 10, // Virtual supervisor external interrupt
    INTERRUPT_MEI   = 11, // Machine external interrupt
    INTERRUPT_SGEI  = 12, // Supervisor guest external interrupt
    INTERRUPT_LCOFI = 13, // Local counter overflow interrupt
    INTERRUPT_RESERVED_14 = 14,
    INTERRUPT_RESERVED_15 = 15
} SupervisorInterruptCode;

// Supervisor Exception Codes (scause MSB=0)
typedef enum {
    EXCEPTION_INSTR_ADDR_MISALIGNED = 0,
    EXCEPTION_INSTR_ACCESS_FAULT     = 1,
    EXCEPTION_ILLEGAL_INSTRUCTION    = 2,
    EXCEPTION_BREAKPOINT             = 3,
    EXCEPTION_LOAD_ADDR_MISALIGNED   = 4,
    EXCEPTION_LOAD_ACCESS_FAULT      = 5,
    EXCEPTION_STORE_AMO_ADDR_MISALIGNED = 6,
    EXCEPTION_STORE_AMO_ACCESS_FAULT = 7,
    EXCEPTION_ENV_CALL_FROM_U_OR_VU  = 8,
    EXCEPTION_ENV_CALL_FROM_HS_MODE  = 9,
    EXCEPTION_ENV_CALL_FROM_VS_MODE  = 10,
    EXCEPTION_ENV_CALL_FROM_M_MODE   = 11,
    EXCEPTION_INSTR_PAGE_FAULT       = 12,
    EXCEPTION_LOAD_PAGE_FAULT        = 13,
    EXCEPTION_RESERVED_14            = 14,
    EXCEPTION_STORE_AMO_PAGE_FAULT   = 15,
    EXCEPTION_RESERVED_16            = 16,
    EXCEPTION_RESERVED_17            = 17,
    EXCEPTION_SOFTWARE_CHECK         = 18,
    EXCEPTION_HARDWARE_ERROR         = 19,
    EXCEPTION_INSTR_GUEST_PAGE_FAULT = 20,
    EXCEPTION_LOAD_GUEST_PAGE_FAULT  = 21,
    EXCEPTION_VIRTUAL_INSTRUCTION    = 22,
    EXCEPTION_STORE_AMO_GUEST_PAGE_FAULT = 23
} SupervisorExceptionCode;


typedef enum {
    // Supervisor Mode CSRs
    CSR_SSTATUS = 0x100,  // Supervisor Status
    CSR_SIE     = 0x104,  // Supervisor Interrupt Enable
    CSR_STVEC   = 0x105,  // Supervisor Trap Vector Base Address
    CSR_SCOUNTEREN = 0x106, // Supervisor Counter Enable

    CSR_SSCRATCH = 0x140, // Supervisor Scratch register
    CSR_SEPC      = 0x141, // Supervisor Exception Program Counter
    CSR_SCAUSE    = 0x142, // Supervisor Cause register
    CSR_STVAL     = 0x143, // Supervisor Trap Value (faulting addr)
    CSR_SIP       = 0x144, // Supervisor Interrupt Pending
    CSR_SATP      = 0x180, // Supervisor Address Translation and Protection
} Csr;


uint64_t read_sstatus(void);
void write_sstatus(uint64_t value);
uint64_t csr_read(Csr csr);
void csr_write(Csr csr, uint64_t value);
void csr_print_as_binary(Csr);