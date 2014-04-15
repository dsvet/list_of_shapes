#pragma once

class Node
{
	Node* pPrev, *pNext;
	Shape* m_Data;
	
	Node(){pPrev=pNext=nullptr;} // ������������ � ������������� List ��� ������������� Head � Tail
	Node(Node* p, const Shape* s); // ������� ���� � �������� ������� ����� ���� p
	Node(Node* p, const Node* node); // ������� ����� ���������� ���� ����� ���� p
	~Node(void); // ��������� this-����, ������� ��������������� � ��� ������
	
	void RemoveNode(); // ���������� this-���� �� ������ (�������� ������)
	void ConstructNode(Node* p); // �������� ������ ������ ����� ������

	friend class List;
};

