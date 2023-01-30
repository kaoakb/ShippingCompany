#pragma once
#include "Cargo.h"
#include "LinkedList.h"
#include "Queue.h"
#include"PriQ.h"
#include "Header.h"
class Events;
class UI;
#include "Truck.h"


class Company
{
private:
	int AutoP;
	UI* Modesptr;

	//Waiting cargos
	LinkedList <Cargo*> Cnormal;
	Queue <Cargo*> Cspecial;
	PriQ <Cargo*> Cvip;

	//Deliviered cargos
	Queue <Cargo*> DCargos;

	//Event list
	Queue <Events*> Eventactions;

	//Available trucks
	Queue <Truck*> Ntruck;
	Queue <Truck*> Vtruck;
	Queue <Truck*> Struck;

	//Moving trucks
	PriQ <Truck*> Mtrucks;

	//loading trucks
	Truck* truck1;
	Truck* truck2;
	Truck* truck3;

	//In-check trucks
	Queue <Truck*>Ntruksincheck;
	Queue <Truck*>Struksincheck;
	Queue <Truck*>Vtruksincheck;
	
	//CDT cargo
	PriQ <Cargo*> CDT;

	int numberjourney; //Number of journeys of trucks before Check-up
	int MaxW;
	int nevent;
	float CountAuto;
	float totalacttime;
	float totalutilization;

public:
	Company();
	bool PeakTruckNightShift(Truck*& T, type Ttype);
	bool getNnightshift(Truck*& t);
	bool getSnightshift(Truck*& t);
	bool getVnightshift(Truck*& t);

	bool peaktruckmaintaining(Truck*& T, type Ttype);
	bool Struckmaintaining();
	bool Vtruckmaintaining();
	bool Ntruckmaintaining();
	void deliveryfailure(Truck*& t, DaynHour currt);
	bool typeexist(type c);
	bool emptyexist();
	bool enqueueintrucks(Truck*& temp);
	Truck*& gettruck1();
	Truck*& gettruck2();
	Truck*& gettruck3();
	LinkedList <Cargo*>& getCnormal();
	Queue <Cargo*>& getCspecial();
	PriQ <Cargo*>& getCvip();
	Queue <Cargo*>& getDCargos();
	Queue <Truck*>& getNtruck();
	Queue <Truck*>& getVtruck();
	Queue <Truck*>& getStruck();
	PriQ <Truck*>& getMtrucks();
	Queue <Truck*>& getNtruksincheck();
	Queue <Truck*>& getStruksincheck();
	Queue <Truck*>& getVtruksincheck();

	void deliveredcargoscheck(DaynHour currT);
	void Simulation(DaynHour &CurrT);
	void modes(int modenum, DaynHour CurrT);
	void loadall(string file);
	bool DequeueNCargo(int id, Cargo*& C1);
	bool EnqueueCargo(Cargo* C1, type ctype);
	void truckFcheckTavail(DaynHour currT);
	void movingtrucksToavailAcheck(DaynHour currT);
	bool enqueueavailtrucks(Truck* truck);
	bool enqueuechecktrucks(Truck* truck);
	void loadingTrucktomoving(DaynHour currT);
	bool NormalCheckMaxW(DaynHour currT);
	bool SpecialCheckMaxW(DaynHour currT);
	bool VipCheckMaxW(DaynHour currT);
	void AutoPromotion(DaynHour CurrTime);
	void CargosAssignment(DaynHour currT);
	void laodingvip(DaynHour currT);
	void laodingnormal(DaynHour currT);
	void laodingspecial(DaynHour currT);
	void saveall(DaynHour currT);
	void setactivetimeandutilization(DaynHour currT);
	bool isWorkingHours(DaynHour currT);
};
