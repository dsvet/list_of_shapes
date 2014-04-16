#pragma once

class Circle :
	public Shape
{
	int m_x,m_y,m_R;
public:
	static Circle default;

	Circle(){*this=default;}
	Circle(int x,int y,int R,Color c);
	Circle(int x,int y,int R);	
	
	virtual double Square() const;
	virtual Shape* Clone() const;
	virtual bool operator==(const Shape&) const;
	bool operator==(const Circle&) const;

	virtual void Print(ostream&) const;

	virtual Shape& operator=(const Shape&);
	void ChangeData(int x,int y,int R,Color c);
	virtual double Remoteness() const {return sqrt(m_x*m_x+m_y*m_y);}; // return remoteness from the initial point (0;0)
};

