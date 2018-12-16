#include <stdio.h>
#include <assert.h>
#include "days.h"

int
main()
{
	struct DAY day1, day2;

		/* isLeap */
	assert(isLeap(2004) == 1);
	assert(isLeap(1600) == 1);
	assert(isLeap(1900) == 0);

	date_init(&day1, 1, 1, 2012);
	assert(days_in_year(day1, 1) == 1);

	date_init(&day1, 1, 1, 1582);
	assert(days_in_year(day1, 1) == 1);

	date_init(&day1, 12, 10, 1582);
	assert(days_in_year(day1, 1) == ERROR);

	date_init(&day1, 10, 12, 1582);
	assert(days_in_year(day1, 1) == 334);

	date_init(&day1, 10, 12, 1583);
	assert(days_in_year(day1, 1) == 344);

		/* date_correctness */
	date_init(&day1, 12, 10, 1582);
	assert(date_correctness(day1) == 0);

	date_init(&day1, 34, 12, 1333);
	assert(date_correctness(day1) == 0);

	date_init(&day1, 26, 7, 1999);
	assert(date_correctness(day1) == 1);

	date_init(&day1, 5, 5, -1);
	assert(date_correctness(day1) == 0);

	date_init(&day1, 21, 0, 1900);
	assert(date_correctness(day1) == 0);

	date_init(&day1, 29, 2, 1900);
	assert(date_correctness(day1) == 0);

	date_init(&day1, 29, 2, 2000);
	assert(date_correctness(day1) == 1);

	date_init(&day1, 29, 2, 2003);
	assert(date_correctness(day1) == 0);


		/* print_date */
	printf("\nprint date test:\n");
	date_init(&day1, 26, 7, 1999);
	print_date(day1, 1);
	date_init(&day2, 18, 10, 1999);
	print_date(day2, 1);
	date_init(&day1, 1, 1, 1);
	print_date(day1, 0);	printf(" ");
	print_date(day2, 0);	printf(" ");
	date_init(&day1, 31, 11, 1999);
	print_date(day1, 1);
	print_date(day1, 0);

		/* date_compare */
	date_init(&day1, 26, 7, 1999);
	date_init(&day2, 18, 10, 1999);
	assert(date_compare(day1, day2) == -1);

		/* days */
	date_init(&day1, 1, 1, 2018);
	date_init(&day2, 1, 1, 2018);
	assert(days(day1, day2) == 0);

	date_init(&day1, 23, 2, 1590);
	date_init(&day2, 31, 12, 2953);
	assert(days(day1, day2) == 498137);

	date_init(&day1, 23, 12, -1);
	date_init(&day2, 12, 7, 1999);
	assert(days(day1, day2) == ERROR);

	date_init(&day1, 35, 1, 1000);
	date_init(&day2, 0, 0, 0);
	assert(days(day1, day2) == ERROR);

	date_init(&day1, 1, 1, 1000);
	date_init(&day2, 1, 1, 2000);
	assert(days(day1, day2) == 365237);

	date_init(&day1, 15, 1, 1923);
	date_init(&day2, 12, 1, 1322);
	assert(days(day1, day2) == 219505);

	date_init(&day1, 12, 1, 1322);
	date_init(&day2, 15, 1, 1923);
	assert(days(day1, day2) == 219505);

	date_init(&day1, 1, 1, 1324);
	date_init(&day2, 1, 1, 1923);
	assert(days(day1, day2) == 218772);

	date_init(&day1, 1, 1, 1400);
	date_init(&day2, 1, 1, 1923);
	assert(days(day1, day2) == 191013);

	date_init(&day1, 2, 2, 2004);
	date_init(&day2, 29, 2, 2008);
	assert(days(day1, day2) == 1488);
/*
	date_init();
	date_init();
	assert(days(day1, day2) == );

	date_init();
	date_init();
	assert(days(day1, day2) == );

	date_init();
	date_init();
	assert(days(day1, day2) == );

	date_init();
	date_init();
	assert(days(day1, day2) == );

	date_init();
	date_init();
	assert(days(day1, day2) == );

	date_init();
	date_init();
	assert(days(day1, day2) == );

	date_init();
	date_init();
	assert(days(day1, day2) == );
*/
	printf("\nACC\n");

	return (0);
}
