#include "Point.h"

using namespace std;

Point::Point()
{
}

Point::~Point()
{
}

void Point::SetPoints(string name, int x, int y)
{
	Point::name = name;
	Point::x = x; 
	Point::y = x;
}