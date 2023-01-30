#include "UI.h"

ostream& operator <<(ostream& out, Truck& CurrT)
{
	out << CurrT.getID();
	if (!CurrT.getCargo())
		return out;
	Cargo* ctemp=nullptr;
	Queue<Cargo*> qtemp;

	if (!CurrT.getCargosid().isEmpty())
	{
		CurrT.getCargosid().peek(ctemp);
		switch (ctemp->getctype())
		{
		case type::vip:
		{
			out << "{";
			while (CurrT.getCargosid().dequeue(ctemp))
			{
				qtemp.enqueue(ctemp);
				out << ctemp->getID();
				if (!CurrT.getCargosid().isEmpty())
					out << ",";
				else
					out << "}";
			}
			break;
		}
		case type::normal:
		{
			out << "[";
			while (CurrT.getCargosid().dequeue(ctemp))
			{
				qtemp.enqueue(ctemp);
				out << ctemp->getID();
				if (!CurrT.getCargosid().isEmpty())
					out << ",";
				else
					out << "]";
			}
			break;
		}
		case type::special:
		{
			
			out << "(";
			while (CurrT.getCargosid().dequeue(ctemp))
			{
				qtemp.enqueue(ctemp);
				out << ctemp->getID();
				if (!CurrT.getCargosid().isEmpty())
					out << ",";
				else
					out << ")";
			}
			break;
		}
		
		}
	}
	while (qtemp.dequeue(ctemp))
		CurrT.getCargosid().enqueue(ctemp,ctemp->GetDistance());//the prioirty of the cargos in the truck is the distance
	return out;
}

ostream& operator <<(ostream& out, Cargo& CurrC)
{

	out << CurrC.getID();
	return out;
}



UI::UI(Company* cptr)
{
	this->Cptr = cptr;
}

void UI::printmessage(string msg)
{
	cout << msg << endl;
}

void UI::Interactivemode(DaynHour CurrT)
{
	cin.ignore();
	//the output file should be produced
	cout << "Current Time (Day:Hour) :";
	string time = CurrT.stringdisplay();
	cout << time<<endl;
	printwaitingcargos();
	cout << "-----------------------------------------------------" << endl;
	printLoadingTrucks();
	cout << "-----------------------------------------------------" << endl;
	printEmptytruck();
	cout << "-----------------------------------------------------" << endl;
	printmovingcargos();
	cout << "-----------------------------------------------------" << endl;
	printincheckcTrucks();
	cout << "-----------------------------------------------------" << endl;
	printDeliveredCargos();
	cout << endl << endl;

}

void UI::Silentmode(DaynHour CurrT)
{
	if(CurrT.DaytoHours()==0)
	//the output file should be produced
	cout << "Silent Mode" << endl << "Simulation Starts" << endl << "Simulation Ends, output file created"<<endl;
}

void UI::Step_by_Step(DaynHour CurrT)
{
	//the output file should be produced
	cout << "Current Time (Day:Hour) :";
	string time = CurrT.stringdisplay();
	cout << time << endl;

	printwaitingcargos();
	cout << "-----------------------------------------------------" << endl;
	printLoadingTrucks();
	cout << "-----------------------------------------------------" << endl;
	printEmptytruck();
	cout << "-----------------------------------------------------" << endl;
	printmovingcargos();
	cout << "-----------------------------------------------------" << endl;
	printincheckcTrucks();
	cout << "-----------------------------------------------------" << endl;
	printDeliveredCargos();
	cout << endl << endl;
	//delivered.
	//it should take some time 
	Sleep(1000);
}

void UI::printincheckcTrucks()
{
	int num = (Cptr->getNtruksincheck().Getcount()) + (Cptr->getStruksincheck().Getcount()) + (Cptr->getVtruksincheck().Getcount());
	cout << num << " In-Check Trucks : [";
	Cptr->getNtruksincheck().print();
	cout << "] (";
	Cptr->getStruksincheck().print();
	cout << ") {";
	Cptr->getVtruksincheck().print();
	cout << "}" << endl;
}

void UI::printwaitingcargos()
{

	int num = (Cptr->getCnormal().getCount()) + (Cptr->getCspecial().Getcount()) + (Cptr->getCvip().getcount());
	cout << num<< " Waiting Cargos : [";
	Cptr->getCnormal().print();
	cout << "] (";
	Cptr->getCspecial().print();
	cout << ") {";
	Cptr->getCvip().print();
	cout << "}" << endl;
}

void UI::printmovingcargos()
{
	Truck* ttemp = nullptr;
	Queue<Truck*> qtemp;
	Cargo* temp;
	int num = 0;
	while (Cptr->getMtrucks().dequeue(ttemp))
	{
		qtemp.enqueue(ttemp);
		num += ttemp->getCargosid().getcount();		
	}
	cout << num << " Moving cargos :";
	while (qtemp.dequeue(ttemp))
	{
		cout << *ttemp<<"  ";
		Cptr->getMtrucks().enqueue(ttemp,ttemp->Getendmoving());
		
	}
	cout << endl;
}

void UI::printEmptytruck()
{
	int num = (Cptr->getNtruck().Getcount()) + (Cptr->getStruck().Getcount()) + (Cptr->getVtruck().Getcount());
	cout << num << " Empty Trucks :[";
	Cptr->getNtruck().print();
	cout << "] (";
	Cptr->getStruck().print();
	cout << ") {";
	Cptr->getVtruck().print();
	cout << "}" << endl;
}

void UI::printDeliveredCargos()
{
	int num = (Cptr->getDCargos().Getcount());
	cout << num << " Delivered Cargos :";
	Queue<Cargo*>qtemp;
	Cargo* ctemp = nullptr;
	while (Cptr->getDCargos().dequeue(ctemp))
	{
		qtemp.enqueue(ctemp);
		switch (ctemp->getctype())
		{
		case type::normal:
		{
			cout << "[" << *ctemp << "]";
			break;
		}
		case type::special:
		{
			cout << "(" << *ctemp << ")";
			break;

		}
		case type::vip:
		{
			cout << "{" << *ctemp << "}";
			break;
		}
		}
	}
	while (qtemp.dequeue(ctemp))
		Cptr->getDCargos().enqueue(ctemp);

	cout << endl;
}

void UI::printLoadingTrucks()
{
	int num = 0;
	if (Cptr->gettruck1())
		num++;
	if (Cptr->gettruck2())
		num++;
	if (Cptr->gettruck3())
		num++;
	cout << num << " Loading Trucks :";
	if (Cptr->gettruck1())
		cout << *(Cptr->gettruck1())<<"  " ;
	if (Cptr->gettruck2())
		cout << *(Cptr->gettruck2()) << "  ";
	if (Cptr->gettruck3())
		cout << *(Cptr->gettruck3()) << "  ";
	
	cout <<  endl;
}
