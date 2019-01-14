#include <stdio.h>
#include <cstring>

#define ISYEAP(x)	((x)%100!=0 && (x)%4==0 || (x)%400==0)

int dayOfMonth[13][2] = {
	{0,  0},
	{31, 31},	//month 1
	{28, 29},
	{31, 31},
	{30, 30},
	{31, 31},
	{30, 30},
	{31, 31},
	{31, 31},
	{30, 30},
	{31, 31},
	{30, 30},
	{31, 31}
};

struct Date {
	int day;
	int month;
	int year;

	void nextDay() {
		day++;
		if (day > dayOfMonth[month][ISYEAP(year)]) {
			day = 1;	
			month++;
			if (month > 12) {
				month = 1;
				year++;
			}
		}
	}
};

int buf[5001][13][32];

char monthName[13][20] = {
	"",
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

char weekName[7][20] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};

int Abs(int x)
{
	return x < 0 ? -x : x;
}

int main(void)
{
	Date tmp;

	int cnt = 0;
	tmp.day = 1;
	tmp.month = 1;
	tmp.year = 0;

	while (tmp.year < 5001) {
		buf[tmp.year][tmp.month][tmp.day] = cnt;
		tmp.nextDay();
		cnt++;
	}

	int d, m, y;
	char s[20];

	printf("Pls input: \'day month year\'\n");

	while (scanf("%d%s%d", &d, s, &y) != EOF) {
		for (m = 1; m <= 12; ++m) {
			if (strcmp(s, monthName[m]) == 0) {
				break;
			}
		}

		int days = buf[y][m][d] - buf[2018][12][26];
		
		days += 3; //2018.12.26 is Wednesday, 
			   //so plus 3 is weekName's subindex.
		printf("%s", weekName[(days%7+7)%7]);
	}

	return 0;
}
