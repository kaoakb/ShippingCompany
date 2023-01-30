#pragma once
#include "DaynHour.h"
#include "Company.h"
#include "windows.h"

class UI
{
	Company* Cptr;
public:
	UI(Company* cptr);
	void printmessage(string msg);
	void Interactivemode(DaynHour CurrT);
	void Silentmode(DaynHour CurrT);
	void Step_by_Step(DaynHour CurrT);

	void printincheckcTrucks();
	void printwaitingcargos();
	void printmovingcargos();
	void printEmptytruck();
	void printDeliveredCargos();
	void printLoadingTrucks();

};

