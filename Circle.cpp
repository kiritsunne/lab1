#include "Circle.h"

Circle::Circle()
{
	m_x = 0;
	m_y = 0;
	m_radius = 0;
}

Circle::Circle(double x, double y, double r)
{
	m_x = x;
	m_y = y;
	m_radius = r;
}

double Circle::GetXCoord()
{
	return m_x;
}

double Circle::GetYCoord()
{
	return m_y;
}

double Circle::GetRadius()
{
	return m_radius;
}

void Circle::SetXCoord(double x)
{
	m_x = x;
}

void Circle::SetYCoord(double y)
{
	m_y = y;
}

void Circle::SetRadius(double r)
{
	m_radius = r;
}


