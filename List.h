#pragma once

class List
{
	size_t m_size;
	Node Head,Tail;

	bool IsGreater(const Node* fNode, const Node* sNode) const; // compare squares of Shapes in the Nodes
	Node* FindMinNode(Node* cur) const; // return minimal Node in the List beginning from Node <cur> inclusively
	void Print(ostream&) const;
	void Read(istream&);
public:
	List(void);	 // create an empty List (Head and Tail point to each other)
	List(const List&);
	List(List&&);

	~List(void);

	List& operator=(const List&);
	List& operator=(List&&);

	void AddToHead(Shape*);
	void AddToTail(Shape*);
	bool RemoveFirst(const Shape& c); // remove the first Node pointed to Shape <c>
	size_t Remove(const Shape& c); // remove all Nodes pointed to Shape <c>; return number of removed Nodes
	void Clear(); // clear List
	void SortBySquare(); // sort by ascending of square


	friend ostream& operator<<(ostream&,const List&);
	friend istream& operator>>(istream&,List&);
};

