#pragma once

class List
{
	size_t m_size;
	Node Head,Tail;

	bool IsGreater(const Node* fNode, const Node* sNode) const; // ��������� �� ������� ���� ����� � �����
	Node* FindMinNode(Node* cur) const; // ���������� ����������� ���� � ������, ������� � ���� cur (������������)
	void Print(ostream&) const;
	void Read(istream&);
public:
	List(void);	 // �������� ������� ������ (������ � ����� ��������� ���� �� �����)
	List(const List&);
	List(List&&);

	~List(void);

	List& operator=(const List&);
	List& operator=(List&&);

	void AddToHead(Shape*);
	void AddToTail(Shape*);
	bool RemoveFirst(const Shape& c); // ������� ������ ����, ����������� �� ������ c
	size_t Remove(const Shape& c); // ������� ��� ����, ����������� �� ������ c; ���������� ���������� ��������� �����
	void Clear(); // clear list
	void SortBySquare(); // ����������� �� ����������� �������


	friend ostream& operator<<(ostream&,const List&);
	friend istream& operator>>(istream&,List&);
};

