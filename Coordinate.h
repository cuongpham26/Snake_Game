#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>

class Coordinate
{
private:
	int m_x;
	int m_y;
public:
	Coordinate() : m_x{ 2 }, m_y {2}{}
	Coordinate(const int& x, const int& y) : m_x{ x }, m_y{ y }
	{
	}
	void setPoint(const int&, const int&);
	int& getX() { return m_x; }
	int& getY() { return m_y; }
	friend bool operator== (const Coordinate&, const Coordinate&);
	void operator= (Coordinate&);
};

#endif
