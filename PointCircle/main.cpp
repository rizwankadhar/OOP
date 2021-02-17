#include <iostream>
#include "Circle.h"
#include <vector>
#include <stdlib.h>
#include <fstream>

using namespace std;

vector<Point> loadFromFile(const string &fileName);
int pointsInCircle(const vector<Point> &v, const Circle &circle);

int main()
{
    double x,y,r;
    cout << "Coordinates of the center of the circle: ";
    cin >> x >> y;
    cout << "Radius: ";
    cin >> r;
    Circle circle(x,y,r);

    string fileName;
    cout << "Input file's name: ";
    cin >> fileName;
    cout << endl;
    vector<Point> v = loadFromFile(fileName);
    cout << "There are " << pointsInCircle(v,circle) << " points in the circle.\n";

    return 0;
}

vector<Point> loadFromFile(const string &fileName)
{
    fstream f(fileName.c_str());
    if (f.fail())
    {
        cout << "Wrong filename!\n";
        exit(1);
    }
    double x,y;
    vector<Point> v;
    while (f >> x >> y)
    {
        Point p(x,y);
        v.push_back(p);
    }
    f.close();
    return v;
}

int pointsInCircle(const vector<Point> &v, const Circle &circle)
{
    int c = 0;
    for (unsigned int i = 0; i< v.size();i++)
    {
        if (circle.isIn(v[i])) ++c;
    }
    return c;
}
