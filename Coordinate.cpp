#include "Coordinate.h"

bool operator== (const Coordinate& c1, const Coordinate& c2)
{
	return ((c1.m_x == c2.m_x) && (c1.m_y == c2.m_y));
}

void Coordinate::operator= (Coordinate& c)
{
    m_x = c.m_x;
    m_y = c.m_y;
}

void Coordinate::setPoint(const int& x, const int& y)
{
    m_x = x;
    m_y = y;
}
