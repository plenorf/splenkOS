#pragma once
#include <stddef.h>


size_t strlen(const char *str);
char* strcat(char* dest, const char* src);
char *itoa(int value, char *str, int base);
char *strcpy(char *dest, const char *src);
int strcmp(const char *str1, const char *str2);
char *strtok(char *str, const char *delim);
char *strchr(const char *str, int ch);