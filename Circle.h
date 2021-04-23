#pragma once

class Circle
{
private:
	double m_x;//х-центр окружности
	double m_y;//у-центр окружности
	double m_radius;//радиус окружности

public:
	Circle();
	Circle(double x, double y, double r);

	double GetXCoord();
	double GetYCoord();
	double GetRadius();

	void SetXCoord(double x);
	void SetYCoord(double y);
	void SetRadius(double r);
};

