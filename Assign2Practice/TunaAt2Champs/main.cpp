#include <iostream>
#include "library/counting.hpp"
#include "library/enumerator.hpp"
#include "library/linsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"

/*
James BigLakeChampionship Tuna 50 Salmon 20 Sardine 5 Tuna 100
Is it true that all anglers caught tuna at at least two championships.
*/

using namespace std;

struct Fish{
    string type;
    int size;
    friend istream &operator>>(istream &is,Fish &f)
    {
        is >> f.type >> f.size;
        return is;
    }
};

class caughtTuna : public LinSearch<Fish>
{
    bool cond(const Fish &e) const override { return e.type == "Tuna";}
};
struct Contest{
    string anglr;
    string championship;
    bool Tuna;
    friend istream &operator>>(istream &is,Contest &c);
};

istream &operator>>(istream &is, Contest &c)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> c.anglr >> c.championship;
    caughtTuna pr;
    StringStreamEnumerator<Fish> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    c.Tuna = pr.found();
    return is;
}

class TunaCatches : public Counting<Contest>
{
private:
    string _name;
public:
    TunaCatches(const string name) : _name(name) {}
protected:
    bool cond(const Contest &e) const override {return e.Tuna;}
    bool whileCond(const Contest &e) const override { return e.anglr == _name;}
    void first() override {}
};
struct Angler{
    string name;
    int TunaCnt;
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
    Angler current() const override {return _angler;}
    ~ContestEnumerator() {delete _f;}
};

void ContestEnumerator::next()
{
    if (_end = _f->end()) return;
    _angler.name = _f->current().anglr;
    TunaCatches pr(_angler.name);
    pr.addEnumerator(_f);
    pr.run();
    _angler.TunaCnt = pr.result();
}

class AtLeast2Tuna : public LinSearch<Angler,true>
{
    bool cond(const Angler &e) const override {return e.TunaCnt >= 2;}
};

int main()
{
    AtLeast2Tuna pr;
    ContestEnumerator enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    if (pr.found())
        cout <<"Yes, all anglers caught tuna at at least two championships.\n";
    else
        cout <<"No, its not true that all anglers caught tuna at at least two championships.\n";
    return 0;
}
