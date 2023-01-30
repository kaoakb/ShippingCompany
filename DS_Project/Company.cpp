#include "Company.h"
#include"DaynHour.h"
#include<fstream>
#include"Events.h"
#include"PreparationEvent.h"
#include"PromoteEvent.h"
#include"CancelEvent.h"
#include "UI.h"

Company::Company()
{
	CountAuto = 0;
	truck1 = truck2 = truck3 = nullptr;
	totalutilization = 0;
	totalacttime = 0;
}

bool Company::PeakTruckNightShift(Truck*& T,type Ttype)
{
	bool exit = false;
	Queue<Truck*>TempQ;
	Truck* tTemp;

	switch (Ttype)
	{
	case type::vip:
	{
		while (Vtruck.dequeue(tTemp))
		{
			if (tTemp->getnightshift() && !exit)
			{
				T= tTemp;
				exit = true;
			}
			TempQ.enqueue(tTemp);
		}

		while (TempQ.dequeue(tTemp))
			Vtruck.enqueue(tTemp);
		return exit;
	}

	case type::normal:
	{
		while (Ntruck.dequeue(tTemp))
		{
			if (tTemp->getnightshift() && !exit)
			{
				T = tTemp;
				exit = true;
			}
			TempQ.enqueue(tTemp);
		}

		while (TempQ.dequeue(tTemp))
			Ntruck.enqueue(tTemp);
		return exit;
	}

	case type::special:
	{
		while (Struck.dequeue(tTemp))
		{
			if (tTemp->getnightshift() && !exit)
			{
				T = tTemp;
				exit = true;
			}
			TempQ.enqueue(tTemp);
		}

		while (TempQ.dequeue(tTemp))
			Struck.enqueue(tTemp);
		return exit;
	}

	default:return false;
	}
	return false;
}

bool Company::getNnightshift(Truck*& t)
{
	bool exit = false;
	Queue<Truck*>temp;
	Truck* ttemp;
	while (Ntruck.dequeue(ttemp))
	{
		if (ttemp->getnightshift()&& !exit)
		{
			t = ttemp;
			exit = true;
		}
		else
		temp.enqueue(ttemp);
	}
	while (temp.dequeue(ttemp))
		Ntruck.enqueue(ttemp);
	return exit;
}
bool Company::getVnightshift(Truck*& t)
{
	bool exit = false;
	Queue<Truck*>temp;
	Truck* ttemp;
	while (Vtruck.dequeue(ttemp))
	{
		if (ttemp->getnightshift() && !exit)
		{
			t = ttemp;
			exit = true;
		}
		else
		temp.enqueue(ttemp);
	}
	while (temp.dequeue(ttemp))
		Vtruck.enqueue(ttemp);
	return exit;
}bool Company::getSnightshift(Truck*& t)
{
	bool exit = false;
	Queue<Truck*>temp;
	Truck* ttemp;
	while (Struck.dequeue(ttemp))
	{
		if (ttemp->getnightshift() && !exit)
		{
			t = ttemp;
			exit = true;
		}
		else
		temp.enqueue(ttemp);
	}
	while (temp.dequeue(ttemp))
		Struck.enqueue(ttemp);
	return exit;
}

bool Company::peaktruckmaintaining(Truck*& T, type Ttype)
{

	bool exit = false;
	Queue<Truck*>TempQ;
	Truck* tTemp;

	switch (Ttype)
	{
	case type::vip:
	{
		while (Vtruksincheck.dequeue(tTemp))
		{
			if (tTemp->getmaint() && !exit)
			{
				T = tTemp;
				exit = true;
			}
			TempQ.enqueue(tTemp);
		}

		while (TempQ.dequeue(tTemp))
			Vtruksincheck.enqueue(tTemp);
		return exit;
	}

	case type::normal:
	{
		while (Ntruksincheck.dequeue(tTemp))
		{
			if (tTemp->getmaint() && !exit)
			{
				T = tTemp;
				exit = true;
			}
			TempQ.enqueue(tTemp);
		}

		while (TempQ.dequeue(tTemp))
			Ntruksincheck.enqueue(tTemp);
		return exit;
	}

	case type::special:
	{
		while (Struksincheck.dequeue(tTemp))
		{
			if (tTemp->getmaint() && !exit)
			{
				T = tTemp;
				exit = true;
			}
			TempQ.enqueue(tTemp);
		}

		while (TempQ.dequeue(tTemp))
			Struksincheck.enqueue(tTemp);
		return exit;
	}

	default:return false;
	}
	return false;
}

bool Company::Struckmaintaining()
{
	Queue<Truck*>temp;
	Truck* t;
	bool exit = false;
	while (Struksincheck.dequeue(t))
	{
		if (t->getmaint())
		{
			if (Struck.isEmpty() && !exit)
			{
				exit = true;
				t->setmaint(false);
				t->setTspeed(t->getspeed() / 2);
				enqueueavailtrucks(t);
			}
			else
				temp.enqueue(t);
		}
		else
			temp.enqueue(t);
	}
	while (temp.dequeue(t))
		Struksincheck.enqueue(t);
	return exit;
}

bool Company::Vtruckmaintaining()
{
	bool exit = false;
	Queue<Truck*>temp;
	Truck* t;
	while (Vtruksincheck.dequeue(t))
	{
		if (t->getmaint())
		{
			if (Vtruck.isEmpty()&& !exit)
			{
				exit = true;
				t->setmaint(false);
				t->setTspeed(t->getspeed() / 2);
				enqueueavailtrucks(t);
			}
			else
				temp.enqueue(t);
		}
		else
			temp.enqueue(t);
	}
	while (temp.dequeue(t))
		Vtruksincheck.enqueue(t);
	return exit;
}

bool Company::Ntruckmaintaining()
{
	bool exit = false;
	Queue<Truck*>temp;
	Truck* t;
	while (Ntruksincheck.dequeue(t))
	{
		if (t->getmaint())
		{
			if (Ntruck.isEmpty() && !exit)
			{
				exit = true;
				t->setmaint(false);
				t->setTspeed(t->getspeed() / 2);
				enqueueavailtrucks(t);
			}
			else
				temp.enqueue(t);
		}
		else
			temp.enqueue(t);
	}
	while (temp.dequeue(t))
		Ntruksincheck.enqueue(t);
	return exit;
}

void Company::deliveryfailure(Truck*& t, DaynHour currt)
{
	Queue<Cargo*>temp;
	Queue<Cargo*>Atemp;
	DaynHour zero;
	Cargo* c;
	while (t->dequeueCargo(c))
	{
		c->ploadreset();
		c->settruck(nullptr);
		c->SetMovingTime(zero);
		temp.enqueue(c);
	}
	if (temp.peek(c))
	{
		switch (c->getctype())
		{
			//needs to reset the ploading
		case type::normal:
		{
			while (Cnormal.dequeue(c))
				Atemp.enqueue(c);
			while (temp.dequeue(c))
				Cnormal.enqueue(c);
			while (Atemp.dequeue(c))
				Cnormal.enqueue(c);
			break;

		}
		case type::special:
		{
			while (Cspecial.dequeue(c))
				Atemp.enqueue(c);
			while (temp.dequeue(c))
				Cspecial.enqueue(c);
			while (Atemp.dequeue(c))
				Cspecial.enqueue(c);
			break;

		}
		case type::vip:
		{
			while (Cvip.dequeue(c))
				Atemp.enqueue(c);
			while (temp.dequeue(c))
				Cvip.enqueue(c, c->getVipprioity());
			while (Atemp.dequeue(c))
				Cvip.enqueue(c, c->getVipprioity());
			break;

		}
		}
	}
		t->setincheckpriorty(currt);
		t->setmovingtime(currt);
		t->MTpriority(currt);//it should br called ans set nexttime before moving its written here only for better debug
		t->resetjourneys();//function implementaion need changing
		enqueuechecktrucks(t);
	
}

bool Company::typeexist(type c)
{
	if (truck1)
	{
		if (truck1->getCargo())
		{
			if (truck1->getCargo()->getctype() == c)
				return true;
		}
	}
	if (truck2)
	{
		if (truck2->getCargo())
		{
			if (truck2->getCargo()->getctype() == c)
				return true;
		}
	}
	if (truck3)
	{
		if (truck3->getCargo())
		{
			if (truck3->getCargo()->getctype() == c)
				return true;
		}
	}
	return false;
}

bool Company::emptyexist()
{
	if (truck1 && truck2 && truck3)
	{		return false;
	}
	return true;
}

bool Company::enqueueintrucks(Truck*& temp)
{
	if (!truck1)
	{
		truck1 = temp;
		return true;
	}
	if (!truck2)
	{
		truck2 = temp;
		return true;
	}
	if (!truck3)
	{
		truck3 = temp;
		return true;
	}
	return false;
}

Truck*& Company::gettruck1()
{
	return truck1;
}

Truck*& Company::gettruck2()
{
	return truck2;
}

Truck*& Company::gettruck3()
{
	return truck3;
}
LinkedList<Cargo*>& Company::getCnormal()
{
	return Cnormal;
}
Queue<Cargo*>& Company::getCspecial()
{
	return Cspecial;
}
PriQ<Cargo*>& Company::getCvip()
{
	return Cvip;
}

Queue<Cargo*>& Company::getDCargos()
{
	return DCargos;
}

Queue<Truck*>& Company::getNtruck()
{
	return Ntruck;
}
Queue<Truck*>& Company::getVtruck()
{
	return Vtruck;
}
Queue<Truck*>& Company::getStruck()
{
	return Struck;
}
PriQ<Truck*>& Company::getMtrucks()
{
	return Mtrucks;
}
Queue<Truck*>& Company::getNtruksincheck()
{
	return Ntruksincheck;
}
Queue<Truck*>& Company::getStruksincheck()
{
	return Struksincheck;
}
Queue<Truck*>& Company::getVtruksincheck()
{
	return Vtruksincheck;
}

void Company::deliveredcargoscheck(DaynHour currT)
{
	Cargo* temp = nullptr;
	Cargo* temp2 = nullptr;
	Truck* ttemp;
	Queue<Truck*>qtemp;
	while (Mtrucks.dequeue(ttemp))
	{
		temp=ttemp->getCargo();
		if (temp && currT.DaytoHours() >= temp->getendmoving().DaytoHours())
		{
			if (!ttemp->dequeueCargo(temp))
				break;
			ttemp->addcargodeliverd();
			DCargos.enqueue(temp);
			temp2 = ttemp->getCargo();
			if (temp2)
			{
				temp2->setploading(temp->GetLtime()+temp->getploading());
			}
			CDT.enqueue(temp, temp->GetCargodeliverytime().DaytoHours());
		}
		qtemp.enqueue(ttemp);

	}
	while (qtemp.dequeue(ttemp))
		Mtrucks.enqueue(ttemp, ttemp->Getendmoving());
}

void Company::Simulation(DaynHour& CurrT)
{
	cout << "please enter 0 for interactive mode, 1 for step by step mode and 2 for silent mode " << endl;
	int mode;
	cin >> mode;
	while (!Eventactions.isEmpty() || !Mtrucks.isEmpty() || truck1||truck2||truck3 ||!Cnormal.isEmpty()||!Cspecial.isEmpty()||!Cvip.isEmpty()||!Vtruksincheck.isEmpty()||!Struksincheck.isEmpty()||!Ntruksincheck.isEmpty())
	{

		if (CurrT.gethours() >= 5 && CurrT.gethours() <= 23)
		{
			Events* tempe;
			while (Eventactions.peek(tempe))
			{
				if (tempe->GetEventTime() == CurrT)
				{
					Eventactions.dequeue(tempe);
					tempe->Excute();
					delete tempe;
				}
				else
				{
					break;
				}
			}
			AutoPromotion(CurrT);
			CargosAssignment(CurrT);
			loadingTrucktomoving(CurrT);
			deliveredcargoscheck(CurrT);
			movingtrucksToavailAcheck(CurrT);
			truckFcheckTavail( CurrT);
			CargosAssignment(CurrT);
		}
		else
		{
			Events* tempe;
			while (Eventactions.peek(tempe))
			{
				if (tempe->GetEventTime() == CurrT)
				{
					Eventactions.dequeue(tempe);
					delete tempe;
					tempe = nullptr;
				}
				else
				{
					break;
				}
			}
			CargosAssignment(CurrT);
			loadingTrucktomoving(CurrT);
			deliveredcargoscheck(CurrT);
			movingtrucksToavailAcheck(CurrT);
			truckFcheckTavail(CurrT);
			CargosAssignment(CurrT);
		}
		modes(mode, CurrT);
		++CurrT;

	}
}

void Company::modes(int modenum, DaynHour CurrT)
{
	Modesptr = new UI(this);
	switch (modenum)
	{
	case 0:
	{
		Modesptr->Interactivemode(CurrT);
		break;
	}
	case 1:
	{
		Modesptr->Step_by_Step(CurrT);
		break;
	}
	case 2:
	{
		Modesptr->Silentmode(CurrT);
		break;
	}
	default:
	{
		string msg = "you did not choose any mode to display ";
		Modesptr->printmessage(msg);
		exit(1);
	}
	}



}



bool Company::DequeueNCargo(int id, Cargo*& C1)
{
	return Cnormal.remove(id, C1);

}



bool Company::EnqueueCargo(Cargo* C1, type ctype)
{
	switch (ctype)
	{
	case type::vip:
	{
		return Cvip.enqueue(C1, C1->getVipprioity());
	}
	case type::special:
	{
		return Cspecial.enqueue(C1);
	}
	case type::normal:
	{
		return Cnormal.enqueue(C1);
	}
	default:
		return false;
	}
}

void Company::truckFcheckTavail(DaynHour currT)
{
	Truck* removet = nullptr;

	while (Vtruksincheck.peek(removet))
	{
		if (currT.DaytoHours() >= removet->incheckpriority())
		{
			Vtruksincheck.dequeue(removet);
			Vtruck.enqueue(removet);
		}
		else break;
	}
	while (Struksincheck.peek(removet))
	{
		if (currT.DaytoHours() >= removet->incheckpriority()){
			Struksincheck.dequeue(removet);
			Struck.enqueue(removet);
		}
		else
			break;
	}
	while (Ntruksincheck.peek(removet))
	{
		if (currT.DaytoHours() >= removet->incheckpriority())
		{
			Ntruksincheck.dequeue(removet);
			Ntruck.enqueue(removet);
		}
		else
			break;
	}
}

void Company::movingtrucksToavailAcheck(DaynHour currT)
{
	int count = 0;
	Truck* removet = nullptr;
	deliveredcargoscheck(currT);
	while (Mtrucks.peek(removet))
	{
		count++;
		if (currT.DaytoHours() % 22 == 0&&count==1)
		{ 
			deliveryfailure(removet, currT);
			Mtrucks.dequeue(removet);
		}
		else if (currT.DaytoHours() >= removet->Getendmoving())
		{
			Mtrucks.dequeue(removet);
			if (removet->needsmainaience())
			{
				removet->setincheckpriorty(currT);
				removet->resetjourneys();
				enqueuechecktrucks(removet);
			}
			else if (removet->gettotaldist() >= 500)
			{
				removet->setincheckpriorty(currT);
				removet->resetjourneys();
				removet->setmaint(true);
				enqueuechecktrucks(removet);
			}
			else
			{
				enqueueavailtrucks(removet);

			}
		}
		else
			break;
	
	}
}

bool Company::enqueueavailtrucks(Truck* truck)
{
	switch (truck->gettype())
	{
	case type::vip:
	{
		return Vtruck.enqueue(truck);
	}
	case type::special:
	{
		return Struck.enqueue(truck);
	}
	case type::normal:
	{
		return Ntruck.enqueue(truck);
	}
	default:
		return false;
	}
}

bool Company::enqueuechecktrucks(Truck* truck)
{
	switch (truck->gettype())
	{
	case type::vip:
	{
		return Vtruksincheck.enqueue(truck);
	}
	case type::special:
	{
		return Struksincheck.enqueue(truck);
	}
	case type::normal:
	{
		return Ntruksincheck.enqueue(truck);
	}
	default:
		return false;
	}
}

void Company::loadingTrucktomoving(DaynHour currT)
{	
		if (truck1 && currT.DaytoHours() >= truck1->Getendloading())
		{
			truck1->addjourney();
			truck1->setmovingtime(currT);
			Mtrucks.enqueue(truck1, truck1->MTpriority(currT));
			truck1 = nullptr;
		}
		 if (truck2 && currT.DaytoHours() >= truck2->Getendloading())
		{
			truck2->addjourney();
			truck2->setmovingtime(currT);
			Mtrucks.enqueue(truck2, truck2->MTpriority(currT));
			truck2 = nullptr;
		}
		 if (truck3 &&  currT.DaytoHours()>= truck3->Getendloading())
		{
			truck3->addjourney();
			truck3->setmovingtime(currT);
			Mtrucks.enqueue(truck3, truck3->MTpriority(currT));
			truck3 = nullptr;
		}
		
	
}

bool Company::NormalCheckMaxW(DaynHour currT)
{
	Cargo* Ncargo = nullptr;
	Truck* AvaNTruck = nullptr;
	Truck* AvaVTruck = nullptr;
	int count = 0;
	if (!emptyexist())
		return false;
	if (typeexist(type::normal))
		return false;
	
	if (Cnormal.peekFront(Ncargo) && Ncargo->GetWaitingtime(currT).DaytoHours() >= MaxW)
	{
		if (isWorkingHours(currT))
		{
			if (Ntruck.isEmpty() && Vtruck.isEmpty())
			{
				if (!Ntruckmaintaining() && !Vtruckmaintaining())
					return false;
			}
			if (Ntruck.peek(AvaNTruck))
				Ntruck.dequeue(AvaNTruck);
			else if (Vtruck.peek(AvaVTruck))
				Vtruck.dequeue(AvaVTruck);
		}
		else
		{
			if (!getNnightshift(AvaNTruck) && !getVnightshift(AvaVTruck))
			{
				return false;
			}
		}
		if (AvaNTruck)
		{
			while (count < AvaNTruck->getTcapacity() && Cnormal.peekFront(Ncargo) && Ncargo->GetWaitingtime(currT).DaytoHours() >= MaxW)
			{
				Cnormal.dequeue(Ncargo);
				AvaNTruck->enqueueCargo(Ncargo);
				count++;
				Ncargo->settruck(AvaNTruck);
			}
			AvaNTruck->LTpriority(currT);
			enqueueintrucks(AvaNTruck);
			return true;
		}
		if (AvaVTruck)
		{
			while (count < AvaVTruck->getTcapacity() && Cnormal.peekFront(Ncargo) && Ncargo->GetWaitingtime(currT).DaytoHours() >= MaxW)
			{
				Cnormal.dequeue(Ncargo);
				AvaVTruck->enqueueCargo(Ncargo);
				Ncargo->settruck(AvaVTruck);
				count++;
			}
			AvaVTruck->LTpriority(currT);
			enqueueintrucks(AvaVTruck);
			return true;
		}
	}
	return false;
}

bool Company::SpecialCheckMaxW(DaynHour currT)
{
	Cargo* Scargo = nullptr;
	Truck* AvaSTruck = nullptr;
	int count = 0;
	if (!emptyexist())
		return false;
		if (typeexist(type::special))
			return false;
		/*if (Cspecial.peek(Scargo) && Scargo->GetWaitingtime(currT).DaytoHours() >= MaxW)
			truckmaintaining();*/
	if (Cspecial.peek(Scargo) && Scargo->GetWaitingtime(currT).DaytoHours() >= MaxW)
	{
		if (isWorkingHours(currT)&& Struck.peek(AvaSTruck))
		{
			if (Struck.isEmpty())
			{
				if (!Struckmaintaining())
					return false;
			}
			Struck.dequeue(AvaSTruck);
		}
		else
		{
			if (!getSnightshift(AvaSTruck))
				return false;
		}

		if (AvaSTruck)
		{
			while (count < AvaSTruck->getTcapacity() && Cspecial.peek(Scargo) && Scargo->GetWaitingtime(currT).DaytoHours() >= MaxW)
			{
				Cspecial.dequeue(Scargo);
				Scargo->settruck(AvaSTruck);
				AvaSTruck->enqueueCargo(Scargo);
				count++;
			}
			AvaSTruck->LTpriority(currT);
			enqueueintrucks(AvaSTruck);
			return true;
		}
	}
	return false;
}

bool Company::VipCheckMaxW(DaynHour currT)
{
	Cargo* Vcargo = nullptr;
	Truck* AvaVTruck = nullptr;
	Truck* AvaNTruck = nullptr;
	Truck* AvaSTruck = nullptr;
	int count = 0;

	if (!emptyexist())
		return false;
	if (typeexist(type::vip))
		return false;

	if (Cvip.peek(Vcargo) && Vcargo->GetWaitingtime(currT).DaytoHours() >= MaxW)
	{
		if (isWorkingHours(currT))
		{
			if (Vtruck.isEmpty()&&Ntruck.isEmpty() && Vtruck.isEmpty())
			{
				if (!Vtruckmaintaining() &&!Ntruckmaintaining() && !Vtruckmaintaining())
					return false;
			}
			if (Vtruck.peek(AvaVTruck))
				Vtruck.dequeue(AvaVTruck);
			else if (Ntruck.peek(AvaNTruck))
				Ntruck.dequeue(AvaNTruck);
			else if (Struck.peek(AvaSTruck))
				Struck.dequeue(AvaSTruck);
		}
		else
		{
			if (!getVnightshift(AvaVTruck) && !getNnightshift(AvaNTruck) && !getSnightshift(AvaSTruck))
			{
				return false;
			}
		}

		if (AvaVTruck)
		{
			while (count < AvaVTruck->getTcapacity() && Cvip.peek(Vcargo) && Vcargo->GetWaitingtime(currT).DaytoHours() >= MaxW)
			{
				Cvip.dequeue(Vcargo);
				AvaVTruck->enqueueCargo(Vcargo);
				Vcargo->settruck(AvaVTruck);
				count++;
			}
			AvaVTruck->LTpriority(currT);
			enqueueintrucks(AvaVTruck);

			return true;
		}
		if (AvaNTruck)
		{
			while (count < AvaNTruck->getTcapacity() && Cvip.peek(Vcargo) && Vcargo->GetWaitingtime(currT).DaytoHours() >= MaxW)
			{
				Cvip.dequeue(Vcargo);
				AvaNTruck->enqueueCargo(Vcargo);
				count++;
				Vcargo->settruck(AvaNTruck);
			}

			AvaNTruck->LTpriority(currT);
			enqueueintrucks(AvaNTruck);
			return true;
		}

		if (AvaSTruck)
		{
			while (count < AvaSTruck->getTcapacity() && Cvip.peek(Vcargo) && Vcargo->GetWaitingtime(currT).DaytoHours() >= MaxW)
			{
				Cvip.dequeue(Vcargo);
				AvaSTruck->enqueueCargo(Vcargo);
				count++;
				Vcargo->settruck(AvaSTruck);
			}

			AvaSTruck->LTpriority(currT);
			enqueueintrucks(AvaSTruck);
			return true;
		}
	}
	return false;
}

void Company::AutoPromotion(DaynHour CurrTime)
{
	Cargo* Ncargo = nullptr;
	while (Cnormal.peekFront(Ncargo) && Ncargo->GetWaitingtime(CurrTime).getday() >= AutoP)
	{
		Cnormal.dequeue(Ncargo);
		Ncargo->SetType(type::vip);
		Cvip.enqueue(Ncargo, Ncargo->getVipprioity());
		CountAuto++;
	}
}

void Company::laodingvip(DaynHour currT)
{
	Truck* ttempv = nullptr;
	Truck* ttempn = nullptr;
	Truck* ttemps = nullptr;
	if (!emptyexist())
		return;
	if (typeexist(type::vip))
		return;
	if (isWorkingHours(currT))
	{
		Vtruck.peek(ttempv);
		if (!ttempv)
		{
			peaktruckmaintaining(ttempv, type::vip);
		}
		Ntruck.peek(ttempn);
		if (!ttempn)
		{
			peaktruckmaintaining(ttempn, type::normal);
		}
		Struck.peek(ttemps);
		if (!ttemps)
		{
			peaktruckmaintaining(ttemps, type::special);
		}
	}
	else
	{
		if (!PeakTruckNightShift(ttempv, type::vip) && !PeakTruckNightShift(ttempn, type::normal) && !PeakTruckNightShift(ttemps, type::special))
			return;
	}

	if (ttempv)
	{
		if (Cvip.getcount() >= ttempv->getTcapacity())
		{
			if (isWorkingHours(currT))
			{
				if (Vtruck.isEmpty())
					Vtruckmaintaining();
				Vtruck.dequeue(ttempv);
			}
			else
				getVnightshift(ttempv);

			for (size_t i = 0; i < ttempv->getTcapacity(); i++)
			{
				Cargo* ctemp;
				Cvip.dequeue(ctemp);
				ctemp->settruck(ttempv);
				ttempv->enqueueCargo(ctemp);
			}
			enqueueintrucks(ttempv);
			ttempv->LTpriority(currT);
		}
	}
	else if (ttempn)
	{
		if (Cvip.getcount() >= ttempn->getTcapacity())
		{
			if (isWorkingHours(currT))
			{
				if (Ntruck.isEmpty())
					Ntruckmaintaining();
				Ntruck.dequeue(ttempn);
			}
			else
				getNnightshift(ttempn);

			for (size_t i = 0; i < ttempn->getTcapacity(); i++)
			{
				Cargo* ctemp;
				Cvip.dequeue(ctemp);
				ctemp->settruck(ttempn);
				ttempn->enqueueCargo(ctemp);
			}
			enqueueintrucks(ttempn);
			ttempn->LTpriority(currT);
		}
	}
	else if (ttemps)
	{
		if (Cvip.getcount() >= ttemps->getTcapacity())
		{
			if (isWorkingHours(currT))
			{
				if (Struck.isEmpty())
					Struckmaintaining();
				Struck.dequeue(ttemps);
			}
			else
				getSnightshift(ttemps);

			for (size_t i = 0; i < ttemps->getTcapacity(); i++)
			{
				Cargo* ctemp;
				Cvip.dequeue(ctemp);
				ctemp->settruck(ttemps);
				ttemps->enqueueCargo(ctemp);
			}
			enqueueintrucks(ttemps);
			ttemps->LTpriority(currT);
		}
	}
}

void Company::laodingnormal(DaynHour currT)
{
	Truck* ttempv = nullptr;
	Truck* ttempn = nullptr;
	if (!emptyexist())
		return;
	if (typeexist(type::normal))
		return;
	if (isWorkingHours(currT))
	{
		Ntruck.peek(ttempn);
		if (!ttempn)
		{
			peaktruckmaintaining(ttempn, type::normal);
		}
		Vtruck.peek(ttempv);
		if (!ttempv)
		{
			peaktruckmaintaining(ttempv, type::vip);
		}
		
	}
	else
	{
		if (!PeakTruckNightShift(ttempn, type::normal) && !PeakTruckNightShift(ttempv, type::vip))
			return;
	}

	if (ttempn) 
	{
		if (Cnormal.getCount() >= ttempn->getTcapacity())
		{
			if (isWorkingHours(currT))
			{
				if (Ntruck.isEmpty())
					Ntruckmaintaining();
				Ntruck.dequeue(ttempn);
			}
			else
				getNnightshift(ttempn);

			for (size_t i = 0; i < ttempn->getTcapacity(); i++)
			{
				Cargo* ctemp;
				Cnormal.dequeue(ctemp);
				ctemp->settruck(ttempn);
				ttempn->enqueueCargo(ctemp);
			}
			enqueueintrucks(ttempn);
			ttempn->LTpriority(currT);
		}
	}
	else if (ttempv)
	{
		if (Cnormal.getCount() >= ttempv->getTcapacity())
		{
			if (isWorkingHours(currT))
			{
				if (Vtruck.isEmpty())
					Vtruckmaintaining();
				Vtruck.dequeue(ttempv);
			}
			else
				getVnightshift(ttempv);

			for (size_t i = 0; i < ttempv->getTcapacity(); i++)
			{
				Cargo* ctemp;
				Cnormal.dequeue(ctemp);
				ctemp->settruck(ttempv);
				ttempv->enqueueCargo(ctemp);
			}
			enqueueintrucks(ttempv);
			ttempv->LTpriority(currT);
		}
	}
}

void Company::laodingspecial(DaynHour currT)
{
	Truck* ttemps = nullptr;
	if (!emptyexist())
		return;
	if (typeexist(type::special))
		return;

	if (isWorkingHours(currT))
	{
		Struck.peek(ttemps);
		if (!ttemps)
			peaktruckmaintaining(ttemps, type::special);
	}
	else
		PeakTruckNightShift(ttemps, type::special);
	if (ttemps)
	{
		if (Cspecial.Getcount() >= ttemps->getTcapacity())
		{
			if (isWorkingHours(currT))
			{
				if (Struck.isEmpty())
					Struckmaintaining();
				Struck.dequeue(ttemps);

			}
			else
				getSnightshift(ttemps);
			for (size_t i = 0; i < ttemps->getTcapacity(); i++)
			{
				Cargo* ctemp;
				Cspecial.dequeue(ctemp);
				ctemp->settruck(ttemps);
				ttemps->enqueueCargo(ctemp);
			}
			enqueueintrucks(ttemps);
			ttemps->LTpriority(currT);
		}
	}
}

void Company::CargosAssignment(DaynHour currT)
{
		if(!VipCheckMaxW(currT))
		laodingvip(currT);
		if (!NormalCheckMaxW(currT))
			laodingnormal(currT);
		if (!SpecialCheckMaxW(currT))
			laodingspecial(currT);
		
}
void Company::loadall(string file)
{
	ifstream infile;
	infile.open(file, ios::in);
	if (infile.is_open())
	{
		int nn, ns, nv, chn, chs, chv, j, can, cas, cav, sn, ss, sv;
		infile >> nn >> ns >> nv;
		infile >> sn >> ss >> sv;
		infile >> can >> cas >> cav;
		infile >> j >> chn >> chs >> chv;
		numberjourney = j;
		for (size_t i = 0; i < nn; i++)
		{
			Truck* t = new Truck(can, chn, j, sn, type::normal);
			Ntruck.enqueue(t);
		}
		for (size_t i = 0; i < ns; i++)
		{
			Truck* t = new Truck(cas, chs, j, ss, type::special);
			Struck.enqueue(t);
		}
		for (size_t i = 0; i < nv; i++)
		{
			Truck* t = new Truck(cav, chv, j, sv, type::vip);
			Vtruck.enqueue(t);
		}
		int au, max;
		infile >> au >> max;
		AutoP = au;
		MaxW = max;
		int nev;
		infile >> nev;
		nevent = nev;
		for (size_t i = 0; i < nevent; i++)
		{
			char x;
			infile >> x;
			Events* Pre;
			switch (x)
			{
			case 'R':
			{
				Pre = new PreparationEvent(this);
				Pre->load(infile, 0, file);
				Eventactions.enqueue(Pre);
				break;
			}
			case 'P':
			{
				Pre = new PromoteEvent(this);
				Pre->load(infile, 1, file);
				Eventactions.enqueue(Pre);
				break;
			}
			case'X':
			{
				Pre = new CancelEvent(this);
				Pre->load(infile, 2, file);
				Eventactions.enqueue(Pre);
				break;
			}
			default:
				break;
			}
		}
	}
	else
	{
		Modesptr->printmessage("no file");
		exit(1);
	}
	infile.close();
}

void Company::saveall(DaynHour currT)
{
	string file;
	cout << "please enter the file name to save";
	cin >> file;
	file += ".txt";
	ofstream outfile;
	outfile.open(file, ios::out);
	if (outfile.is_open())
	{
		Queue <Cargo*>temp;
		outfile << "CDT  ID  PT  WT  TID" << endl;
		while (!CDT.isEmpty())
		{
			Cargo* c;
			CDT.dequeue(c);
			temp.enqueue(c);
			outfile << c->GetCargodeliverytime().getday() << ":" << c->GetCargodeliverytime().gethours() << "  " << c->getID() << "  " << c->GetPrepareTime().getday() << ":" << c->GetPrepareTime().gethours() << "  " << c->GetWaitingtime(currT).getday() << ":" << c->GetWaitingtime(currT).gethours() << "  " << c->GetTruck()->getID() << endl;
		}
		while (!temp.isEmpty())
		{
			Cargo* c;
			temp.dequeue(c);
			CDT.enqueue(c,c->GetCargodeliverytime().DaytoHours());
		}
		outfile << "........................................................." << endl;
		outfile << "........................................................." << endl;
		outfile << "Cargos:";
		int countvip = 0;
		int countnormal = 0;
		int countspecial = 0;
		int tmp = 0;
		while (!CDT.isEmpty())
		{
			Cargo* c;
			CDT.dequeue(c);
			if (c->getctype() == type::vip)
				countvip++;
			if (c->getctype() == type::normal)
				countnormal++;
			if (c->getctype() == type::special)
				countspecial++;
			temp.enqueue(c);
			tmp += c->GetWaitingtime(currT).DaytoHours();
		}
		while (!temp.isEmpty())
		{
			Cargo* c;
			temp.dequeue(c);
			CDT.enqueue(c, c->GetCargodeliverytime().DaytoHours());
		}
		outfile << CDT.getcount() << " [ N: " << countnormal << ", S: " << countspecial << ", V: " << countvip << "]" << endl;

		tmp = tmp / CDT.getcount();


		DaynHour d(tmp);
		int totalnormal = countnormal + CountAuto;
		outfile << "Cargo Avg Wait = " << d.getday() << ":" << d.gethours() << endl;

		outfile << "Auto-promoted Cargo : " << ((1.0*CountAuto) / totalnormal) * 100 << "%" << endl;

		outfile << "Truck: " << Ntruck.Getcount() + Vtruck.Getcount() + Struck.Getcount();

		outfile << " [ N: " << Ntruck.Getcount() << ", S: " << Struck.Getcount() << ", V: " << Vtruck.Getcount() << "]" << endl;

		setactivetimeandutilization(currT);
		outfile << " Avg Active time = " << (totalacttime * 100) << "%" << endl;

		outfile << " Avg utilization = " << totalutilization << "%" << endl;
	}
	else
	{
		cout << "Not Save" << "\n";
	}
	outfile.close();
}

void Company::setactivetimeandutilization(DaynHour currT)
{
	Truck* temp=nullptr;
	int total = (Ntruck.Getcount() + Vtruck.Getcount() + Struck.Getcount());
	while (Ntruck.dequeue(temp))
	{
		totalutilization += temp->getutilization(currT);
		totalacttime += temp->getactivetime(currT);
	}
	while (Struck.dequeue(temp))
	{
		totalutilization += temp->getutilization(currT);
		totalacttime += temp->getactivetime(currT);
	}
	while (Vtruck.dequeue(temp))
	{
		totalutilization = temp->getutilization(currT);
		totalacttime += temp->getactivetime(currT);
	}
	totalacttime = totalacttime / (total * currT.DaytoHours()) ;
	totalutilization = 100*totalutilization /total;
}

bool Company::isWorkingHours(DaynHour currT)
{
	return (currT.gethours() >= 5 && currT.gethours() <= 23);
}
