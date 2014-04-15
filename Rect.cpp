#include "stdafx.h"
#include "Rect.h"

Rect Rect::default=Rect(0,0,1,1);


Rect::Rect(int x,int y,int w,int h,Color c):Shape(c)
{
	m_x=x;
	m_y=y;
	
	m_w=w;
	m_h=h;
}

Rect::Rect(int x,int y,int w,int h)
{
	m_x=x;
	m_y=y;
	m_w=w;
	m_h=h;
}

double Rect::Square() const
{
	return m_w*m_h;
}

void Rect::ChangeData(int x,int y,int w,int h,Color c)
{
	m_x=x;
	m_y=y;
	m_w=w;
	m_h=h;
	m_c=c;
}

Shape* Rect::Clone() const
{
	return new Rect(*this);
}

bool Rect::operator==(const Rect& rect) const
{
	return (m_x==rect.m_x && m_y==rect.m_y && m_w==rect.m_w && m_h==rect.m_h && Shape::operator==(rect));
}

bool Rect::operator==(const Shape& shape) const
{
	if(typeid(shape)!=typeid(Rect))
		return false;
	else
		return (*this==static_cast<const Rect&>(shape));
}

void Rect::Print(ostream& o) const
{
	o<<"R"<<endl;

	Shape::Print(o);

	o<<"x = "<<m_x<<endl;
	o<<"y = "<<m_y<<endl;
	o<<"Width = "<<m_w<<endl;
	o<<"Height = "<<m_h<<endl<<endl;
}

Shape& Rect::operator=(const Shape& shape)
{
	Shape::operator=(shape);
	Rect& rR=static_cast<Rect&>(const_cast<Shape&>(shape));
	m_w=rR.m_w;
	m_h=rR.m_h;
	m_x=rR.m_x;
	m_y=rR.m_y;

	return *this;
}