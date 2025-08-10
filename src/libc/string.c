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

char *itoa(int value, char *str, int base) {
    const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i = 0;
    int sign = 0;

    if (str == NULL) return NULL;          /* require a buffer pointer */
    if (base < 2 || base > 36) return NULL;/* unsupported base */

    /* special case: zero */
    if (value == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    /* only show negative sign for base 10 */
    if (value < 0 && base == 10) {
        sign = 1;
    }

    /* convert using an unsigned magnitude to safely handle INT_MIN */
    unsigned long long mag;
    if (value < 0) {
        mag = (unsigned long long)(-(long long)value); /* safe for INT_MIN */
    } else {
        mag = (unsigned long long)value;
    }

    /* produce digits in reverse order */
    while (mag > 0) {
        unsigned int rem = (unsigned int)(mag % (unsigned long long)base);
        str[i++] = digits[rem];
        mag /= base;
    }

    if (sign) {
        str[i++] = '-';
    }

    /* terminate and reverse the string in-place */
    str[i] = '\0';
    /* reverse */
    for (int a = 0, b = i - 1; a < b; ++a, --b) {
        char tmp = str[a];
        str[a] = str[b];
        str[b] = tmp;
    }

    return str;
}

char *strcpy(char *dest, const char *src) {
    char *d = dest;
    while ((*d++ = *src++)); // copy until null terminator (0) is copied
    return dest;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return (unsigned char)*str1 - (unsigned char)*str2;
}

char *strtok(char *str, const char *delim) {
    static char *next; // saves position between calls
    if (str) {
        next = str; // first call with the string
    }
    if (!next) {
        return NULL; // no more tokens
    }

    // Skip leading delimiters
    char *start = next;
    while (*start && strchr(delim, *start)) {
        start++;
    }

    if (*start == '\0') {
        next = NULL;
        return NULL; // reached end
    }

    // Find end of the token
    char *end = start;
    while (*end && !strchr(delim, *end)) {
        end++;
    }

    if (*end) {
        *end = '\0';  // terminate token
        next = end + 1; // save position for next call
    } else {
        next = NULL; // no more tokens
    }

    return start;
}

char *strchr(const char *str, int ch) {
    while (*str) {
        if (*str == (char)ch) {
            return (char *)str; // cast to non-const for compatibility
        }
        str++;
    }
    // If ch is '\0', return pointer to the null terminator
    if (ch == '\0') {
        return (char *)str;
    }
    return NULL;
}

int atoi(char *p) {
    int k = 0;
    while (*p) {
        k = (k << 3) + (k << 1) + (*p) - '0';
        p++;
     }
     return k;
}