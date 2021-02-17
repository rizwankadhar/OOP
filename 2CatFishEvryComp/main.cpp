#include <iostream>
#include "library/enumerator.hpp"
#include "library/counting.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/linsearch.hpp"
/*At every competition of the National Angling Championship, the results of the competitors were
recorded and put into a text file. Every line of the file contains the name of the angler the ID
of the competition (string without spaces), and the species and the size of the caught fishes
(pair of a string without spaces and a natural number). Data is separated by space or tab.
The lines of the file are ordered by the name of the anglers. The file is assumed to be in
the correct form. Sample line in the file:
PETER LAC0512 carp 45 carp 53 catfish 96
Give all those anglers who caught at least two catfishes on every competition they participated in.*/
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

class CatCount : public Counting<Fish>
{
    bool cond(const Fish& e) const override { return e.type == "catfish";}
};

struct Contest{
    string angler;
    string championship;
    bool CatFishes;
    friend istream &operator>>(istream &is,Contest &c);
};
istream &operator>>(istream &is,Contest &c)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> c.angler >>c.championship;
    StringStreamEnumerator<Fish> ssenor(ss);
    CatCount pr;
    pr.addEnumerator(&ssenor);
    pr.run();
    c.CatFishes = (pr.result() >= 2);
    return is;
}

struct Angler{
    string name;
    bool twoCats;
    ///int noOfCatFishes;
};
class CatFishes : public Summation<Contest,bool>
{
private:
    string _name;
public:
    CatFishes(const string &name) : _name(name) {}
protected:
    bool func(const Contest& e) const override { return e.CatFishes;}
    bool neutral() const override { return true;}
    bool add( const bool& a, const bool& b) const override { return a && b;}
    bool whileCond(const Contest &e) const override { return e.angler == _name;}
    void first() override { }
} ;
/*
class CatFishes : public Summation<Contest,int>
{
private:
    string _name;
public:
    CatFishes(const string &name) : _name(name) {}
protected:
    int func(const Contest& e) const override { return e.CatFishes;}
    int neutral() const override { return 0;}
    int add( const int& a, const int& b) const override { return a+b;}
    void first() override {}
    bool whileCond(const Contest &e) const override { return e.angler == _name;}
};
*/
class FishEnor : public Enumerator<Angler>
{
private:
    SeqInFileEnumerator<Contest>* _f;
    Angler _angler;
    bool _end;
    bool _empty;
public:
    FishEnor(const string &fname) : _empty(true) {_f = new SeqInFileEnumerator<Contest>(fname);}
    void first() override { _f->first(); next(); if (!end()) _empty = false;}
    void next() override;
    bool end() const override { return _end;}
    Angler current() const override { return _angler;}
    bool isEmpty() const {return _empty;}
    ~FishEnor() { delete _f;}
};
void FishEnor::next()
{
    if (_end = _f->end()) return;
    _angler.name = _f->current().angler;
    CatFishes pr(_angler.name);
    pr.addEnumerator(_f);
    pr.run();
    _angler.twoCats = pr.result();
    ///cout <<_angler.noOfCatFishes<<endl;
}

class WriteOutput : public Summation<Angler,ostream>
{
public:
    WriteOutput(ostream* o) : Summation<Angler,ostream> (o) { }
protected:
    string func(const Angler &e) const override
    {
        ostringstream oss(e.name);
        oss << e.name <<" caught at least two catfishes on every competition he participated in.\n";
        return oss.str();
    }
    bool cond(const Angler &e) const override { return e.twoCats;}
};

int main(int argc,char** argv)
{
    try{
        string filename;
        if (argc > 1) filename = argv[1];
        else filename = "input.txt";
        WriteOutput pr(&cout);
        FishEnor enor(filename);
        pr.addEnumerator(&enor);
        pr.run();
        if (enor.isEmpty())
        {
            cout <<"Bruh...you gave me empty file!!!!\n";
        }
    }catch(SeqInFileEnumerator<Contest>::Exceptions e)
    {
        cout<<"Bruh....That aint a file!!!!\n";
    }
    return 0;
}
