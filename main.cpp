#include "r.h"
#include <time.h>
int test1(int tm)
{
	srand(time(NULL)+tm);
	CList a(1000);
	int i=rand()%1000+1,sizem;
	sizem=a.getsize();
	const double x=((double)rand()/RAND_MAX)*pow(10,rand()%5)*pow(-1,rand());
	a.Put(x,i);
	if(fabs(*a.getpointer(i)-x)>=1e-15 || a.getsize()-sizem!=1)
		return -1;
	a.Put(x+1,i+1);
	if(a.search(x+1)!=i+1)
		return -2;
	a.Delete(i);
	if(fabs(*a.getpointer(i)-x)<1e-15 || a.getsize()-sizem!=1)
		return -3;
	a.AddElement(x);
	if(fabs(*a.getpointer(1001)-x)<1e-15 || a.getsize()-sizem!=2)
		return -4;
	a.resize(i);
	if(a.getsize()!=i)
		return -5;
	return 0;
}
int test_sort(int tm)
{
	srand(time(NULL)+tm+100);
	CList a;
	clock_t start,stop;
	for(int i=0;i<tm;i++)
		a.Put(((double)rand()/RAND_MAX)*pow(10,rand()%5)*pow(-1,rand()),1);
	start = clock();
	a.sort();
	stop = clock();
	for(int i=1;i<tm;i++)
		if((*(a.getpointer(i)))-(*(a.getpointer(i+1)))>1e-15)
			return -1;
	return (stop-start)/CLK_TCK;
}
int main()
{
	int flag=0;
	for(int i=0;i<1000;i++)
		if(test1(i)!=0)
			flag=1;
	if(flag)
		cout<<"test1 is not ok"<<endl;
	else
		cout<<"test1 is ok"<<endl;
	flag=0;
	
	for(int i=0;i<1000;i++)
		if(test_sort(i)==-1)
			flag=1;
	if(flag)
		cout<<"test_sort is not ok"<<endl;
	else
		cout<<"test_sort is ok"<<endl;

	/*CList a(20);
	a.output();
	cout<<a.getsize()<<endl;
	a.resize(30);
	a.output();
	cout<<a.getsize()<<endl;
	a.Put(2,25);
	cout<<a.search(2)<<endl;
	a.output();
	a.Delete(21);
	a.output();
	cout<<a.getsize()<<endl;*/

	for(int i=1;i<=5;i++)
		cout<<test_sort(i*10000)<<" "<<i*10000<<" elements."<<endl;
	return 0;
}