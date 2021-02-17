#include "Point.h"

double Point::getX() const
{
    return _x;
}
double Point::getY() const
{
    return _y;
}
void Point::setX(double x)
{
    _x = x;
}
void Point::setY(double y)
{
    _y = y;
}

std::ostream &operator<<(std::ostream &os,const Point &p)
{
    os << "(" << p._x << "," << p._y << ")";
    return os;
}
