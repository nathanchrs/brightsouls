#include "io.h"
#include "stringutils.h"

FILE* IO_openFile(const char *directory, const char *fileName) {
	char *filePath = StringUtils_concat(directory, fileName);
	FILE *fin = fopen(filePath, "r");
	StringUtils_deallocate(filePath);
	return fin;
}

FILE* IO_openFileForWrite(const char *directory, const char *fileName) {
	char *filePath = StringUtils_concat(directory, fileName);
	FILE *fout = fopen(filePath, "w");
	StringUtils_deallocate(filePath);
	return fout;
}

void IO_closeFile(FILE *file) {
	fclose(file);
}

void IO_discardCharacters(FILE *fin, const char *discard) {
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

void IO_writeNewline(FILE *fout) {
	fprintf(fout, "\n");
}

char* IO_readString(FILE *fin) {
	char c;
	bool stop;

	/* Search for opening quote */
	stop = false;
	while(!stop) {
		c = fgetc(fin);
		if (c == EOF || c == IO_STRING_QUOTE) {
			stop = true;
		}
	}

	/* Read actual string plus ending quote */
	char delim[2];
	delim[0] = IO_STRING_QUOTE;
	delim[1] = 0;
	return StringUtils_scan(fin, delim);
}

void IO_writeString(FILE *fout, const char *str) {
	fprintf(fout, "%c%s%c ", IO_STRING_QUOTE, str, IO_STRING_QUOTE);
}

int IO_readInteger(FILE *fin) {
	int inp = 0;
	fscanf(fin, "%d", &inp);
	return inp;
}

void IO_writeInteger(FILE *fout, int integer) {
	fprintf(fout, "%d ", integer);
}

/* Load a boolean array from string of 0's and 1's in file */
BoolArray IO_readBoolArray(FILE *fin) {
	BoolArray array;
	IO_discardCharacters(fin, IO_WHITESPACE);
	char *input = StringUtils_scan(fin, IO_NEWLINE);
	size_t inputLen = StringUtils_strlen(input);
	Array_allocate(&array, inputLen);
	int i;
	for (i = 0; i < inputLen; i++) {
		if (input[i] == '0') Array_pushBack(&array, false);
		else if (input[i] == '1') Array_pushBack(&array, true);
	}
	StringUtils_deallocate(input);
	return array;
}

void IO_writeBoolArray(FILE *fout, BoolArray boolArray) {
	int i;
	for (i = 0; i < boolArray.length; i++) {
		if (boolArray.items[i]) fprintf(fout, "1");
		else fprintf(fout, "0");
	}
	fprintf(fout, " ");
}
