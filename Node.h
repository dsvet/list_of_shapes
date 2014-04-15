#pragma once

class Node
{
	Node* pPrev, *pNext;
	Shape* m_Data;
	
	Node(){pPrev=pNext=nullptr;} // used in constructors of List for initialization of Head and Tail
	Node(Node* p, const Shape* s); // insertion of Node with <s> after Node <p>
	Node(Node* p, const Node* node); // insertion of already created Node after Node <p>
	~Node(void); // remove this-Node, delete associated Shape
	
	void RemoveNode(); // remove this-Node from the List (delete links)
	void ConstructNode(Node* p); // create necessary links between Nodes

	friend class List;
};

