#ifndef __MYDATE__
#define __MYDATE__

#define MIN_YEAR 2020

typedef struct
{
	int			day;
	int			month;
	int			year;
}Date;

void	getCorrectDate(Date* pDate);
int		checkDate(char* date, Date* pDate);
void	printDate(const Date* pDate);
char*   createDateString(const Date* pDate);
int		compareDate(const void* d1, const void* d2);
void setCurrentDate(Date* datePtr);

int		 equalDate(const Date* pDate1, const Date* pDate2);
#endif

