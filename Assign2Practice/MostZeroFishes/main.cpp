#include <iostream>
#include "library/counting.hpp"
#include "library/enumerator.hpp"
#include "library/linsearch.hpp"
#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
using namespace std;
/*James BigLakeChampionship Tuna 50 Salmon 20 Sardine 5 Tuna 100
Which angler participated in the most championships where he/she caught no fish?*/

struct Fish{
    string type;
    int size;
    friend istream &operator>>(istream &is,Fish &f)
    {
        is >> f.type >> f.size;
        return is;
    }
};

class FishCnt : public Counting<Fish> { };

struct Contest{
    string anglr;
    string championship;
    bool NoFish;
    friend istream &operator>>(istream &is,Contest &c);
};
istream &operator>>(istream &is,Contest &c)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> c.anglr >> c.championship;
    FishCnt pr;
    StringStreamEnumerator<Fish> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    c.NoFish = (pr.result()==0);
    return is;
}

class ZeroFishCnt : public Counting<Contest>
{
private:
    string _name;
public:
    ZeroFishCnt(const string name) : _name(name) {}
protected:
    bool whileCond(const Contest &e) const override {return e.anglr == _name;}
    bool cond(const Contest& e) const override { return e.NoFish; }
    void first() override {}
};

struct Angler{
    string name;
    int DucksCnt;
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
    ZeroFishCnt pr(_angler.name);
    pr.addEnumerator(_f);
    pr.run();
    _angler.DucksCnt = pr.result();
}

class MaxDucks : public MaxSearch<Angler,int>
{
    int func(const Angler& e) const override { return e.DucksCnt;}
};

int main()
{
    try{
    MaxDucks pr;
    ContestEnor enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    if (pr.opt()>0)
        cout <<"Angler named: "<<pr.optElem().name<<" participated in the most championships i.e "<<pr.opt()<<" where he caught no fish.";
    else
        cout<<"There is no such who angler participated in the most championships where he/she caught no fish\n";
    }catch(SeqInFileEnumerator<Contest>::Exceptions ex)
    {
        cout <<"There is no such file!\n";
    }
    return 0;
}
