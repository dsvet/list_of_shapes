#pragma once

class Rect :
	public Shape
{
	int m_x,m_y,m_w,m_h;
public:
	Rect(int x,int y,int w,int h, Color c);
	Rect(int x,int y,int w,int h);
	Rect(){*this=default;}
	static Rect default;
	
	virtual double Square() const;

	virtual Shape* Clone() const;
	virtual bool operator==(const Shape&) const;
	bool operator==(const Rect&) const;

	virtual void Print(ostream&) const;
	virtual Shape& operator=(const Shape&);

	void ChangeData(int x,int y,int w,int h,Color c);
	virtual double Remoteness() const {return sqrt(m_x*m_x+m_y*m_y);}; // return remoteness from the initial point (0;0)
};

