#pragma once
#include <stdbool.h>

#define PORT 0x3f8          // COM1

static bool serialEnabled = false;

bool init_serial();
int serial_received();
char read_serial();
int is_transmit_empty();
void write_serial(char a);
void write_serial_string(const char* str);