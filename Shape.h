#pragma once

enum Color{RED,GREEN,BLUE};

class Shape
{
protected:
	Color m_c;
public:
	Shape(Color c=BLUE){m_c=c;};

	virtual double Square() const = 0;
	virtual Shape* Clone() const = 0; // "copy" current Shape (our List deals with copies of Shape's objects)
	virtual bool operator==(const Shape& sh) const {return sh.m_c==m_c;}
	virtual void Print(ostream& o) const {o<<"Colour is "<<m_c<<endl;};
	virtual Shape& operator=(const Shape&);
};

