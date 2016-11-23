#ifndef IO_H
#define IO_H

#include "array.h"
#include "boolean.h"
#include <stdio.h>

#define IO_STRING_QUOTE '`'
#define IO_WHITESPACE " \n\t\v\f\r"
#define IO_NEWLINE "\n\r"

void IO_writeNewLine(FILE *fout);

/* Read/write quoted string from file */
char* IO_readString(FILE *fin);
void IO_writeString(FILE *fout, const char *str);

int IO_readInteger(FILE *fin);
void IO_writeInteger(FILE *fout, int integer);

bool IO_readBool(FILE *fin);
void IO_writeBool(FILE *fout, bool boolean);

/* Load a boolean array from string of 0's and 1's in file */
BoolArray IO_readBoolArray(FILE *fin);
void IO_writeBoolArray(FILE *fout, BoolArray boolArray);

#endif
