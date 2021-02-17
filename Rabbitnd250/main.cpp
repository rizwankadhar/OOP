#include <iostream>
#include "library/enumerator.hpp"
#include "library/counting.hpp"
#include "library/linsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
/*Given a file containing data of huntings. Each line of the file consists of the name of the hunter, the
date of the hunting, the species and weight of the animal shot by the given hunter at the given
hunting. The file is sorted by hunter and then by date.
Count the hunters who shot a rabbit at each of his/her huntings and the total weight of animals
shot by the hunter is greater than 250 kg.*/
using namespace std;

struct oneHunt{
    string huntr;
    int weight;
    bool rabShot;
    friend istream &operator>>(istream &is, oneHunt &h);
};
istream &operator>>(istream &is, oneHunt &h)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    string date,specie;
    ss >> h.huntr >> date >> specie >> h.weight;
    h.rabShot = (specie == "Rabbit");
    return is;
}

struct Hunter{
    string hunter;
    int weightOfHunted;
    bool shotRabbit;
    Hunter() : hunter(""), weightOfHunted(0), shotRabbit(true) {}
    Hunter(string htr,int weight,bool sR) : hunter(htr), weightOfHunted(weight), shotRabbit(sR) {}
};
class sumResult : public Summation<oneHunt,Hunter>
{
private:
    string _name;
public:
    sumResult(const string &name) : _name(name) { }
protected:

    Hunter func(const oneHunt& e) const override { return Hunter(e.huntr,e.weight,e.rabShot);}
    Hunter neutral() const override { return Hunter();}
    Hunter add( const Hunter& a, const Hunter& b) const override { return Hunter(b.hunter,a.weightOfHunted+b.weightOfHunted,a.shotRabbit && b.shotRabbit);}
    void first() override { }
    bool whileCond(const oneHunt& e) const override { return e.huntr == _name;}
};

class HunterEnor : public Enumerator<Hunter>
{
private:
    SeqInFileEnumerator<oneHunt>* _f;
    Hunter _hunter;
    bool _end;
    bool _empty;
public:
    HunterEnor(const string &fname) : _empty(true) { _f = new SeqInFileEnumerator<oneHunt>(fname);}
    void first() override { _f->first(); next(); if (!end()) _empty = false;}
    void next() override;
    bool end() const override { return _end;}
    Hunter current() const override { return _hunter;}
    ~HunterEnor() { delete _f;}
    bool isEmpty() const { return _empty;}
};

void HunterEnor::next()
{
    if (_end = _f->end()) return;
    _hunter.hunter = _f->current().huntr;
    sumResult pr(_hunter.hunter);
    pr.addEnumerator(_f);
    pr.run();
    _hunter = pr.result();

}

class countRabHunters : public Counting<Hunter>
{
    bool cond(const Hunter& e) const override {
        return e.weightOfHunted > 250; }
};


int main(int argc, char** argv)
{
    try{
        string filename;
        if (argc>1) filename = argv[1];
        else filename = "input.txt";
        countRabHunters pr;
        HunterEnor enor(filename);
        pr.addEnumerator(&enor);
        pr.run();
        if (enor.isEmpty())
        {
            cout <<"There is no hunting data in file!\n";
        }
        else
        {
            if (pr.result() == 0)
            {
                cout <<"There are no hunters who meet this criteria in the file.\n";
            }
            else
            {
                cout <<"There are "<<pr.result() <<" hunters who have hunted rabbit at every hunting and weight of their hunted animals is more than 250.\n";

            }
        }
    }catch(SeqInFileEnumerator<oneHunt>::Exceptions e)
    {
        cout <<"File not found!";
    }
    return 0;
}
