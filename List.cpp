#include "stdafx.h"
#include "List.h"


List::List(void)
{
	m_size=0;
	Head.pNext=&Tail;
	Tail.pPrev=&Head;
	// ��� ����������� ������ ~Node():
	Head.m_Data=nullptr;
	Tail.m_Data=nullptr;
}


List::~List(void)
{
	Clear();
}

void List::AddToHead(Shape* c)
{
	new Node(&Head,c);
	m_size++;
}

void List::AddToTail(Shape* c)
{
	new Node(Tail.pPrev,c);
	m_size++;
}

bool List::RemoveFirst(const Shape& c)
{
	Node* p=Head.pNext;
	while(p!=&Tail)
	{
		if(*p->m_Data==c)
		{
			delete p;
			m_size--;
			return true;			
		}
		p=p->pNext;
	}
	return false;
}

size_t List::Remove(const Shape& c)
{
	size_t count=0;
	Node* p=Head.pNext;
	while(p!=&Tail)
	{
		Node* n=p->pNext;
		if(*p->m_Data==c)
		{
			count++;
			delete p;
			m_size--;
		}
		p=n;
	}

	return count;
}

void List::Clear()
	// ������� ������
{
	while(Head.pNext!=&Tail)
		delete Head.pNext; // �������� ���������� ��� ����
}

void List::SortBySquare()
{
	if(m_size>1)
	{
		Node* cur=&Head;
		Node* minNode=nullptr;
		while(cur!=Tail.pPrev)
		{
			// �������, ��� ������ ������������ �� Head �� cur
			minNode=FindMinNode(cur); //���� ����������� ���� � ������, ������� �� ����. ����� cur
			// "���������" ���� (������� � ���������):
			minNode->RemoveNode();
			minNode->ConstructNode(cur); // ������� minNode ����� �������� ����

			cur=cur->pNext;
		}
	}
}

bool List::IsGreater(const Node* fNode, const Node* sNode) const
{
	double eps=0.0001;
	return (fNode->m_Data->Square()-sNode->m_Data->Square()>eps);

}

Node* List::FindMinNode(Node* p) const // ������������� ������, ������� � ���� p
{
	Node* node=p->pNext;
	p=p->pNext;
	while(p!=Tail.pPrev)
	{
		Node* next=p->pNext;
		if(IsGreater(p,next))
			node=next;
		p=p->pNext;
	}
	return node;
}

ostream& operator<<(ostream& o, const List& l)
{
	l.Print(o); // print List
	return o;
}

void List::Print(ostream& o) const // print List
{
	Node* node=Head.pNext;
	while(node!=&Tail)
	{
		node->m_Data->Print(o); // print Shape
		node=node->pNext;
	}
}


istream& operator>>(istream& i,List& l)
{
	l.Read(i);	
	return i;
}

void List::Read(istream& i)
{
	Node* node=&Head; // ������� ���� � ������, � ������� ������
	int x,y,R,c,w,h; // ��������� ������
	char type; // ��� ������ (R/C)
	char str[20]; // ��� �������� ������, ����������� �� �����
	while(!i.eof()) // ������ ���� �� ��������� ����� �����
	{
		i.getline(str,_countof(str)); // ������ ������
		if(str[0]=='\0') // ���� ������ ������ (����� ������)
			continue;
		// ������ ���������� ����.		
		// ����� ����� ��� ����� � ��������������:
		sscanf_s(str,"%1c",&type); // ������ ��� ������ (R/C)
		i.getline(str,_countof(str));
		sscanf_s(str,"%*10c %d", &c); // ���������� "Colour is "
		i.getline(str,_countof(str));
		sscanf_s(str,"%*4c %d", &x); // ���������� "x = "
		i.getline(str,_countof(str));
		sscanf_s(str,"%*4c %d", &y); // ���������� "y = "
		i.getline(str,_countof(str));
		if(type=='C') // ���� ������ ����
		{
			sscanf_s(str,"%*9c %d", &R); // ���������� "Radius = "
			if(node->pNext!=&Tail)
			{
				if(Circle* pC=dynamic_cast<Circle*>(node->pNext->m_Data)) // ���� � ���� ��� ����,
					pC->ChangeData(x,y,R,static_cast<Color>(c)); // �� ���������� �������� ������
				else // dynamic_cast ������ 0
				{
					delete node->pNext->m_Data;
					node->pNext->m_Data=new Circle(x,y,R,static_cast<Color>(c));
				}
			}
			else // ���� � ������ ���������
				AddToTail(new Circle(x,y,R,static_cast<Color>(c)));
		}
		if(type=='R') // ���� ������ �������������
		{
			sscanf_s(str,"%*8c %d", &w); // ���������� "Width = "
			i.getline(str,_countof(str));
			sscanf_s(str,"%*9c %d", &h); // ���������� "Height = "
			if(node->pNext!=&Tail)
			{
				if(Rect* pC=dynamic_cast<Rect*>(node->pNext->m_Data)) // ���� � ���� ��� �������������,
					pC->ChangeData(x,y,w,h,static_cast<Color>(c)); // �� ���������� �������� ������
				else // dynamic_cast ������ 0
				{
					delete node->pNext->m_Data;
					node->pNext->m_Data=new Rect(x,y,w,h,static_cast<Color>(c));
				}
			}
			else // ���� � ������ ���������
				AddToTail(new Rect(x,y,w,h,static_cast<Color>(c)));
		}
		node=node->pNext;
	}
}

List::List(const List& l)
{
	Head.pNext=&Tail;
	Tail.pPrev=&Head;
	m_size=0;
	Head.m_Data=Tail.m_Data=nullptr; // ��� ����������� ������ ������������ ���������� Node

	*this=l;
}

List::List(List&& l)
{
	*this=std::move(l);
}

List& List::operator=(const List& l)
{
	if(this!=&l)
	{
		Node* node=Head.pNext;
		Node* lNode=l.Head.pNext;

		if(m_size!=0)
		{
			// �������� "����� �����":
			while(node->pNext!=&Tail && lNode->pNext!=&l.Tail)
			{
				try
				{
					*node->m_Data=*lNode->m_Data; // �������� operator= ������ ���� *node->m_Data
				}
				catch(...) // ������������ ���������� (������� ������ ����� - Circle & Rect)
				{
					delete node->m_Data;
					node->m_Data=lNode->m_Data->Clone();
				}
				node=node->pNext;
				lNode=lNode->pNext;
			}
		}
		if(m_size<l.m_size) // ���� � l ���� ��� ��������, �� � ����� ������ �� ������� �����
		{
			while(lNode!=&l.Tail)
			{
				AddToTail(lNode->m_Data->Clone());
				lNode=lNode->pNext;
			}
		}
		else // ���� ����� �� ����� l, �� ����� ������� �������� �������� � ����� ������
		{
			node=node->pPrev;
			while(node->pNext!=&Tail)
			{
				delete node->pNext;
				node=node->pNext;
				m_size--;
			}
		}
	}

	return *this;
}

List& List::operator=(List&& l)
{	
	if(this!=&l)
	{
		if(l.m_size==0)
		{
			
			Head.pNext=&Tail;
			Tail.pPrev=&Head;
			m_size=0;
		}
		else
		{
			// ���������� ������ � ����� ������ ������ �� ������ � ����� ������� 
			Head.pNext=l.Head.pNext;
			Head.pNext->pPrev=&Head;
			Tail.pPrev=l.Tail.pPrev;
			Tail.pPrev->pNext=&Tail;
			m_size=l.m_size;
		}

			// �������� ������ ������
			l.Head.pNext=&l.Tail;
			l.Tail.pPrev=&l.Head;
			l.m_size=0; // ���������
		
	}

	return *this;
}
