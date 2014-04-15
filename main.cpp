#include "stdafx.h"
#include "List.h"
#define stop __asm nop

int _tmain(int argc, _TCHAR* argv[])
{
	List l;
	{
		Circle c1(1,1,2,RED);
		Circle c2;
		Circle c3(3,12,8);
		Circle* c4=new Circle(0,0,3,GREEN);

		Rect r1;
		Rect r2(4,3,15,34);
		Rect r3(3,8,6,9,GREEN);
		Rect* r4=new Rect(5,19,23,2);

		l.AddToHead(&c1);
		l.AddToTail(&c2);
		l.AddToHead(&c3);
		l.AddToTail(c4);
		l.AddToHead(&r1);
		l.AddToTail(&r2);
		l.AddToHead(&r3);
		l.AddToTail(r4);

		delete c4;
		delete r4;
	}

	Rect r5(3,5,23,2);
	Rect r6=r5;
	l.AddToHead(&r5);
	l.AddToHead(&r6);

	Circle c5=Circle();
	Circle c6=Circle(c5);
	l.AddToTail(&c5);
	l.AddToTail(&c6);

	cout<<l;
	stop

	List l2;
	l2=l;

	cout<<l2.Remove(r5)<<" nodes were removed."<<endl;		
	cout<<l;

	l2.SortBySquare();
	ofstream fout("MyList.txt");
	fout<<l2;

	List l3=std::move(List());
	l2=std::move(l3);
	ifstream fin("MyList.txt");
	fin>>l2;
	cout<<l2;

	stop
	return 0;
}

