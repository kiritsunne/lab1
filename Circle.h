#pragma once

class Circle
{
private:
	double m_x;//�-����� ����������
	double m_y;//�-����� ����������
	double m_radius;//������ ����������

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

