#ifndef DATETIME_H
#define DATETIME_H

#include <stdlib.h>
#include "boolean.h"
#include "io.h"

typedef struct {
	int hour;
	int minute;
	int second;
	int day;
	int month;
	int year;
} DateTime;

void DateTime_now(DateTime *dateTime);

void DateTime_load(DateTime *dateTime, FILE *fin);

void DateTime_save(const DateTime *dateTime, FILE *fout);

bool IsDateTimeValid(DateTime dateTime);

#endif