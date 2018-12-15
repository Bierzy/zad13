#ifndef days_h
#define days_h

#include <stdio.h>
#include <stdlib.h>

#define COMMON_YEAR_DAYS 365
#define LEAP_YEAR_DAYS 366
#define ERROR (-2)

struct DAY {
	int day;
	int month;
	int year;
	int correct;
};

	/* Number of days between two dates */
int days(struct DAY first, struct DAY second);

int isLeap(int year);

int date_correctness(struct DAY date);

int date_compare(struct DAY date_1, struct DAY date_2);

void date_init(struct DAY *date, int in_day, int in_month,
		int in_year);

int days_in_year(struct DAY date, int cal_change);

void print_date(struct DAY date, int new_line);

#endif
