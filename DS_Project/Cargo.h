#pragma once
#include "DaynHour.h"
#include "Header.h"
#include <ostream>


class Truck;
class Cargo
{
	DaynHour Cprepare;
	int Cload;
	int distance;
	double cost;
	type ctype;
	int ID;
	Truck* Movingtruck;
	DaynHour MovingTime;
	DaynHour EndMovingTime;
	DaynHour waitingtime;
	DaynHour cdt;
	int ploading;

public:
	int getploading();
	void ploadreset();
	void setploading(int t);
	Cargo(DaynHour Cprepare, int Cload, int distance, double cost, int id, type c);
	Cargo();
	int getVipprioity();
	void SetCost(int ncost);
	type getctype();
	void SetType(type t);
	double GetCost();
	int getID();
	DaynHour GetPrepareTime();
	bool operator==(int id);
	void setID(int i);
	int GetLtime();
	int GetDistance();
	void SetMovingTime(DaynHour c);
	DaynHour GetWaitingtime(DaynHour CurrTime);
	DaynHour GetCargodeliverytime();
	DaynHour getendmoving();
	bool SetEndMovingTime(DaynHour CurrTime);
	void settruck(Truck* t);
	Truck* GetTruck();
};

