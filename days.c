#include "days.h"

int
isLeap(int year)
{
	return ((!(year % 4) && year % 100 ) || !(year % 400));
}

void
date_init(struct DAY *date, int in_day, int in_month, int in_year)
{
	date->day = in_day;
	date->month = in_month;
	date->year = in_year;
	date->correct = date_correctness(*date);
}

void
print_date(struct DAY date, int new_line)
{
	if (date.correct) {
		printf("%02d %02d %d", date.day, date.month, date.year);
		if (new_line)
			printf("\n");
	}
	else
		printf("\nerror!\nThere's no such a date:   %d %d %d\n\n", date.day,
						      date.month, date.year);
}

int
date_correctness(struct DAY date)
{
	/*
	 * Function checks correctness of given date.
	 * It returns 1 when date is correct and 0 otherwise.
	 */

		/* year correctness */
	if (date.year < 1) {
		return (0);
	}

	int leap = isLeap(date.year);

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
			if (leap) {
				if (date.day > 29)
					return (0);
			}
			else {
				if (date.day > 28)
					return (0);
			}
			break;
		default:
			return (0);
	}

		/* julian to gregorain calendar change*/
	if (date.year == 1582 && date.month == 10 && (date.day >= 5 && date.day <= 14))
		return (0);

	return (1);
}

int
date_compare(struct DAY date_1, struct DAY date_2)
{
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

int
days_in_year(struct DAY date, int cal_change)
{
		/* security check */
	if (!date.correct)
		return (ERROR);

	int counter = 0;

	if (date.year == 1582 && cal_change) {
		struct DAY calendar_change_last_day = {4, 10, 1582, 1};
		if (date_compare(date, calendar_change_last_day) == 1)
			counter -= 10;
	}

	int months_left = date.month - 1;

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

	counter += date.day;

	return (counter);
}

int
days(struct DAY date_1, struct DAY date_2)
{
	int num_days = 0;

		/* security check */
	if (!(date_1.correct && date_2.correct))
		return (ERROR);

	int tmp;
	struct DAY *max = NULL, *min = NULL;
	if ((tmp = date_compare(date_1, date_2)) == 1) {
		max = &date_1;
		min = &date_2;
	}
	else if (tmp == -1) {
		max = &date_2;
		min = &date_1;
	}
	else {
		return (0);
	}

		/* in days difference */
	num_days += days_in_year(*max, 0) - days_in_year(*min, 0);

	struct DAY calendar_change_checker = {10, 10, 1582, 1};

	if (date_compare(*max, calendar_change_checker) == 1 &&
	    date_compare(*min, calendar_change_checker) == -1)
		num_days -= 10;

		/* in years difference */
	for (int year = min->year; year < max->year; year++) {
		if (isLeap(year))
			num_days += LEAP_YEAR_DAYS;
		else
			num_days += COMMON_YEAR_DAYS;
	}

	return (num_days);
}
