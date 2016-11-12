#include "stringutils.h"
#include "boolean.h"
#include <stdlib.h>

int tolower(int c) {
	if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
	return c;
}

int toupper(int c) {
	if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
	return c;
}

/* Read string from the input file from the current position until the delimiter character(s)
   (each character in the delimiter parameter is treated as a separate delimiter).
   The resulting string is dynamically allocated. Returns null on allocation failure. */
char* StringUtils_scan(FILE *fin, const char *delim) {
	char inp;
	size_t delimLen = StringUtils_strlen(delim);
	size_t len = 0;
	size_t capacity = STRING_ALLOC_BLOCK_SIZE;
	char *str = malloc(sizeof(char)*capacity);
	if (!str) return str;

	bool stop = false;
	while (!stop) {
		inp = fgetc(fin);

		if (inp == EOF) stop = true;
		int i = 0;
		while(i < delimLen && !stop) {
			if (inp == delim[i]) stop = true;
			i++;
		}

		if (!stop) {
			str[len] = inp;
			len++;

			// Resize if actual length + 1 exceeds capacity
			if (len == capacity) {
				str = realloc(str, sizeof(char) * (capacity + STRING_ALLOC_BLOCK_SIZE));
				if (!str) return str;
				capacity += STRING_ALLOC_BLOCK_SIZE;
			}
		}
	}

	// Set ending null character
	str[len] = 0;

	// Resize to exact string length, then return
	return realloc(str, sizeof(char) * (len + 1));
}

void StringUtils_discardCharacters(FILE *fin, const char *discard) {
	char c;
	size_t discardLen = StringUtils_strlen(discard);
	bool stop = false;
	while(!stop) {
		c = fgetc(fin);
		if (c == EOF) {
			stop = true;
		} else {
			int i = 0;
			bool found = false;
			while(i < discardLen && !found) {
				if (c == discard[i]) {
					found = true;
				} else {
					i++;
				}
			}
			if (!found) {
				stop = true;
				ungetc(c, fin);
			}
		}
	}
}

/* Returns a pointer to a clone of string str
   The resulting string is dynamically allocated. Returns null on allocation failure. */
char* StringUtils_clone(const char *str) {
	char *res = malloc(sizeof(char) * (StringUtils_strlen(str) + 1));
	if (res) StringUtils_strcpy(res, str);
	return res;
}

/* Creates a new string containing the concatenation of str1 and str2. Returns null on allocation failure. */
char* StringUtils_concat(const char *str1, const char *str2) {
	size_t slen1 = StringUtils_strlen(str1);
	size_t slen2 = StringUtils_strlen(str2);
	char *res = malloc(sizeof(char) * (slen1 + slen2 + 1));
	if (res) {
		StringUtils_strcpy(res, str2);
		StringUtils_strcpy(res + slen1, str2);
	}
	return res;
}

void StringUtils_deallocate(char *str) {
	free(str);
}

size_t StringUtils_strlen(const char *str) {
	size_t len = 0;
	while (str[len] != 0) len++;
	return len;
}

char* StringUtils_strcpy(char *destination, const char *source) {
	size_t i = 0;
	while (source[i] != 0) {
		destination[i] = source[i];
		i++;
	}
	destination[i] = 0;
	return destination;
}

char* StringUtils_strncpy(char *destination, const char *source, size_t num) {
	size_t i;
	bool sourceEnd = false;
	for (i = 0; i < num; i++) {
		if (source[i] == 0) sourceEnd = true;
		if (sourceEnd) {
			destination[i] = 0;
		} else {
			destination[i] = source[i];
		}
	}
	return destination;
}

/* Case-insensitive string comparison,
   returns <0 if first character that does not match in str1 < str2, 0 if both strings are equal, or >0 otherwise */
int StringUtils_strcmpi(const char *str1, const char *str2) {
	const char *p1 = str1;
	const char *p2 = str2;
	char c1, c2;
	do {
		c1 = (char) tolower((int) *p1);
		c2 = (char) tolower((int) *p2);
		p1++;
		p2++;
	} while (c1 == c2 && c1 != 0);
	return c1-c2;
}

/* Checks whether all characters in a string (not including ending null byte) satisfies a condition.
   checker is a pointer to a function which accepts an integer representing a character,
   and outputs a non-zero integer if the character satisfies the condition,
   or 0 otherwise (e.q. ctype's isdigit, isspace, islower functions. */
unsigned char StringUtils_check(const char *str, int (*checker)(int)) {
	const char *p = str;
	while ((*p) != 0) {
		if (!(*checker)((int) *p)) return 1;
		p++;
	}
	return 0;
}