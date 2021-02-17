#include <iostream>
#include <vector>
#include "library/enumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/linsearch.hpp"
/*The results of the National Angler's Championship is stored in a text file.
Each line of the file contains the identifier of the participant and the championship
(strings without whitespace), and the list of the caught fish, which are stored as pairs:
(the kind of the fish, the size of the fish). The kind of the fish is a string without whitespace, its size is a natural number. The data in a line are separated by whitespace. The lines of the text file are sorted according to the name of the championship. You can assume that the text file is correct.
An example for a line of the text file:
James BigLakeChampionship Tuna 50 Salmon 20 Sardine 5 Tuna 100
List all the championships where tuna has been caught.
*/
using namespace std;
struct Fish{
    string type;
    int size;
    friend istream &operator>>(istream &is, Fish &f)
    {
        is >> f.type >> f.size;
    }
};

class TunaCaught : public LinSearch<Fish>
{
    bool cond(const Fish &e) const override {return e.type == "Tuna";}
};

struct Contest{
    string angler;
    string name;
    bool caughtTuna;
    friend istream &operator>>(istream &is,Contest &c);
};

istream &operator>>(istream &is,Contest &c)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> c.angler >> c.name;
    TunaCaught pr;
    StringStreamEnumerator<Fish> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    c.caughtTuna = pr.found();
    return is;
}

struct Champ{
    string name;
    bool Tuna;
};
class ChampsWidTuna : public Summation<Contest,bool>
{
private:
    string _name;
public:
    ChampsWidTuna(const string name) : _name(name) {}
protected:

    bool func(const Contest& e) const override { return e.caughtTuna;}
    bool neutral() const override { return false;}
    bool add( const bool& a, const bool& b) const override { return a || b; }
    bool whileCond(const Contest& e) const { return e.name == _name; }
    void first() override { }

};

class FishEnumerator : public Enumerator<Champ>
{
private:
    SeqInFileEnumerator<Contest>* _f;
    Champ _champ;
    bool _end;
public:
    FishEnumerator(const string fname) { _f = new SeqInFileEnumerator<Contest>(fname);}
    ~FishEnumerator() { delete _f;}
    void first() override { _f->first(); next();}
    void next() override;
    bool end() const override { return _end;}
    Champ current() const override { return _champ;}

};

void FishEnumerator::next()
{
    if (_end = _f->end()) return;
    _champ.name = _f->current().name;
    ChampsWidTuna pr2(_champ.name);
    pr2.addEnumerator(_f);
    pr2.run();
    _champ.Tuna = pr2.result();
}

class Assort : public Summation<Champ,ostream>
{
public:
    Assort(ostream *o) : Summation<Champ,ostream>(o) { }
protected:
    string func(const Champ& e) const override
    {
        ostringstream oss(e.name);
        oss << e.name <<" \n";
        return oss.str();
    }
    bool cond(const Champ& e) const { return e.Tuna; }
};



int main()
{
    try{
    Assort pr(&cout);
    FishEnumerator enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    }catch(SeqInFileEnumerator<Contest>::Exceptions ex)
    {
        cout <<"File does not exist!\n";
    }

    return 0;
}
