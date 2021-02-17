#pragma once
#include <iostream>
#include <fstream>

using namespace std;

struct Prey{
    string hunter;
    string specie;
    int weight;
    friend istream &operator>>(istream &is, Prey &p);
};

enum Status{norm,abnorm};

class infile
{
    public:
        enum Error {Open_Error};
        infile(const string &filename);
        ~infile(){_x.close();}
        void first() { read(); next();}
        void next();
        double current() const { return _curr; }
        bool end() const {return _end;}

    private:
        ifstream _x;
        Status _sx;
        Prey _dx;
        double _curr;
        bool _end;

        void read();
};

