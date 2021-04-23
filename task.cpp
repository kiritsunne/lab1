#include "Circle.h"
#define _USE_MATH_DEFINES
#include <cmath>



double MaxRadius(double r1, double r2)
{
	if (r1 > r2)
		return r1;
	else
		return r2;
}

double MinRadius(double r1, double r2)
{
	if (r1 > r2)
		return r2;
	else
		return r1;
}

double Distance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double MethodTriangle(double r1, double r2, double distance) {
	double f1 = 2 * acos((pow(r1, 2) - pow(r2, 2) + pow(distance, 2)) / (2 * r1*distance));
	double f2 = 2 * acos((pow(r2, 2) - pow(r1, 2) + pow(distance, 2)) / (2 * r2*distance));
	return (pow(r1, 2)*(f1 - sin(f1))) / 2 + (pow(r2, 2)*(f2 - sin(f2))) / 2;
}

double Square(Circle &A, Circle &B)
{
	double r1 = A.GetRadius();
	double r2 = B.GetRadius();
	double dist = Distance(A.GetXCoord(), A.GetYCoord(), B.GetXCoord(), B.GetYCoord());
	if (dist < 0.0000001)
		return M_PI * pow(MinRadius(r1, r2), 2);
	
	if(dist > (r1 + r2))
		return 0.0;
	
	if(dist + MinRadius(r1, r2) - MaxRadius(r1, r2) < -0.00000001)
		return M_PI * pow(MinRadius(r1, r2), 2);
	else return MethodTriangle(r1, r2, dist);
}