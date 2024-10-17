#include "r.h"

CNode::CNode()      //Узел списка
{
	for(int i=0;i<n;i++)
		v[i]=0;
	next = NULL;
	prev = NULL;
}
CNode::CNode(double * a)
{
	for(int i=0;i<n;i++)
		v[i]=a[i];
	next = NULL;
	prev = NULL;
}
/*CNode::~CNode()
{
	next=NULL;
}
void CNode::CopyOnly(const CNode &a)
{
	this->next=a.next;
	for(int i=0;i<n;i++)
		this->v[i]=a.v[i];
}
CNode& CNode::operator=(const CNode &a)
{
	delete next;
	next = NULL;
	cout<<"ROFL"<<endl;
	CopyOnly(a);
	return *this;
}*/
CList::CList()      //Функции списка
{
	cur=begin=end=NULL;
	size = 0;
}
CList::CList(int size)
{
	cur=begin=end=NULL;
	this->size = size;
	for(int i=0;i<size/n+(size%n!=0);i++)
		AddAfter();
	/*assert(size>0);
	this->size = size;
	int k = size/n+(size%n!=0);
	CNode *p;
	cur->next=NULL;
	for(int i=0;i<k;i++)
	{
		p=new CNode;
		p->next = cur->next;
		cur->next = p;
		p->prev=cur;
		if(i==0)
			end = p;
		if(i==k-1)
			begin=cur;
	}*/
	//fict.next = p[0];
	/*for(int i=0;i<k-1;i++)
		p[i]->next = p[i+1];*/
	//p[k-1]->next = NULL;
}
CList::~CList()
{
	Clean();
}
void CList::Clean()
{
	GoToBegin();
	while(!IsEmpty())
		DelCur();
	size = 0;
}
int CList::IsEmpty()
{
	return (begin == NULL);
}
void CList::GoToBegin()
{
	cur = begin;
}
void CList::GoToEnd()
{
	cur = end;
}
int CList::GoToNext()
{
	if(cur == end)
		return -2;
	cur = cur->next;
	return 0;
}
int CList::GoToPrev()
{
	if(cur == begin)
		return -2;
	cur = cur->prev;
	return 0;
}
int CList::GoToNode(int i)
{
	if(i<=0 || i>size)
		return -1;
	GoToBegin();
	for(int j=0;j<i/n-(i%n==0);j++)
		GoToNext();
	return 0;
}
int CList::GetCur(double *a)
{
	if(IsEmpty())
		return -3;
	else
		for(int i=0;i<n;i++)
			a[i]=cur->v[i];
	return 0;
	
}
int CList::DelCur()
{
	if(IsEmpty())
		return -1;
	CNode *save = cur;
	if(cur->prev)
		cur->prev->next=cur->next;
	else
		begin=cur->next;
	if(cur->next)
		cur->next->prev=cur->prev;
	else
		end=cur->prev;
	if(cur->prev)
		cur=cur->prev;
	else
		cur=cur->next;
	delete save;
	return 0;
}
/*void CList::AddAfter(const double *a)
{
	assert(sizeof(a)==sizeof(double)*10);
	CNode *p = new CNode;
	for(int i=0;i<n;i++)
		p->v[i]=a[i];
	p->next = cur->next;
	cur->next = p;
}*/
void CList::AddAfter()
{
	CNode *t=new CNode;
	for(int i=0;i<n;i++)
		t->v[i]=0;
	if(IsEmpty())
		{cur=begin=end=t;}
	else
	{
		t->next=cur->next;
		t->prev=cur;
		cur->next=t;
		if(t->next)
			t->next->prev=t;
		else
			end=t;
	}
}
void CList::AddElement(const double x)
{
	GoToEnd();
	if(size%n==0)
	{
		AddAfter();
		cur->next->v[0]=x;
	}
	else
		cur->v[size%n] = x;
	size++;
}
void CList::Put(const double x, int i)
{
	if(i>size)
	{
		resize(i);
		GoToEnd();
		cur->v[(i%n==0) ? n-1 : i%n-1]=x;
		return;
	}
	else
		if(size%n==0)
		{
			GoToEnd();
			AddAfter();
		}
	GoToNode(i);
	double t0;
	t0=shiftright(x,cur->v,(i-1)%n);
	if(GoToNext()!=0)
	{
		size++;
		return;
	}
	int k=i/n+1+(i%n!=0);
	while(size/n>k)
	{
		t0=shiftright(t0,cur->v,0);
		cur=cur->next;
		k++;
	}
	shiftright(t0,cur->v,0);
	size++;
}
void CList::Delete(int i)
{
	if(i==size && i%n==1)
	{
		GoToNode(i);
		DelCur();
		size--;
		return;
	}
	int k=i/n+(i%n!=0);
	GoToNode(i);
	shiftleft((cur != end) ? cur->next->v[0] : 0,cur->v,(i%n==0) ? n-1 : i%n-1);
	GoToNext();
	while(size/n>k)
	{
		shiftleft((cur != end) ? cur->next->v[0] : 0,cur->v,0);
		GoToNext();
		k++;
	}
	shiftleft(0,cur->v,0);
	size--;
}
double* CList::getpointer(int i)
{
	GoToNode(i);
	int k;
	k = (i%n==0) ? n-1 : i%n-1;
	double *p=&(cur->v[k]);
	return p;
}
int CList::getsize()
{
	return size;
}
int CList::search(double a)
{
	if(IsEmpty())
		return -1;
	GoToBegin();
	int k=0,s=1;
	while(1)
	{
		if(fabs(cur->v[k]-a)<1e-15)
			return k+1+(s-1)*n; 
		if(k+1+n*(s-1)==size)
			return -1;
		if(k==n-1)
		{
			GoToNext();
			k = 0;
			s++;
		}
		else
			k++;
	}
}
void CList::sort()
{
	int i=0,j,s=1;
	if(IsEmpty())
		return;
	GoToBegin();
	double t;
	while(1)
	{
		if(i<n-1)
		{
			if(cur->v[i]-cur->v[i+1]>1e-15)
			{
				//cout<<"Zamena1 "<<s<<"."<<cur->v[i]<<" and "<<s<<"."<<cur->v[i+1]<<endl;
				t=cur->v[i];
				cur->v[i]=cur->v[i+1];
				cur->v[i+1]=t;
				j=i;
				while(j>=0)
				{
					if(j>0)
					{
						if(cur->v[j-1]-cur->v[j]<1e-15)
							break;
						else
						{
							//cout<<"Zamena2 "<<s<<"."<<cur->v[j-1]<<" and "<<s<<"."<<cur->v[j]<<endl;
							t=cur->v[j];
							cur->v[j]=cur->v[j-1];
							cur->v[j-1]=t;
							j--;
						}	
					}
					else 
						if(GoToPrev()==0)
						{
							if(cur->v[n-1]-cur->next->v[0]<1e-15)
							{
								GoToNext();
								break;
							}
							else
							{
								//cout<<"Zamena3 "<<s<<"."<<cur->v[n-1]<<" and "<<s+1<<"."<<cur->next->v[0]<<endl;
								t=cur->next->v[0];
								cur->next->v[0]=cur->v[n-1];
								cur->v[n-1]=t;								
								j=9;
								s--;
							}
						}
						else
							break;
				}
			}
			if((s-1)*10+i+1==size)
				return ;
			i++;
		}
		else
		{
			if(cur == end)
				break;
				/*cout<<":";
				for(int h=0;h<n;h++)
					cout<<cur->next->v[h]<<endl;
				cout<<"attention i="<<i<<" "<<cur->next->v[0]<<endl;*/
			if(cur->v[n-1]-cur->next->v[0]>1e-15)
			{
				//cout<<"Zamena4 "<<s<<"."<<cur->v[n-1]<<" and "<<s+1<<"."<<cur->next->v[0]<<endl;
				t=cur->v[n-1];
				cur->v[n-1]=cur->next->v[0];
				cur->next->v[0]=t;
				j=i;
				while(j>=0)
				{
					if(j>0)
					{
						if(cur->v[j]-cur->v[j-1]>1e-15 || fabs(cur->v[j]-cur->v[j-1])<1e-15)
							break;
						else
						{
							//cout<<"Zamena5 "<<s<<".["<<j-1<<"]"<<cur->v[j-1]<<" and "<<s<<".["<<j<<"]"<<cur->v[j]<<endl;
							t=cur->v[j];
							cur->v[j]=cur->v[j-1];
							cur->v[j-1]=t;
							j--;
						}	
					}
					else 
						if(GoToPrev()==0)
						{
							if(cur->next->v[0]-cur->v[n-1]>1e-15 || fabs(cur->next->v[0]-cur->v[n-1])<1e-15)
							{
								GoToNext();
								break;
							}
							else
							{
								//cout<<"Zamena6 "<<s<<"."<<cur->v[n-1]<<" and "<<s+1<<"."<<cur->v[0]<<endl;
								t=cur->next->v[0];
								cur->next->v[0]=cur->v[n-1];
								cur->v[n-1]=t;								
								j=9;
								s--;
							}
						}
						else
							break;
				}
			}
			if((s-1)*10+i+1==size)
				return;
			GoToNext();
			i=0;
			s++;
		}
	}
}
double shiftright(double b, double* a,int d)
{
	double t;
	for(int s=d;s<n;s++)
	{
		t=a[s];
		a[s]=b;
		b=t;
	}
	return b;
}
void shiftleft(double b, double* a,int d)
{
	for(int s=d;s<n-1;s++)
		a[s]=a[s+1];
	a[n-1]=b;
}
void CList::resize(int newsize)
{
	GoToEnd();
	while(size<newsize)
	{
		AddAfter();
		size+=n;
	}
	size=newsize;
}
void CList::output()
{
	if(IsEmpty())
	{
		cout<<"Empty."<<endl;
		return;
	}
	GoToBegin();
	int i=0,s=1;
	while(i+(s-1)*10<size)
	{
		cout<<cur->v[i]<<" ";
		if(i==n-1)
		{
			i=0;
			s++;
			if(GoToNext())
			{
				cout<<endl;
				return;
			}
		}
		else
			i++;
	}
	cout<<endl;
}

/*
void CList::output()
{
	GoToBegin();
	if(GoToNext())
		cout<<"Empty."<<endl;
	int i=0,s=1;
	while(i+(s-1)*10<size)
		if(i!=n)
		{
			if(i+1+(s-1)*10==size)
			{
				cout<<endl;
				return;
			}
			cout<<cur->v[i]<<" ";
			i++;
		}
		else
		{
			i=0;
			s++;
			if(GoToNext())
			{
				cout<<endl;
				return;
			}
		}
	cout<<endl;
}
*/
/* 
-1 -- bad delete
-2 -- bad go to next
-3 -- bad getcur

*/

