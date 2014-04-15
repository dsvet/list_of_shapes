#include "stdafx.h"
#include "Shape.h"

Shape& Shape::operator=(const Shape& other)
{
	m_c=other.m_c;
	return *this;
}
