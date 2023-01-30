#include "DaynHour.h"

DaynHour::DaynHour()
{
	day = hours = 0;
}
DaynHour::DaynHour(int a)
{
	day = a / 24;
	hours = a % 24;
}
DaynHour::DaynHour(string a)
{
	string b;
	string c;
	int i = 0;
	for (i = 0; i < a.length(); i++)
	{

		if (a[i] == ':')
			break;
			b += a[i];
	}
	int j;
	for (j = i+1; j < a.length(); j++)
	{
			c += a[j];
	}
	day = stoi(b);
	hours = stoi(c);
}

void DaynHour::setday(int d)
{
	if (d > 0)
		day = d;
}

void DaynHour::sethours(int h)
{
	if (h > 0)
		hours = h;
	while (hours >= 24)
	{
		hours -= 24;
		day += 1;
	}
}

int DaynHour::getday()
{
	return day;
}

int DaynHour::gethours()
{
	return hours;
}
string DaynHour::stringdisplay()
{
	string currenttime = to_string(day);
	currenttime = currenttime + ":" + to_string(hours);
	return currenttime;
}

bool DaynHour::operator==(DaynHour t2)
{

	return (this->day==t2.getday()&&this->hours==t2.gethours());
}

void DaynHour::operator=(int t2)
{
	day = 0;
	hours = 0;
}

DaynHour DaynHour::operator-(DaynHour t2)
{
	int x = DaytoHours() - t2.DaytoHours();
	DaynHour difference(x);
	return difference;
}

DaynHour DaynHour::operator+(int t2)
{

	DaynHour sum;
	sum.sethours(hours + t2);
	int x = sum.getday() + day;
	sum.setday(x);
	return sum;
}

bool DaynHour::operator>=(DaynHour t2)
{
	if (day >= t2.day)
		return true;
	if (hours >= t2.hours)
		return true;
	return false;
}
bool DaynHour::operator<=(DaynHour t2)
{
	if (day <= t2.day)
		return true;
	if (hours <= t2.hours)
		return true;
	return false;
}

void DaynHour::operator++()
{
	sethours(hours + 1);
}

int DaynHour::DaytoHours()
{
	int num = day * 24 + hours;
	return num;
}
