#pragma once
#include <string>
#include "data.h"

struct Angler{
    string name;
    int tuna_cnt;
};

class EnorAngler
{
    public:
         EnorAngler(const string &str) : _ED(str) { };
         void first() { _ED.first(); next();}
         void next();
         Angler current() const { return _cur;}
         bool end() const { return _end;}

    private:
        EnorData _ED;
        Angler _cur;
        bool _end;

};
