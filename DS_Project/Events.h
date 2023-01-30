#pragma once
#include "DaynHour.h"
#include "Company.h"
#include "Cargo.h"
#include "Header.h"
class Events
{
protected:
	DaynHour ET;
	int CargoID;
	Company* Cpointer;
public:
	Events(Company* Cptr);
	Events(DaynHour t, int id, Company* Cptr);
	DaynHour GetEventTime();
	void SetEventTime(DaynHour t);
	int GetCargoID();
	void SetCargoID(int id);
	virtual bool Excute() = 0;
	virtual void load(ifstream& infile, int type, string file)=0;
};

