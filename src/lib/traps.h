#pragma once
#include <stdint.h>
void enable_supervisor_interrupts(void);
void trap_handler(void);
void sstatus_analyze();
void set_trap_handler_function(void* handler);