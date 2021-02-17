#include <iostream>
#include "library/enumerator.hpp"
#include "library/linsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
/*Given a file containing data of huntings. Each line of the file consists of the name of the hunter, the
date of the hunting, the species and weight of the animal shot by the given hunter at the given
hunting. The file is sorted by hunter and then by date.
example line : Rizwan 2Jan18 Deer 42
Decide, whether every hunter has shot a bear at any of his/her hunting.*/
using namespace std;
/*
struct Prey{
    string specie;
    int weight;
    friend istream &operator>>(istream &is,Prey &p)
    {
        is >> p.specie >> p.weight;
        return is;
    }
};

class isBear : public LinSearch<Prey>
{
    bool cond(const Prey &e) const override { return e.specie == "Bear";}
};
*/
struct Hunt{
    string hunter;
    string date;
    bool shotBear;
    friend istream &operator>>(istream& is, Hunt &h);
};
istream &operator>>(istream& is, Hunt &h)
{
    string line;
    string animal;
    int weight;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> h.hunter >> h.date >> animal >> weight;
    /*isBear pr;
    StringStreamEnumerator<Prey> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    h.shotBear = pr.found();*/
    h.shotBear = (animal == "Bear");
    return is;
}

struct Hunter{
    string name;
    bool huntedBear;
};

class BearCheckforOne : public Summation<Hunt,bool>
{
private:
    string _name;
public:
    BearCheckforOne(const string name) : _name(name) {}
protected:
    bool func(const Hunt& e) const override { return e.shotBear;}
    bool neutral() const override { return false;}
    bool add( const bool& a, const bool& b) const override { return a || b;}
    bool whileCond(const Hunt& e) const override { return e.hunter == _name;}
    void first() override { }
};

class HunterEnumerator : public Enumerator<Hunter>
{
private:
    SeqInFileEnumerator<Hunt>* _f;
    Hunter _hunter;
    bool _end;
    bool _empty;
public:
    HunterEnumerator(const string &fname) : _empty(true) { _f = new SeqInFileEnumerator<Hunt>(fname);}
    void first() override { _f->first(); next(); if (!end()) _empty = false;}
    void next() override;
    bool end() const override { return _end;}
    Hunter current() const override {return _hunter; }
    ~HunterEnumerator(){ delete _f;}
    bool isEmpty() const {return _empty;}
};

void HunterEnumerator::next()
{
    if (_end = _f->end()) return;
    _hunter.name = _f->current().hunter;
    BearCheckforOne pr(_hunter.name);
    pr.addEnumerator(_f);
    pr.run();
    _hunter.huntedBear = pr.result();
}

class BearCheckAll : public LinSearch<Hunter,true>
{
    bool cond(const Hunter &e) const override {return e.huntedBear;}
};

int main(int argc,char** argv)
{
    try {
        string filename;
        if (argc>1) filename = argv[1];
        else filename = "input.txt";
        BearCheckAll pr;

        HunterEnumerator enor(filename);
        pr.addEnumerator(&enor);
        pr.run();
        if (enor.isEmpty())
        {
            cout <<"File is Empty!\n";
        }
        else {
            if (pr.found())
            {
                cout <<" Yes! all the hunters have shot Bear.";
            }
            else
            {
                cout <<" No! not all the hunters have shot Bear.";
            }
        }



    }catch(SeqInFileEnumerator<Hunt>::Exceptions ex)
    {
        cout <<"File not found!";
    }
    return 0;
}
