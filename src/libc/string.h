#pragma once
#include <stddef.h>


size_t strlen(const char *str);
char* strcat(char* dest, const char* src);
char *itoa_safe(int value, char *str, int base);