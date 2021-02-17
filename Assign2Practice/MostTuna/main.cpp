#include <iostream>
#include "library/counting.hpp"
#include "library/enumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"

using namespace std;
/*James BigLakeChampionship Tuna 50 Salmon 20 Sardine 5 Tuna 100
Which angler caught the most tuna?*/

struct Fish{
    string type;
    int size;
    friend istream &operator>>(istream &is, Fish &f)
    {
        is >> f.type >> f.size;
        return is;
    }
};

class TunaCnt1Contest : public Counting<Fish>
{
    bool cond(const Fish& e) const override { return e.type == "Tuna"; }
};

struct Contest{
    string anglr;
    string championship;
    int Tunas;
    friend istream &operator>>(istream &is, Contest &c);
};

istream &operator>>(istream &is, Contest &c)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> c.anglr >> c.championship;
    TunaCnt1Contest pr;
    StringStreamEnumerator<Fish> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    c.Tunas = pr.result();
    return is;
}

class TunaSum : public Summation<Contest,int>
{
private:
    string _name;
public:
    TunaSum(const string name) : _name(name) {}
protected:
    int func(const Contest& e) const override { return e.Tunas;}
    int neutral() const override { return 0;}
    int add( const int& a, const int& b) const override { return a+b;}
    void first() override { }
    bool whileCond(const Contest &e) const override { return e.anglr == _name;}
};

struct Angler{
    string name;
    int TunasCaught;
};

class ContestEnumerator : public Enumerator<Angler>
{
private:
    SeqInFileEnumerator<Contest>* _f;
    Angler _angler;
    bool _end;
public:
    ContestEnumerator(const string fname) {_f = new SeqInFileEnumerator<Contest>(fname);}
    void first() override { _f->first(); next();}
    void next() override;
    bool end() const override { return _end;}
    Angler current() const override { return _angler;}
    ~ContestEnumerator() {delete _f;}
};

void ContestEnumerator::next()
{
    if (_end = _f->end()) return;
    _angler.name = _f->current().anglr;
    TunaSum pr(_angler.name);
    pr.addEnumerator(_f);
    pr.run();
    _angler.TunasCaught = pr.result();
}

class MostTunas : public MaxSearch<Angler,int>
{
    int func(const Angler& e) const override {return e.TunasCaught;}
};

int main()
{
    try{
    MostTunas pr;
    ContestEnumerator enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    if (pr.opt()>0)
        cout <<"Angler "<<pr.optElem().name <<" caught most Tuna that is "<<pr.optElem().TunasCaught<<" Tuna.\n";
    else
        cout <<"No Angler was able to catch Tuna.\n";
    }catch(SeqInFileEnumerator<Contest>::Exceptions ex)
    {
        cout <<"File does not exist!";

    }
    return 0;
}
