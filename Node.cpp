#include "stdafx.h"
#include "Node.h"


Node::Node(Node* p, const Shape* s)
{
	m_Data = s->Clone();	
	ConstructNode(p); // создание нужных связей между узлами
}


Node::~Node(void)
{
	RemoveNode();
	delete m_Data;
}

void Node::RemoveNode()
{
	// исключение this
	if(pPrev)
		pPrev->pNext=pNext;
	if(pNext)
		pNext->pPrev=pPrev;
}


Node::Node(Node* p, const Node* node)
{
	m_Data=node->m_Data->Clone();
	ConstructNode(p); // создание нужных связей между узлами
}

void Node::ConstructNode(Node* p)
{
	// добавление после p
	pPrev=p;
	pNext=p->pNext;
	p->pNext=this;
	pNext->pPrev=this;
}

