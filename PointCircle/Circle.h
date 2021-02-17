#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"
#include <math.h>

class Circle
{
    public:
        Circle():_center(),_radius(1) {}
        Circle(const Point &center,double radius);
        Circle(double x,double y,double radius);
        friend std::ostream &operator<<(std::ostream &os,const Circle &c);
        double area() const {return _radius * _radius * 3.14; }
        double distance(const Point &p) const;
        bool isIn(const Point &p) const { return _radius >= distance(p); }


    protected:

    private:
        Point _center;
        double _radius;
};

#endif // CIRCLE_H
