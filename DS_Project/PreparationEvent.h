#pragma once
#include "Events.h"
#include "Header.h"
class PreparationEvent : public Events
{
private:
	type cType;
	int DIST;
	int LT;
	double Cost;
public:
	PreparationEvent(Company* Cptr);
	PreparationEvent(DaynHour Cprepare, int Cload, int distance, double cost, int id, type c, Company* Cptr);
	bool Excute();
	void load(ifstream& infile, int type, string file);

};

