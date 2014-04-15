#include "stdafx.h"
#include "Node.h"


Node::Node(Node* p, const Shape* s)
{
	m_Data = s->Clone();	
	ConstructNode(p); // �������� ������ ������ ����� ������
}


Node::~Node(void)
{
	RemoveNode();
	delete m_Data;
}

void Node::RemoveNode()
{
	// ���������� this
	if(pPrev)
		pPrev->pNext=pNext;
	if(pNext)
		pNext->pPrev=pPrev;
}


Node::Node(Node* p, const Node* node)
{
	m_Data=node->m_Data->Clone();
	ConstructNode(p); // �������� ������ ������ ����� ������
}

void Node::ConstructNode(Node* p)
{
	// ���������� ����� p
	pPrev=p;
	pNext=p->pNext;
	p->pNext=this;
	pNext->pPrev=this;
}

