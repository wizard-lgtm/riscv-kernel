#include <stdint.h>

void u64_to_binary(uint64_t value, char *buffer) {
    for (int i = 0; i < 64; i++) {
        buffer[i] = (value & (1ULL << (63 - i))) ? '1' : '0';
    }
    buffer[64] = '\0'; // null-terminate the string
}

char digit_to_char(int d){
    return (d >= 0 && d <= 9) ? ('0' + d) : '?';
}