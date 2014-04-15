#pragma once

class List
{
	size_t m_size;
	Node Head,Tail;

	bool IsGreater(const Node* fNode, const Node* sNode) const; // сравнение по площади двух фигур в узлах
	Node* FindMinNode(Node* cur) const; // возвращает минимальный узел в списке, начиная с узла cur (включительно)
	void Print(ostream&) const;
	void Read(istream&);
public:
	List(void);	 // создание пустого списка (голова и хвост указывают друг на друга)
	List(const List&);
	List(List&&);

	~List(void);

	List& operator=(const List&);
	List& operator=(List&&);

	void AddToHead(Shape*);
	void AddToTail(Shape*);
	bool RemoveFirst(const Shape& c); // удалить первый узел, указывающий на фигуру c
	size_t Remove(const Shape& c); // удалить все узлы, указывающие на фигуру c; возвращает количество удаленных узлов
	void Clear(); // clear list
	void SortBySquare(); // сортировать по возрастанию площади


	friend ostream& operator<<(ostream&,const List&);
	friend istream& operator>>(istream&,List&);
};

