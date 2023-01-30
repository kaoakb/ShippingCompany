#pragma once
#include "DaynHour.h"
#include"Header.h"
#include "Cargo.h"
#include <ostream>
#include "Queue.h"
#include "PriQ.h"

class Truck
{
	static int IDcounter;
	DaynHour movingtime;
	int truckcapacity;
	int maintenancetime;
	int speed;
	float deliveryinterval;
	int ID;
	type ttype;
	int maxj;
	PriQ<Cargo*> LCargo;//it has the id of the cargos it carry
	//the prioirty of the cargos in the truck is the distance
	int carriedcargos;
	int numofjourney;
	int endcheck;
	int endmoving;
	int endloading;
	float activetime;
	int numberofcargodeliverd;
	float utilization;
	int totalnumofjourney;
	bool maint;
	bool nightshift;
	int totaldist;
	//truck can have a pointer to the cargo type it load
public: 
	bool getnightshift();
	int gettotaldist();
	bool getmaint();
	void setmaint(bool t);
	float getactivetime(DaynHour currT);
	bool needsmainaience();
	void addjourney();
	DaynHour getmovingtime();
	Truck(int truckcapacity, int maintenancetime, int maxj, int speed, type ttype);
	Truck();
	int incheckpriority();
	void setincheckpriorty(DaynHour currT);
	int getID();
	int getspeed();
	int getTcapacity();
	void setTcapacity(int C);
	int Mtime();
	PriQ <Cargo*>& getCargosid();
	int Tspeed();
	void setTspeed(int s);
	float TdelivaryIn();
	void setDeliveryNum(int n);
	type gettype();
	int GetCarriedcargos();
	int MTpriority(DaynHour CurrTime);
	int LTpriority(DaynHour CurrTime);
	float GetMaxDistance();
	int GettotalLtime();
	int Getendmoving();
	int Getendloading();
	void setmovingtime(DaynHour currt);
	void resetjourneys();
	bool dequeueCargo(Cargo*& c);
	void enqueueCargo(Cargo* c);
	Cargo* & getCargo();
	float getutilization(DaynHour currT);
	void addcargodeliverd();
};
