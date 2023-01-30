#include "PromoteEvent.h"
#include "PromoteEvent.h"
#include<fstream>
PromoteEvent::PromoteEvent(Company* Cptr):Events(Cptr)
{
}
PromoteEvent::PromoteEvent(DaynHour t, int id, Company* Cptr, int Pcost):Events(t,id,Cptr)
{
	pcost = Pcost;
}

bool PromoteEvent::Excute()
{
	Cargo* promcargo;
	bool exist=Cpointer->DequeueNCargo(GetCargoID(), promcargo);
	if(!exist)
		//error message should be printed
	return false;
	promcargo->SetCost(promcargo->GetCost() + pcost);
	promcargo->SetType(type::vip);
	exist = Cpointer->EnqueueCargo(promcargo,type::vip);
	return exist;
}
void PromoteEvent::load(ifstream& infile, int type, string file)
{
	string tim2;
	infile >> tim2;
	DaynHour d1(tim2);
	ET = d1;
	int i;
	infile >> i;
	CargoID = i;
	int cost;
	infile >> cost;
	pcost = cost;
}
