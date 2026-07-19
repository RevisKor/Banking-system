#ifndef DATE_H
#define DATE_H

// imports
#include "../../common.h"

// prototypes
int is_leap_year(int year);
void get_date(const char* prompt, char* dest_date);
void get_time(const char* prompt, char* dest_time);
int validate_date(char* date);
int validate_time(char* time);
int validate_opening_hours(char* times, char* opening_hours, char* closing_hours);

#endif