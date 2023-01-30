#pragma once
#include<iostream>
#include "Node.h"

using namespace std;

template <typename T>
class Queue
{
	Node<T>* frtPtr;
	Node<T>* backPtr;
	int count;
public:
	Queue()
	{
		frtPtr = NULL;
		backPtr = NULL;
		count = 0;
	}
	bool enqueue(const T& newEntry)
	{
		Node<T>* newNodePtr = new Node<T>(newEntry);
		// Insert the new node 
		if (isEmpty())
			frtPtr = newNodePtr; // The queue was empty 
		else
			backPtr->setNext(newNodePtr); // The queue was not empty 
		backPtr = newNodePtr; // New node is at back 
		count++;
		return true;
	}
	bool dequeue(T& item) {

		bool result = false;
		if (!isEmpty())
		{
			// Queue is not empty; remove front 
			Node<T>* nodeToDeletePtr = frtPtr;
			item = frtPtr->getData();
			if (frtPtr == backPtr)
			{ // Special case: one node in queue 
				frtPtr = nullptr;
				backPtr = nullptr;
			}
			else
				frtPtr = frtPtr->getNext();
			// Return deleted node to system 
			nodeToDeletePtr->setNext(nullptr);
			delete nodeToDeletePtr;
			result = true;
			count--;
		} 
		return result;
	}

	int Getcount() { return count; }
	bool peek(T & temp)
	{
		if (isEmpty())
			return false;
		temp = frtPtr->getData();
		return true;
	}

	bool isEmpty()
	{
		return(frtPtr == NULL);
	}
	void print()
	{
		if (isEmpty())
			return;
		Node<T>* ptr = frtPtr;
		while (ptr->getNext())
		{
			cout << *(ptr->getData());
			cout << ",";
			ptr = ptr->getNext();
		}
		cout << *(ptr->getData());
	}
	~Queue()
	{
		T temp;
		while (!isEmpty())
		{
			dequeue(temp);
		}
	}
};