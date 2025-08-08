#include "string.h"


size_t strlen(const char *str) {
	size_t len = 0;
	while (*str++) {
		len++;
	}
	return len;
}
char* strcat(char* dest, const char* src) {
	size_t len_dest = strlen(dest);
	size_t len_src = strlen(src);
	size_t i = 0 + len_dest;
	for (; i < len_src + len_dest; i++) {
		(*(dest + i)) = (*(src + i - len_dest));
	}
	(*(dest + i)) = '\0';
	return dest;
}