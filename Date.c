#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Date.h"
#include "StringToolBox.h"

const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };


void getCorrectDate(Date* pDate) {
    char date[MAX_STR_LEN];
    int ok = 1;

    do {
        puts("Enter Date dd/mm/yyyy\t");
        fflush(stdin); // Flush the input buffer to remove any leftover newline characters
        myGets(date, MAX_STR_LEN, stdin);
        ok = checkDate(date, pDate);
        if (!ok)
            printf("Error try again\n");
    } while (!ok);
}


int	 checkDate(char* date, Date* pDate)
{
	int day, month, year;
	if (strlen(date) != 10)
		return 0;
	if ( (date[2] != '/') || (date[5] != '/'))
		return 0;
	sscanf(date, "%d/%d/%d", &day, &month, &year);
	if (day < 1 || month < 1 || month > 12 || year < MIN_YEAR)
		return 0;

	if (day > DAY_MONTHS[month - 1])
		return 0;

	pDate->day = day;
	pDate->month = month;
	pDate->year = year;

	return 1;
}

void printDate(const Date* pDate)
{
	printf("Date: %02d/%02d/%4d\t", pDate->day, pDate->month, pDate->year);
}

char*  createDateString(const Date* pDate)
{
	char str[MAX_STR_LEN];
	sprintf(str,"Date: %02d/%02d/%4d\t", pDate->day, pDate->month, pDate->year);

	return getDynStr(str);
}

int		 equalDate(const Date* pDate1, const Date* pDate2)
{
	if (pDate1->year == pDate2->year &&
		pDate1->month == pDate2->month &&
		pDate1->day == pDate2->day)
		return 1;
	return 0;

}

int		compareDate(const void* d1, const void* d2){
    const Date* pDate1 = (const Date*)d1;
    const Date* pDate2 = (const Date*)d2;
    if (pDate1->year > pDate2->year)
        return 1;
    if (pDate1->year < pDate2->year)
        return -1;

    if (pDate1->month > pDate2->month)
        return 1;

    if (pDate1->month < pDate2->month)
        return -1;

    if (pDate1->day > pDate2->day)
        return 1;

    if (pDate1->day < pDate2->day)
        return -1;

    return 0;
}

void setCurrentDate(Date* datePtr) {
    if (datePtr == NULL) {
        printf("Error: NULL pointer received.\n");
        return;
    }

    time_t now;
    struct tm* localTime;

    // Get the current time
    now = time(NULL);
    localTime = localtime(&now);

    // Update the fields of the Date struct with the current date
    datePtr->day = localTime->tm_mday;
    datePtr->month = localTime->tm_mon + 1;  // tm_mon is 0-indexed, so add 1
    datePtr->year = localTime->tm_year + 1900;  // tm_year is years since 1900
}