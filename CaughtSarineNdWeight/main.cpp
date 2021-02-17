#include <iostream>
#include "library/enumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
/*The results of the National Angler's Championship is stored in a text file.
Each line of the file contains the identifier of the participant and the
championship (strings without whitespace), and the list of the caught fish,
which are stored as pairs: (the kind of the fish, the size of the fish).
The kind of the fish is a string without whitespace, its size is a natural number.
The data in a line are separated by whitespace. The lines of the text file are sorted
according to the name of the championship. You can assume that the text file is correct.
An example for a line of the text file:
James BigLakeChampionship Tuna 50 Salmon 20 Sardine 5 Tuna 100
Give an angler who caught Sardine at all champs and also give the avg weight of one champ caught by him\her.
*/

using namespace std;

struct Fish{
    string type;
    int weight;
    friend istream &operator>>(istream &is,Fish &f)
    {
        is >>f.type >>f.weight;
        return is;
    }
};

struct Result{
    bool sardine;
    int weight;
    Result() : sardine(false), weight(0) {}
    Result(bool sard,int w) : sardine(sard), weight(w) { }
};

class sumResult : public Summation<Fish,Result>
{
    Result func(const Fish& e) const override { return Result(e.type == "Sardine",e.weight);}
    Result neutral() const override { return Result();}
    Result add( const Result& a, const Result& b) const override { return Result(a.sardine || b.sardine,a.weight+b.weight);}
};

struct Line{
    string name;
    string champ;
    bool sardine;
    int weight;
    friend istream &operator>>(istream &is,Line &l);

};
istream &operator>>(istream &is,Line &l)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> l.name >> l.champ;
    StringStreamEnumerator<Fish> ssenor(ss);
    sumResult pr;
    pr.addEnumerator(&ssenor);
    pr.run();
    l.sardine = pr.result().sardine;
    l.weight = pr.result().weight;
    return is;
}


struct AnglerSum{
    bool sardineAll;
    int weight;
    int count;
    AnglerSum() : sardineAll(true), weight(0), count(0) {}
    AnglerSum(bool sard,int w,int c): sardineAll(sard), weight(w), count(c) {}
};

class AnglerResult : public Summation<Line,AnglerSum>
{
private:
    string _name;
public:
    AnglerResult(const string &name) : _name(name) { }
protected:
    AnglerSum func(const Line& e) const override { return AnglerSum(e.sardine,e.weight,1);}
   AnglerSum neutral() const override { return AnglerSum();}
   AnglerSum add( const AnglerSum& a, const AnglerSum& b) const override { return AnglerSum(a.sardineAll && b.sardineAll,a.weight+b.weight,a.count + b.count);}
   bool whileCond(const Line &e) const override { return e.name == _name;}
   void first() override { }
};
struct Angler{
    string name;
    bool allSardines;
    double avg_weight;
};
class AnglerEnor : public Enumerator<Angler>
{
private:
    SeqInFileEnumerator<Line>* _f;
    Angler _angler;
    bool _end;
    bool _empty;
public:
    AnglerEnor(const string &fname) : _empty(true) { _f = new SeqInFileEnumerator<Line>(fname);}
    void first() override { _f->first(); next(); if (!end()) _empty = false;}
     void next() override;
     bool end() const override { return _end;}
     Angler current() const override { return _angler;}
     ~AnglerEnor() { delete _f;}
     bool isEmpty() const { return _empty;}
};

void AnglerEnor::next()
{
    if (_end = _f->end()) return;
    _angler.name = _f->current().name;
    AnglerResult pr(_angler.name);
    pr.addEnumerator(_f);
    pr.run();
    _angler.allSardines = pr.result().sardineAll;
    if (pr.result().count > 0)
    {
        _angler.avg_weight = double(pr.result().weight)/pr.result().count;
    }
    else _angler.avg_weight = 0;
}
class WriteOutput : public Summation<Angler,ostream>
{
public:
    WriteOutput(ostream *o) : Summation<Angler,ostream>(o) { }
protected:
    string func(const Angler &e) const override
    {
        ostringstream oss;
        oss << e.name <<" has caught Sardine at all the Championships and the average weight he caught in one championship is : " <<e.avg_weight <<"\n";
        return oss.str();
    }
    bool cond(const Angler &e) const override { return e.allSardines;}
};
int main()
{
    WriteOutput pr(&cout);
    AnglerEnor enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    return 0;
}
