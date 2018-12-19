#ifndef days_h
#define days_h

	/* Allow C++ */
#ifdef __cplusplus
extern "C++" {
#endif


	/* Definition of macros */
#define COMMON_YEAR_DAYS 365
#define LEAP_YEAR_DAYS 366
#define ERROR (-2)

	/* Structure containing date */
struct DAY {
	int day;
	int month;
	int year;
	int correct;	/* Correctness of date */
};

	/* Number of days between two dates */
extern int days(struct DAY date_1, struct DAY date_2);

	/* Check if year is a leap year */
extern int isLeap(int year);

	/* Check correctness of date */
extern int date_correctness(struct DAY date);

	/* Date comparison */
extern int date_compare(struct DAY date_1, struct DAY date_2);

	/* Initialization of date with values and checking 
	   correctness also */
extern void date_init(struct DAY *date, int in_day, int in_month,
		int in_year);

	/* Number of days in particular year up to given date */
extern int days_in_year(struct DAY date, int cal_change);

	/* End C++ */
#ifdef __cplusplus
}
#endif

#endif
