#include <iostream>
#include "library/enumerator.hpp"
#include "library/linsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
using namespace std;
/*James BigLakeChampionship Tuna 50 Salmon 20 Sardine 5 Tuna 100
Was there an angler who caught a sardine at all the championships where he/she
participated?*/

struct Fish{
    string type;
    int size;
    friend istream &operator>>(istream &is,Fish &f)
    {
        is >> f.type >> f.size;
        return is;
    }
};

class SardineIn1Champ : public LinSearch<Fish>
{
    bool cond(const Fish& e) const override {return e.type == "Sardine";}
};

struct Contest{
    string anglr;
    string championship;
    bool caughtSardine;
    friend istream &operator>>(istream &is,Contest &c);
};

istream &operator>>(istream &is,Contest &c)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> c.anglr >> c.championship;
    SardineIn1Champ pr;
    StringStreamEnumerator<Fish> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    c.caughtSardine = pr.found();
    return is;
}

struct Angler{
    string name;
    bool SardineCaughtAll;
};

class SardineAtAll : public Summation<Contest,bool>
{
private:
    string _name;
public:
    SardineAtAll(const string name) : _name(name) {}
protected:
    bool func(const Contest& e) const override { return e.caughtSardine;}
    bool neutral() const override { return true;}
    bool add( const bool& a, const bool& b) const override { return a && b; }
    bool whileCond(const Contest &e) const override { return e.anglr == _name; }
    void first() override { }
};

class ContestEnor : public Enumerator<Angler>
{
private:
    SeqInFileEnumerator<Contest>* _f;
    Angler _angler;
    bool _end;
public:
    ContestEnor(const string fname) {_f = new SeqInFileEnumerator<Contest>(fname);}
    void first() override {_f->first();next();}
    void next() override;
    bool end() const override {return _end;}
    Angler current() const override { return _angler;}
    ~ContestEnor(){ delete _f;}

};


void ContestEnor::next()
{
    if (_end = _f->end()) return;
    _angler.name = _f->current().anglr;
    SardineAtAll pr(_angler.name);
    pr.addEnumerator(_f);
    pr.run();
    _angler.SardineCaughtAll = pr.result();
}

class AnglerWithSardineAll : public LinSearch<Angler>
{
    bool cond(const Angler &e) const override {return e.SardineCaughtAll;}
};


int main()
{
    AnglerWithSardineAll pr;
    ContestEnor enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    if (pr.found())
        cout<<"Yes! There is an Angler named: "<<pr.elem().name<<" who caught Sardines at all the Championships he participated.\n";
    else
    cout <<"There is no such angler who caught Sardines at all the Championships he participated.\n";
    return 0;
}
