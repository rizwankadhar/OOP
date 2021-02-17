#include "Circle.h"
//#include <iostream>

Circle::Circle(const Point &center,double radius):_center(center)
{
    if (radius <=0)
    {
            _radius = 1;
            std::cout << "A sugarat 1-re allitottam.\n";
    }
    else
    {
        _radius = radius;
    }
}

Circle::Circle(double x,double y,double radius):_center(x,y)
{
    if (radius <= 0)
    {
            _radius = 1;
            std::cout << "A sugarat 1-re allitottam.\n";
    }
    else
    {
        _radius = radius;
    }
}

double Circle::distance(const Point &p) const
{
    return pow(p.getX()-_center.getX(),2);
    //return sqrt((p.getX()-_center.getX())*(p.getX()-_center.getX())+(p.getY()-_center.getY())*(p.getY()-_center.getY()));
}


std::ostream &operator<<(std::ostream &os,const Circle &c)
{
    os << "kp.: " << c._center << ", sugar: " << c._radius;
    return os;
}

