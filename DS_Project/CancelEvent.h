#pragma once
#include "Events.h"
class CancelEvent : public Events
{
public:
	CancelEvent(Company* Cptr);
	void load(ifstream& infile, int type, string file);
	CancelEvent(DaynHour t, int id, Company* Cptr);
	bool Excute();
};

