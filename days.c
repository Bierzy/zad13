#include "days.h"

extern int
isLeap(int year)
{
	/*
	 * Function checks if the given year is a leap year.
	 * It returns 1 if the year is a leap year and 0 otherwise.
	 */

		/* security check */
	if (year < 1)
		return (ERROR);
	
	if (year > 1582)	/* gregorian calendar */
		return ((!(year % 4) && year % 100 ) || !(year % 400));	
	else			/* julian calendar */
		return (!(year % 4));
}

extern void
date_init(struct DAY *date, int in_day, int in_month, int in_year)
{
	/*
	 * Function provides initialization of a new date.
	 */

	date->day = in_day;
	date->month = in_month;
	date->year = in_year;
	date->correct = date_correctness(*date);
}

extern int
date_correctness(struct DAY date)
{
	/*
	 * Function checks correctness of the given date.
	 * It returns 1 when date is correct and 0 otherwise.
	 */

		/* year correctness */
	if (date.year < 1) {
		return (0);
	}

		/* month correctness */
	if (date.month < 1 || date.month > 12)
		return (0);

		/* lower limit of days */
	if (date.day < 1)
		return (0);

		/* upper limit of days */
	switch (date.month) {
		case 1: case 3:
		case 5: case 7:
		case 8: case 10:
		case 12:
			if (date.day > 31)
				 return (0);
			break;
		case 4: case 6:
		case 9: case 11:
			if (date.day > 30)
				return (0);
			break;
		case 2:
			if (isLeap(date.year)) {
				if (date.day > 29)
					return (0);
			}
			else {
				if (date.day > 28)
					return (0);
			}
			break;
	}

		/* julian to gregorain calendar change*/
	if (date.year == 1582 && date.month == 10 && (date.day >= 5 && date.day <= 14))
		return (0);

	return (1);
}

extern int
date_compare(struct DAY date_1, struct DAY date_2)
{
	/*
	 * Function compares two dates. If the first date is after the second it returns 1.
	 * If the second date is after the first it returns -1. If dates are the same it returns 0.
	 * On error it returns ERROR.
	 */

		/* security check */
	if (!(date_1.correct && date_2.correct))
		return (ERROR);	

		/* comparison of years */
	if (date_1.year > date_2.year)
		return (1);
	if (date_1.year < date_2.year)
		return (-1);

		/* comparison of months */
	if (date_1.month > date_2.month)
		return (1);
	if (date_1.month < date_2.month)
		return (-1);

		/* comparison of days */
	if (date_1.day > date_2.day)
		return (1);
	if (date_1.day < date_2.day)
		return (-1);

	  /* dates are the same */
	return (0);
}

extern int
days_in_year(struct DAY date, int cal_change)
{
	/*
	 * Function returns number of days from the beginning of the year.
	 * If value of cal_change is true(different from 0), then the change
	 * of the calendar is considered and otherwise not.
	 */

		/* security check */
	if (!date.correct)
		return (ERROR);

	int counter = 0;

		/* If cal_change is true the lack of ten days in 1582
		   would be taken into consideration */
	if (cal_change && date.year == 1582) {
		struct DAY calendar_change_last_day = {4, 10, 1582, 1};
		if (date_compare(date, calendar_change_last_day) == 1)
			counter -= 10;
	}

		/* -1 because counting days in date's month is made separately */
	int months_left = date.month - 1;

		/* counting days in months before date's month */
	while (months_left > 0) {
		switch (months_left) {
			case 1: case 3:
			case 5: case 7:
			case 8: case 10:
			case 12:
				counter += 31;
				break;
			case 4: case 6:
			case 9: case 11:
				counter += 30;
				break;
			case 2:
				if (isLeap(date.year))
					counter += 29;
				else
					counter += 28;
				break;
		}
		months_left--;
	}

		/* counting days in date's month */
	counter += date.day;

	return (counter);
}

extern int
days(struct DAY date_1, struct DAY date_2)
{
	/*
	 * Function computes number of days between two dates.
	 * It returns number of days between or ERROR if one of dates
	 * is incorrect.
	 */

	int num_days = 0;

		/* security check */
	if (!(date_1.correct && date_2.correct))
		return (ERROR);

		/* setting order of dates */
	int tmp;
	struct DAY *later, *earlier;
	if ((tmp = date_compare(date_1, date_2)) == 1) {
		later = &date_1;
		earlier = &date_2;
	}
	else if (tmp == -1) {
		later = &date_2;
		earlier = &date_1;
	}
	else {	/* if dates are the same there were no days between them */
		return (0);
	}

		/*
		 * Difference between days from the beginning of the later
		 * year and the days from the beginning of the earlier date.
		 * If there were more days in the earlier date the negative 
		 * difference will be compensated later.
		 */
	num_days += days_in_year(*later, 0) - days_in_year(*earlier, 0);

	struct DAY calendar_change_checker = {10, 10, 1582, 1};

		/* calendar change */
	if (date_compare(*later, calendar_change_checker) == 1 &&
	    date_compare(*earlier, calendar_change_checker) == -1)
		num_days -= 10;

		/* in years difference */
	for (int year = earlier->year; year < later->year; year++) {
		if (isLeap(year))
			num_days += LEAP_YEAR_DAYS;
		else
			num_days += COMMON_YEAR_DAYS;
	}

	return (num_days);
}
