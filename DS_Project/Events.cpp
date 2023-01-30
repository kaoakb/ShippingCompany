#include "Events.h"
#include "Events.h"
#include"PreparationEvent.h"
#include"PromoteEvent.h"
#include"CancelEvent.h"
Events::Events(Company* Cptr)
{
	Cpointer = Cptr;
}
Events::Events(DaynHour t, int id , Company* Cptr)
{
	ET = t;
	CargoID = id;
	Cpointer = Cptr;
}

DaynHour Events::GetEventTime()
{
	return ET;
}

void Events::SetEventTime(DaynHour t)
{
	ET = t;
}

int Events::GetCargoID()
{
	return CargoID;
}

void Events::SetCargoID(int id)
{
	CargoID = id;
}
