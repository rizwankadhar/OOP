#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

 using namespace std;

 struct data{
 string name;
 string champ;
 int tunas;
 };
class EnorData
{
    public:
        EnorData(const string &filename) { _f.open(filename);}
        data current() const { return _curr;}
        void first() { next();}
        void next();

        bool end() const { return _end;}

    private:
        ifstream _f;
        data _curr;
        bool _end;
};

