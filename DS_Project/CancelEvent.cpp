#include "CancelEvent.h"
#include<fstream>
CancelEvent::CancelEvent(DaynHour t, int id, Company* Cptr):Events(t,id,Cptr)
{
}

bool CancelEvent::Excute()
{
    Cargo* cancelCargo= nullptr;
    if (Cpointer->DequeueNCargo(CargoID, cancelCargo))
    {
        delete cancelCargo;
        cancelCargo = NULL;
        return true;
    }
    return false;
}
CancelEvent::CancelEvent(Company* Cptr):Events(Cptr)
{
}
void CancelEvent::load(ifstream& infile, int type, string file)
{
    string tim3;
    infile >> tim3;
    DaynHour d1(tim3);
    ET = d1;
    int i;
    infile >> i;
    CargoID = i;
}