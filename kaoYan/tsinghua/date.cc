#include <stdio.h>

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

	int d1, m1, y1;
	int d2, m2, y2;

	while (scanf("%4d%2d%2d", &y1, &m1, &d1) != EOF) {
		printf("%d\n", buf[y1][m1][d1]-buf[y1][1][1]+1);
	}

	return 0;
}
