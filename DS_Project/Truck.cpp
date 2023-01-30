#include "Truck.h"

int Truck::IDcounter = 1;

bool Truck::getmaint()
{
    return maint;
}

void Truck::setmaint(bool t)
{
    maint = t;
}

float Truck::getactivetime(DaynHour currT)
{
    return activetime;
}

bool Truck::needsmainaience()
{
    return numofjourney >= maxj;
}

void Truck::addjourney()
{
    numofjourney++;
    totalnumofjourney++;
}
DaynHour Truck::getmovingtime()
{
    return movingtime;
}


Truck::Truck(int truckcapacity, int maintenancetime, int maxj, int speed, type ttype)
{
    totaldist = 0;
    activetime = 0; 
    this->truckcapacity = truckcapacity;
    this->maintenancetime = maintenancetime;
    this->speed = speed;
    this->maxj = maxj;
    this->ttype = ttype;
    carriedcargos = 0;
    ID = IDcounter;
    IDcounter++;
    numofjourney = 0;
    endmoving = 0;
    totalnumofjourney = 0;
    maint = false;
    if (ID % 5 == 0)
        nightshift = true;
    else
        nightshift = false;
}

Truck::Truck()
{
    maint = false;
    totaldist = 0;
    endmoving = 0;
    numofjourney = 0;
    speed = 0;
    carriedcargos = 0;
    ID = IDcounter;
    IDcounter++;
    activetime = 0;
    totalnumofjourney = 0;
    if (ID % 5 == 0)
        nightshift = true;
    else
        nightshift = false;
}

int Truck::incheckpriority()
{
    return endcheck;

}
void Truck::setincheckpriorty(DaynHour currT)
{
    endcheck = maintenancetime + currT.DaytoHours();
}
int Truck::getID()
{
    return ID;
}

int Truck::getspeed()
{
    return speed;
}

int Truck::getTcapacity()
{
    return truckcapacity;
}

void Truck::setTcapacity(int C)
{
    truckcapacity = C;
}

int Truck::Mtime()
{
    return maintenancetime;
}

PriQ<Cargo*>& Truck::getCargosid()
{
    return  LCargo;
}

int Truck::Tspeed()
{
    return speed;
}

void Truck::setTspeed(int s)
{
    speed = s;
}

float Truck::TdelivaryIn()
{
    float max = GetMaxDistance();
    deliveryinterval = ceil((max /( speed)/1.0 ))* 2 + GettotalLtime();
    activetime+= ceil(((max / (speed/1.0))) + GettotalLtime()*2);
    return  deliveryinterval;
}



void Truck::setDeliveryNum(int n)
{
    maxj = n;
}



type Truck::gettype()
{
    return ttype;
}

int Truck::GetCarriedcargos()
{
    return carriedcargos;
}

int Truck::LTpriority(DaynHour CurrTime)//to calculate the end loading time to be dequeued from the trucks to moving
{
    int totalLT = GettotalLtime();
    endloading = CurrTime.DaytoHours() + totalLT;
    return CurrTime.DaytoHours() + totalLT;
}
bool Truck::getnightshift()
{
    return nightshift;
}
int Truck::gettotaldist()
{
    return totaldist;
}
float Truck::GetMaxDistance()
{
    Cargo* Ctemp=nullptr;
    Queue <Cargo*> Temp;

    float max =0;
    while (LCargo.dequeue(Ctemp))
    {
        if (max < Ctemp->GetDistance())
            max = Ctemp->GetDistance();
        Temp.enqueue(Ctemp);
    }
    while (Temp.dequeue(Ctemp))
    {
        LCargo.enqueue(Ctemp, Ctemp->GetDistance());
    }
    totaldist += 2*max;
    return max;
}
int Truck::GettotalLtime()
{
    Cargo* Ctemp = nullptr;
    Queue <Cargo*> Temp;

    int totalLT = 0;
    while (LCargo.dequeue(Ctemp))
    {
        totalLT += Ctemp->GetLtime();
        Temp.enqueue(Ctemp);
    }
    
    while (Temp.dequeue(Ctemp))
    {
        LCargo.enqueue(Ctemp, Ctemp->GetDistance());
    }
    return totalLT;
}
int Truck::Getendmoving()
{
    return endmoving;
}
int Truck::Getendloading()
{
    return endloading;//the time for all cargos be loaded and for it to be set LTpriority must be called in loading functions
}
void Truck::setmovingtime(DaynHour currt)
{
    movingtime = currt;

}
void Truck::resetjourneys()
{
    totaldist = 0;
    numofjourney=0;
}
void Truck::enqueueCargo(Cargo* c)
{
    carriedcargos++;
    LCargo.enqueue(c,c->GetDistance());
}
bool Truck::dequeueCargo(Cargo* &c)
{
    carriedcargos--;
  return  LCargo.dequeue(c);
}
Cargo* & Truck::getCargo()
{
    Cargo* C=nullptr;
    LCargo.peek(C);
    return C;
}
int Truck::MTpriority(DaynHour CurrTime)
{
    Cargo* Ctemp = nullptr;
    Queue <Cargo*> Temp;
    TdelivaryIn();
    while (LCargo.dequeue(Ctemp))
    {
      Ctemp->SetMovingTime(CurrTime);
      Ctemp->SetEndMovingTime(CurrTime);//to calculate the time for the cargos to be delevered
        Temp.enqueue(Ctemp);
    }
    while (Temp.dequeue(Ctemp))
    {
        LCargo.enqueue(Ctemp, Ctemp->GetDistance());
    }
    endmoving = CurrTime.DaytoHours() + deliveryinterval; //the time at which the truck leaves the moving DS
    return CurrTime.DaytoHours() + deliveryinterval;
}
float Truck::getutilization(DaynHour currT)
{
    if (totalnumofjourney == 0)
    {
        utilization = 0;
        return 0;
    }
    utilization = (numberofcargodeliverd / (truckcapacity * (totalnumofjourney/1.0))) * (activetime*1.0 / currT.DaytoHours());
    return utilization;
}
void Truck::addcargodeliverd()
{
    numberofcargodeliverd++;
}