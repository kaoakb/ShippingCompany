#pragma once
#include <string>
#include <iostream>
using namespace std;
class DaynHour
{
	int day, hours;
public:

	DaynHour(string a);
	DaynHour(int a);
	DaynHour();
	void setday(int d);
	void sethours(int h);
	int getday();
	int gethours();
	string stringdisplay();
	bool operator == (DaynHour t2);
	void operator = ( int t2);
	
	DaynHour operator -(DaynHour t2);
	DaynHour operator +(int t2);
	bool operator >=(DaynHour t2);
	bool operator<=(DaynHour t2);
	void operator ++();
	int DaytoHours();
};

