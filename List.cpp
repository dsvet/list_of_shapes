#include "stdafx.h"
#include "List.h"


List::List(void)
{
	m_size=0;
	Head.pNext=&Tail;
	Tail.pPrev=&Head;
	// Для корректного вызова ~Node():
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
	// очистка списка
{
	while(Head.pNext!=&Tail)
		delete Head.pNext; // вызываем деструктор для узла
}

void List::SortBySquare()
{
	if(m_size>1)
	{
		Node* cur=&Head;
		Node* minNode=nullptr;
		while(cur!=Tail.pPrev)
		{
			// считаем, что список отсортирован от Head до cur
			minNode=FindMinNode(cur); //ищем минимальный узел в списке, начиная со след. после cur
			// "Переносим" узел (удаляем и вставляем):
			minNode->RemoveNode();
			minNode->ConstructNode(cur); // вставка minNode после текущего узла

			cur=cur->pNext;
		}
	}
}

bool List::IsGreater(const Node* fNode, const Node* sNode) const
{
	double eps=0.0001;
	return (fNode->m_Data->Square()-sNode->m_Data->Square()>eps);

}

Node* List::FindMinNode(Node* p) const // просматриваем список, начиная с узла p
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
	Node* node=&Head; // текущий узел в списке, в который читаем
	int x,y,R,c,w,h; // параметры фигуры
	char type; // тип фигуры (R/C)
	char str[20]; // для хранения строки, прочитанной из файла
	while(!i.eof()) // читаем пока не достигнут конец файла
	{
		i.getline(str,_countof(str)); // читаем строку
		if(str[0]=='\0') // если пустая строка (между узлами)
			continue;
		// Читаем содержимое узла.		
		// Общая часть для круга и прямоугольника:
		sscanf_s(str,"%1c",&type); // читаем тип фигуры (R/C)
		i.getline(str,_countof(str));
		sscanf_s(str,"%*10c %d", &c); // пропускаем "Colour is "
		i.getline(str,_countof(str));
		sscanf_s(str,"%*4c %d", &x); // пропускаем "x = "
		i.getline(str,_countof(str));
		sscanf_s(str,"%*4c %d", &y); // пропускаем "y = "
		i.getline(str,_countof(str));
		if(type=='C') // если читаем круг
		{
			sscanf_s(str,"%*9c %d", &R); // пропускаем "Radius = "
			if(node->pNext!=&Tail)
			{
				if(Circle* pC=dynamic_cast<Circle*>(node->pNext->m_Data)) // если в узле был круг,
					pC->ChangeData(x,y,R,static_cast<Color>(c)); // то достаточно поменять данные
				else // dynamic_cast вернул 0
				{
					delete node->pNext->m_Data;
					node->pNext->m_Data=new Circle(x,y,R,static_cast<Color>(c));
				}
			}
			else // узлы в списке кончились
				AddToTail(new Circle(x,y,R,static_cast<Color>(c)));
		}
		if(type=='R') // если читаем прямоугольник
		{
			sscanf_s(str,"%*8c %d", &w); // пропускаем "Width = "
			i.getline(str,_countof(str));
			sscanf_s(str,"%*9c %d", &h); // пропускаем "Height = "
			if(node->pNext!=&Tail)
			{
				if(Rect* pC=dynamic_cast<Rect*>(node->pNext->m_Data)) // если в узле был прямоугольник,
					pC->ChangeData(x,y,w,h,static_cast<Color>(c)); // то достаточно поменять данные
				else // dynamic_cast вернул 0
				{
					delete node->pNext->m_Data;
					node->pNext->m_Data=new Rect(x,y,w,h,static_cast<Color>(c));
				}
			}
			else // узлы в списке кончились
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
	Head.m_Data=Tail.m_Data=nullptr; // для корректного вызова деструкторов встроенных Node

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
			// Копируем "общую часть":
			while(node->pNext!=&Tail && lNode->pNext!=&l.Tail)
			{
				try
				{
					*node->m_Data=*lNode->m_Data; // вызываем operator= класса типа *node->m_Data
				}
				catch(...) // присваивание невозможно (объекты разных типов - Circle & Rect)
				{
					delete node->m_Data;
					node->m_Data=lNode->m_Data->Clone();
				}
				node=node->pNext;
				lNode=lNode->pNext;
			}
		}
		if(m_size<l.m_size) // если в l есть еще элементы, но в нашем списке не хватает места
		{
			while(lNode!=&l.Tail)
			{
				AddToTail(lNode->m_Data->Clone());
				lNode=lNode->pNext;
			}
		}
		else // если дошли до конца l, то нужно удалить ненужные элементы в нашем списке
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
			// направляем голову и хвост нового списка на голову и хвост старого 
			Head.pNext=l.Head.pNext;
			Head.pNext->pPrev=&Head;
			Tail.pPrev=l.Tail.pPrev;
			Tail.pPrev->pNext=&Tail;
			m_size=l.m_size;
		}

			// удаление старых связей
			l.Head.pNext=&l.Tail;
			l.Tail.pPrev=&l.Head;
			l.m_size=0; // избыточно
		
	}

	return *this;
}
