
#include <stdint.h>

typedef unsigned char uint8_t;

#define UART0 0x10000000
volatile uint8_t* const uart = (uint8_t*)UART0;



#define SBI_CONSOLE_PUTCHAR 1
#define SBI_CONSOLE_GETCHAR 2
#define SBI_SET_TIMER 0
#define SBI_SHUTDOWN 8
#define delta_cycles 10000000  // 10 million cycles


#define SBI_CALL(which, arg0, arg1, arg2) ({ \
  register unsigned long a0 asm ("a0") = (unsigned long)(arg0); \
  register unsigned long a1 asm ("a1") = (unsigned long)(arg1); \
  register unsigned long a2 asm ("a2") = (unsigned long)(arg2); \
  register unsigned long a7 asm ("a7") = (unsigned long)(which); \
  asm volatile ("ecall" \
                : "+r"(a0) \
                : "r"(a1), "r"(a2), "r"(a7)); \
  a0; })


static inline void sbi_set_timer(uint64_t stime_value) {
    register uint64_t a0 asm("a0") = stime_value;
    register uint64_t a7 asm("a7") = SBI_SET_TIMER;
    asm volatile ("ecall" : "+r"(a0) : "r"(a7));
}

static inline uint64_t get_time() {
    uint64_t time;
    asm volatile("rdtime %0" : "=r"(time));
    return time;
}



void sbi_putchar(char c) {
    SBI_CALL(SBI_CONSOLE_PUTCHAR, c, 0, 0);
}


void uart_putc(char c) {
    uart[0] = c;
}   

void uart_print(const char* s) {
    while (*s) sbi_putchar(*s++);
}

void kmain() {
    sbi_set_timer(get_time() + delta_cycles);

    uart_print("Hello from our RISC-V kernel123!\n");
    while (1);
}

