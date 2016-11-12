#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <stdio.h>

/* Operations that dynamically expands the size of a string will allocate blocks of this size */
#define STRING_ALLOC_BLOCK_SIZE 16

#define STRINGUTILS_WHITESPACE " \n\t\v\f\r"
#define STRINGUTILS_NEWLINE "\n\r"

int tolower(int c);

int toupper(int c);

/* Read string from the input file from the current position until the delimiter character.
   The resulting string is dynamically allocated. Returns null on allocation failure. */
char* StringUtils_scan(FILE *fin, const char *delim);

/* Discard characters from input file until the next character is not in the discard string or EOF has been reached. */
void StringUtils_discardCharacters(FILE *fin, const char *discard);

/* Returns a pointer to a clone of string str
   The resulting string is dynamically allocated. Returns null on allocation failure. */
char* StringUtils_clone(const char *str);

void StringUtils_deallocate(char *str);

/* Creates a new string containing the concatenation of str1 and str2. Returns null on allocation failure. */
char* StringUtils_concat(const char *str1, const char *str2);

size_t StringUtils_strlen(const char *str);

char* StringUtils_strcpy(char *destination, const char *source);

char* StringUtils_strncpy(char *destination, const char *source, size_t num);

/* Case-insensitive string comparison,
   returns <0 if first character that does not match in str1 < str2, 0 if both strings are equal, or >0 otherwise */
int StringUtils_strcmpi(const char *str1, const char *str2);

/* Checks whether all characters in a string (not including ending null byte) satisfies a condition.
   checker is a pointer to a function which accepts an integer representing a character,
   and outputs a non-zero integer if the character satisfies the condition,
   or 0 otherwise (e.q. ctype's isdigit, isspace, islower functions. */
unsigned char StringUtils_check(const char *str, int (*checker)(int));

#endif