#pragma once
#include <iostream>
#include <stdlib.h>
#include <cassert>
#include <math.h>
#include <string.h>
#define n 10

using namespace std;
//Walking on a Dream by Empire of the Sun
class CNode
{
public:
	CNode *next,*prev;
	double v[n];
	CNode();
	CNode(double *a);
	//~CNode();
	//void CopyOnly(const CNode &a);
	//CNode &operator=(const CNode &a);
	friend class CList;
};

class CList
{
private:
	CNode *begin,*cur,*end;
	int size;
public:
	CList();
	CList(int size);
	~CList();
	int IsEmpty();
	void Clean();
	void GoToBegin();
	void GoToEnd();
	int GoToNext();
	int GoToPrev();
	int GoToNode(int i);
	int GetCur(double *a);
	int DelCur();
	void AddAfter();
	void AddElement(const double x);
	void Put(const double x, int i);
	void Delete(int i);
	double* getpointer(int i);
	void resize(int newsize);
	int getsize();
	int search(double a);
	void sort();
	void output();
};
double shiftright(double b, double* a,int d);
void shiftleft(double b, double* a,int d);
