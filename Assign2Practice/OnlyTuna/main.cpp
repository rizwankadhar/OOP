#include <iostream>
#include "library/counting.hpp"
#include "library/enumerator.hpp"
#include "library/linsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"

using namespace std;
/*James BigLakeChampionship Tuna 50 Salmon 20 Sardine 5 Tuna 100
How many anglers caught only tuna at the championships?*/

struct Fish{
    string type;
    int size;
    friend istream &operator>>(istream &is, Fish &f)
    {
        is >> f.type >>f.size;
        return is;
    }
};
class onlyTunaOnce : public LinSearch<Fish,true>
{
    bool cond(const Fish& e) const override {return e.type == "Tuna";}
};

struct Contest{
    string anglr;
    string championship;
    bool justTuna;
    friend istream &operator>>(istream &is,Contest &c);
};

istream &operator>>(istream &is,Contest &c)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> c.anglr >> c.championship;
    onlyTunaOnce pr;
    StringStreamEnumerator<Fish> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    c.justTuna = pr.found();
    return is;
}

class onlyTunaAtAll : public Summation<Contest,bool>
{
private:
    string _name;
public:
    onlyTunaAtAll(const string name) : _name(name) {}
protected:
    bool whileCond(const Contest &e) const override {return e.anglr == _name;}
    bool func(const Contest& e) const override { return e.justTuna;}
    bool neutral() const override {return true;}
    bool add( const bool& a, const bool& b) const override {return a && b; }
    void first() override {}
};

struct Angler{
    string name;
    bool OnlyCaughtTuna;
};

class ContestEnor : public Enumerator<Angler>
{
private:
    SeqInFileEnumerator<Contest>* _f;
    Angler _angler;
    bool _end;
public:
    ContestEnor(const string fname) {_f = new SeqInFileEnumerator<Contest>(fname);}
    void first() override { _f->first();next();}
    void next() override;
    bool end() const override { return _end;}
    Angler current() const override { return _angler;}
    ~ContestEnor() { delete _f; }
};

void ContestEnor::next()
{
    if (_end = _f->end()) return;
    _angler.name = _f->current().anglr;
    onlyTunaAtAll pr(_angler.name);
    pr.addEnumerator(_f);
    pr.run();
    _angler.OnlyCaughtTuna = pr.result();
}

class onlyTunaCatchers : public Counting<Angler>
{
    bool cond(const Angler& e) const override { return e.OnlyCaughtTuna; }
};

int main()
{
    onlyTunaCatchers pr;
    ContestEnor enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    cout <<pr.result()<<" anglers caught only tuna at the championships.\n";
    return 0;
}
