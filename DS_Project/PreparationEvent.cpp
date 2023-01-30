#include "PreparationEvent.h"
#include "PreparationEvent.h"
#include<fstream>
#include"Header.h"
#include "Company.h"
#include<fstream>
#include"Events.h"
#include"PreparationEvent.h"
#include"DaynHour.h"
#include"PromoteEvent.h"
#include"CancelEvent.h"
#include "UI.h"
#include<iostream>
using namespace std;
PreparationEvent::PreparationEvent(Company* Cptr):Events(Cptr)
{

}

PreparationEvent::PreparationEvent(DaynHour Cprepare, int Cload, int distance, double cost, int id, type c, Company* Cptr)
	:Events(Cprepare, id,Cptr)
{
	 cType=c;
	 DIST=distance;
	 LT=Cload;
	 Cost=cost;
}

bool PreparationEvent::Excute()
{
	Cargo* ptr = new Cargo(ET, LT, DIST, Cost, CargoID, cType);
	return Cpointer->EnqueueCargo(ptr,cType);
}
void PreparationEvent::load(ifstream& infile, int type, string file)
{
	char y;
	infile >> y;
	if (y == 'N')
		cType = type::normal;
	if (y == 'S')
		cType = type::special;
	if (y == 'V')
		cType = type::vip;
	string tim1;
	infile >> tim1;
	DaynHour d1(tim1);
	ET = d1;
	int i;
	infile >> i;
	CargoID = i;
	int dist;
	infile >> dist;
	DIST = dist;
	int lhours;
	infile >> lhours;
	LT = lhours;
	int cost;
	infile >> cost;
	Cost = cost;

}