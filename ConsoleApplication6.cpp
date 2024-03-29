#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

struct datetime
{
	int second;
	int minute;
	int hour;
	int day;
	int month;
	int year;

	void out();
	bool getNext();
	bool getPrev();
};

void datetime::out()
{
	cout << "second: " << second << endl << " " << "minute: " << minute << endl 
		<< "hour: " << hour << endl << "day: " << day << endl 
		<< "month: " << month << endl << "year: " << year << endl;
}

struct MyStack
{
	struct Node
	{
		datetime data;
		Node *prev;
	};
	Node *Top = NULL;
	int Count = 0;

	bool Push(datetime);
	bool Pop(datetime&);
	void Info();
	void clear(datetime&);
};

bool MyStack::Push(datetime data)
{
	if (!Top)
	{
		Top = new Node;
		Top->prev = NULL;
		Count = 1;
	}
	else
	{
		Node *temp;
		temp = new Node;
		temp->prev = Top;
		Top = temp;
		Count++;
	}
	Top->data = data;
	return true;
}

bool MyStack::Pop(datetime&data)
{
	if (!Top) return false;
	Node *temp = Top->prev;
	data = Top->data;
	delete Top;
	Top = temp;
	Count--;
	return true;
}

void MyStack::Info()
{
	if (!Top) cout << "Stack is empty" << endl;
	else
	{
		cout << endl << "Stack info: " << endl;
		cout << "Stack size = " << Count << endl;
		Top->data.out();
	}
}

void MyStack::clear(datetime& k) {
	while (Count != 0) Pop(k);
}


struct MyQueue
{
	struct Node
	{
		char* data;
		int n;
		Node* next;
	};
	Node* First = NULL;
	int Count = 0;

	bool Push(char*, int n);
	bool Pop(char*&, int& n);
	void Info();
};
bool MyQueue::Push(char* data, int n)
{

	if (!First)
	{
		First = new Node;
		First->next = NULL;
		First->data = new char[n];
		First->n = n;
		for (int i = 0; i < n; i++) (First->data)[i] = data[i];
		Count = 1;
	}
	else
	{
		Node* temp;
		temp = First;
		while (temp->next != NULL) temp = temp->next;
		temp->next = new Node;
		temp->next->data = new char[n];
		temp->next->n = n;
		for (int i = 0; i < n; i++) (temp->next->data)[i] = data[i];
		temp->next->next = NULL;
		Count++;
	}
	return true;
}
bool MyQueue::Pop(char*& data, int& n)
{
	if (!First) return false;
	Node* temp = First->next;
	data = new char[n];
	n = First->n;
	for (int i = 0; i < First->n; i++) data[i] = (First->data)[i];
	delete[](First->data);
	delete First;
	First = temp;
	Count--;
	return true;
}
void MyQueue::Info()
{
	if (!First) cout << "Queue is empty" << endl;
	else
	{
		cout << endl << "Queue info: " << endl;
		cout << "\tQueue size = " << Count << endl;
	}
}

bool datetime::getNext()
{
	return false;
}

bool datetime::getPrev()
{
	return 0;
}

void read(MyStack& S, string FileName);

int main()
{

}

void read(MyStack& S, string FileName) {
	ifstream F(FileName);

	if (!F) {
		cout << "Error with loading file" << endl << endl;
		return;
	}

	datetime object;
	
	while (F >> object.second >> object.minute >> object.hour >> object.day
		>> object.month >> object.year) S.Push(object);

	F.close();
}