#pragma once
#include "Events.h"
class PromoteEvent : public Events
{
	int pcost;
public:
	PromoteEvent(Company* Cptr);
	PromoteEvent(DaynHour t, int id, Company* Cptr, int Pcost);
	bool Excute();
	void load(ifstream& infile, int type, string file);
};

