#pragma once
#include <iostream>
#include "Node.h"



template <typename T>
class PriQ
{
private:
	Node<T>* Head;
	int count;
public:
	//Constructor
	PriQ()
	{
		Head = NULL;
		count = 0;
	}

	//Function that enqueues the elemtents sorted according to the key
	bool enqueue(T& newEntry, const int& newKey)
	{
		//Creating the new node to be inserted 
		Node<T>* temp = new Node<T>(newEntry, newKey);
		Node<T>* ptr;

		//If the entry is in the first place or the list is empty
		if (Head == NULL || (temp->getKey() < Head->getKey()))
		{
			temp->setNext(Head);
			Head = temp;
		}
		//General Case
		else
		{
			ptr = Head;
			while (ptr->getNext() != NULL && ptr->getNext()->getKey() <= temp->getKey())
				ptr = ptr->getNext();

			temp->setNext(ptr->getNext());
			ptr->setNext(temp);
		}
		count++;
		return true;
	}

	//Function the takes out elements out of the queue
	bool dequeue(T& item )
	{
		if (isEmpty())
			return false;

		Node<T>* nodeToDeletePtr = Head;
			item  = Head->getData();
		 Head = Head->getNext();
		 delete nodeToDeletePtr;
		 count--;
		return true;

	}

	int getcount() 
	{ 
		return count; 
	}

	//Function the checks the first element.
	bool peek(T& temp)
	{
		if (isEmpty())
			return false;

		temp = Head->getData();
		return true;

	}

	//Function that checks whether the queue is empty or not
	bool isEmpty()
	{
		return (Head == NULL);
	}

	void print() 
	{
		if (isEmpty())
			return ;

		Node<T>* ptr = Head;
		while (ptr->getNext())
		{
			cout << *(ptr->getData());
			cout << ",";

			ptr = ptr->getNext();
		}
		cout << *(ptr->getData());

	}
	~PriQ()
	{
		T temp;
		while (!isEmpty())
		{
			dequeue(temp);
		}
	}
};