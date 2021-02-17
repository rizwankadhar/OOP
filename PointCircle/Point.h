#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;
class Point
{
    public:
        Point() { _x = 0; _y = 0; }
        Point(double x, double y): _x(x), _y(y)
        {///_x=x; _y=y;
        }
        void print() const { cout << "(" << _x << "," << _y << ")"; }

        ///getterek
        double getX() const;
        double getY() const;
        void setX(double x);
        void setY(double y);
        friend ostream &operator<<(ostream &os,const Point &p);


    protected:

    private:
        double _x;
        double _y;
};

#endif // POINT_H
