#include <stdint.h>
#include "util.h"

#define UART0_BASE 0x10000000 // Uart pointer
volatile uint8_t* const uart = (uint8_t*) UART0_BASE;


void uart_putc(char c) {
    uart[0] = c;
}

void uart_print(const char* str) {
    while (*str) {
        uart_putc(*str++);
    }
}



// Helper: print a labeled bit value (0 or 1)
void print_bit(const char* label, int bit_val) {
    uart_print(label);
    uart_print(": ");
    char c[2] = {digit_to_char(bit_val), 0};
    uart_print(c);
    uart_print("\n");
}

// Helper: print UXL field explanation
void print_uxl(int uxl) {
    uart_print("UXL (bits 33:32): ");
    char c[2] = {digit_to_char(uxl), 0};
    uart_print(c);
    uart_print("\n");
    uart_print(" 1=32-bit, 2=64-bit, 3=128-bit\n");
}