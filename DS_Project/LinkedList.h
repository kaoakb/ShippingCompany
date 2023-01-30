#pragma once
#include "Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T>* frontPtr;
	int count;

public:


	LinkedList()
	{
		frontPtr = nullptr;
		count = 0;
	}


	~LinkedList()
	{
		T temp;
		while (!isEmpty())
		{
			dequeue(temp);
		}
	}

	bool isEmpty() const
	{
		return !count;
	}

	bool enqueue(const T& data)
	{
		Node<T>* p = frontPtr;

		if (frontPtr)
		{
			while (p->getNext())
			{
				p = p->getNext();
			}
			Node<T>* R = new Node<T>(data);
			p->setNext(R);
		}
		else
		{
			Node<T>* R = new Node<T>(data);
			frontPtr = R;
		}
		count++;
		return true;
	}


	bool dequeue(T& itm)
	{
		if (isEmpty())
			return false;

		Node<T>* p = frontPtr;
		itm = frontPtr->getData();
		frontPtr = frontPtr->getNext();

		delete p;

		count--;
		return true;

	}


	bool remove(const int key, T& itm)
	{
		Node<T>* p = frontPtr;
		Node<T>* m;
		if (p &&( *(p->getData())) == key)
		{
			return dequeue(itm);
		}

		while (p)
		{

			if (p->getNext() && *(p->getNext()->getData()) == key)
			{
				m = p->getNext();
				p->setNext(p->getNext()->getNext());
				itm = m->getData();
				delete m;
				count--;
				return true;
			}
			else
				p = p->getNext();
		}
		return false;
	}

	int getCount()
	{
		return count;
	}

	bool peekFront(T& frntEntry) const
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->getData();
		return true;

	}
	void print()
	{
		if (isEmpty())
			return;
		Node<T>* ptr = frontPtr;
		while (ptr->getNext())
		{
			cout << *(ptr->getData());
			cout << ",";

			ptr = ptr->getNext();
		}
		cout <<*( ptr->getData());
	}
};