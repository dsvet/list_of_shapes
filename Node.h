#pragma once

class Node
{
	Node* pPrev, *pNext;
	Shape* m_Data;
	
	Node(){pPrev=pNext=nullptr;} // используется в конструкторах List для инициализации Head и Tail
	Node(Node* p, const Shape* s); // вставка узла с заданной фигурой после узла p
	Node(Node* p, const Node* node); // вставка ранее созданного узла после узла p
	~Node(void); // исключить this-узел, удалить ассоциированную с ним фигуру
	
	void RemoveNode(); // исключение this-узла из списка (удаление связей)
	void ConstructNode(Node* p); // создание нужных связей между узлами

	friend class List;
};

