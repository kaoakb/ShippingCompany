#include "Cargo.h"
#include "Truck.h"


int Cargo::getploading()
{
	return ploading;
}

void Cargo::ploadreset()
{
	
		ploading = 0;
	
}

void Cargo::setploading(int t)
{
	ploading += t;
}

Cargo::Cargo(DaynHour Cprepare, int Cload, int distance, double cost, int id, type c)
{
	this-> Cprepare= Cprepare;
	this-> Cload= Cload;
	this-> distance= distance;
	this-> cost=cost;
	this->ctype=c;
	this-> ID=id;
	waitingtime.setday(0) ;
	waitingtime.sethours(0);
	ploading = 0;

}
int Cargo::getVipprioity()
{

	float eq = (Cprepare.DaytoHours() * distance)/cost;
	int priority = eq * 100;
	return priority;
}
Cargo::Cargo()
{
	ploading = 0;
	cost= 0;
	waitingtime.setday(0);
	waitingtime.sethours(0);
}

void Cargo::SetCost(int ncost)
{
	cost = ncost;
}
type Cargo::getctype()
{
	return ctype;
}
void Cargo::SetType(type t)
{
	ctype = t;
}
double Cargo::GetCost()
{
	return cost;
}
int Cargo::getID()
{
	return ID;
}

DaynHour Cargo::GetPrepareTime()
{
	return Cprepare;
}

bool Cargo::operator==(int id)
{
	return ID==id;
}

void Cargo::setID(int i)
{
	ID = i;
}


DaynHour Cargo::GetWaitingtime(DaynHour CurrTime)
{
	DaynHour WT;

	if (!Movingtruck&&MovingTime.DaytoHours()==0)
	{
		WT = CurrTime - Cprepare;
	}
	else
		WT = MovingTime - Cprepare;

	return WT;
}


int Cargo::GetLtime()
{
	return Cload;
}

DaynHour Cargo::GetCargodeliverytime()
{
	return cdt;
}

DaynHour Cargo::getendmoving()
{
	return EndMovingTime + ploading;
}

int Cargo::GetDistance()
{
	return distance;
}

void Cargo::SetMovingTime(DaynHour c)
{
	MovingTime=c;
}

bool Cargo::SetEndMovingTime(DaynHour CurrTime)//to check if the current time is the time to be delivered
{
	EndMovingTime = CurrTime + ceil(1.0* distance / Movingtruck->getspeed())+Cload;
	cdt = CurrTime + ceil(1.0* distance / Movingtruck->getspeed())+Cload;
	return true;
}

void Cargo::settruck(Truck* t)
{
	Movingtruck = t;
}

Truck* Cargo::GetTruck()
{
	return Movingtruck;
}
