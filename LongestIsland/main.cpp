#include <iostream>
#include "library/selection.hpp"
#include "library/counting.hpp"
#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/enumerator.hpp"

/*Find the length of the longest island if measured elevations can be found in a text file.*/
using namespace std;

class FindIsland : public Selection<int>
{
    bool cond(const int& e) const override { return e > 0 || _enor->end();}
    void first() override {}
};

class CountElevations : public Counting<int>
{
    bool whileCond(const int &e) const override { return e > 0;}
    void first() override { }
};

struct Island{
    int number;
    int length;
};

class IslandEnor : public Enumerator<Island>
{
private:
    SeqInFileEnumerator<int>* _f;
    Island _island;
    bool _end;
    bool _empty;
public:
    IslandEnor(const string &fname) : _empty(true) { _f = new SeqInFileEnumerator<int>(fname);}
    void first() override { _f->first(); _island.number = 0; next(); if (!end()) _empty = false;}
    void next() override;
    bool end() const override { return _end;}
    Island current() const override { return _island;}
    bool isEmpty() const { return _empty;}
    ~IslandEnor() { delete _f;}
};

void IslandEnor::next()
{
    FindIsland pr;
    pr.addEnumerator(_f);
    pr.run();

    if (_end = _f->end()) return;
   _island.number++;
   CountElevations pr2;
   pr2.addEnumerator(_f);
   pr2.run();
   _island.length = pr2.result();
}

class MinLength : public MaxSearch<Island,int,Less<int>>
{
    int func(const Island &e) const override { return e.length;}
};
int main(int argc, char** argv)
{
    try{
        string filename;
        if (argc > 1) filename = argv[1];
        else filename = "empty.txt";

        MinLength pr;
        IslandEnor enor(filename);
        pr.addEnumerator(&enor);
        pr.run();
        if (enor.isEmpty())
        {
            cout <<"Bruhh...your file is land locked..it has no island!!!\n";
        }
        else
        {
            if (pr.found())
            {
                cout <<"Smallest island is IsLand no: "<<pr.optElem().number <<" whose length is : "<< pr.opt()<<endl;
            }
        }
    }catch(SeqInFileEnumerator<int>::Exceptions e)
    {
        cout <<"Bruh...that aint a filename!!!!!!\n";
    }
    return 0;
}
