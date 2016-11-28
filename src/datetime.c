#include <time.h>
#include "datetime.h"

void DateTime_now(DateTime *dateTime){
   time_t hour;	
   struct tm *info;

   time(&hour);
   info = localtime(&hour);

   dateTime->hour = (info->tm_hour)%24;
   dateTime->minute = (info->tm_min);
   dateTime->second = (info->tm_sec);
   dateTime->day = (info->tm_mday); 
   dateTime->month = (info->tm_mon);
   dateTime->year = 2000+(info->tm_year)%100; // only valid for years >= 2000
}

void DateTime_load(DateTime *dateTime, FILE *fin){
	dateTime->hour = IO_readInteger(fin); 
	dateTime->minute = IO_readInteger(fin);
	dateTime->second = IO_readInteger(fin);
	dateTime->day = IO_readInteger(fin);
	dateTime->month = IO_readInteger(fin);
	dateTime->year = IO_readInteger(fin);
}

void DateTime_save(const DateTime *dateTime, FILE *fout){
	IO_writeInteger(fout, dateTime->hour);
	IO_writeInteger(fout, dateTime->minute);
	IO_writeInteger(fout, dateTime->second);
	IO_writeInteger(fout, dateTime->day);
	IO_writeInteger(fout, dateTime->month);
	IO_writeInteger(fout, dateTime->year);
	IO_writeNewline(fout);
}

/* Simplistic dateTime validity checking, does not validate day of month */
bool IsDateTimeValid(DateTime dateTime) {
	if (dateTime.hour > 23 || dateTime.hour < 0)
		return false;
	else if (dateTime.minute < 0 || dateTime.minute >= 60)
		return false;
	else if (dateTime.second < 0 || dateTime.second >= 60)
		return false;
	else if (dateTime.day > 31 || dateTime.day < 1)
		return false;
	else if (dateTime.month > 12 || dateTime.month < 1)
		return false;
	else if (dateTime.year < 1)
		return false;
	else
		return true;
}
