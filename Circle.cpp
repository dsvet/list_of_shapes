#include "stdafx.h"
#include "Circle.h"

Circle Circle::default=Circle(1,1,1);

Circle::Circle(int x,int y,int R,Color c):Shape(c)
{
	m_x=x;
	m_y=y;
	m_R=R;
}

Circle::Circle(int x,int y,int R)
{
	m_x=x;
	m_y=y;
	m_R=R;
}

double Circle::Square() const
{
	return M_PI*pow(m_R,2);
}

void Circle::ChangeData(int x,int y,int R, Color c)
{
	m_x=x;
	m_y=y;
	m_R=R;
	m_c=c;
}


Shape* Circle::Clone() const
{
	return new Circle(*this);
}

bool Circle::operator==(const Circle& c) const
{
	return (m_x==c.m_x && m_y==c.m_y && m_R==c.m_R && Shape::operator==(c));
}

bool Circle::operator==(const Shape& shape) const
{
	if(typeid(shape)!=typeid(Circle))
		return false;
	else
		return (*this==static_cast<const Circle&>(shape));
}

void Circle::Print(ostream& o) const
{
	o<<"C"<<endl;

	Shape::Print(o);

	o<<"x = "<<m_x<<endl;
	o<<"y = "<<m_y<<endl;
	o<<"Radius = "<<m_R<<endl<<endl;
}

Shape& Circle::operator=(const Shape& shape)
{
	Shape::operator=(shape);
	Circle& rC=static_cast<Circle&>(const_cast<Shape&>(shape));
	m_R=rC.m_R;
	m_x=rC.m_x;
	m_y=rC.m_y;

	return *this;
}