#include <iostream>
#include "library/counting.hpp"
#include "library/enumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"

using namespace std;
/*James BigLakeChampionship Tuna 50 Salmon 20 Sardine 5 Tuna 100
Which championship had the most participants?*/

struct Fish{
    string type;
    int size;
    friend istream &operator>>(istream &is, Fish &f)
    {
        is >> f.type >> f.size;
        return is;
    }
};

class FishCnt : public Counting<Fish> { };

struct Contest{
    string angler;
    string name;
    int catches;
    friend istream &operator>>(istream &is, Contest &c);
};

istream &operator>>(istream &is, Contest &c)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> c.angler >>c.name;
    FishCnt pr;
    StringStreamEnumerator<Fish> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    c.catches = pr.result();
    return is;
}

class ParticipantCnt : public Counting<Contest>
{
private:
    string _name;
public:
    ParticipantCnt(const string name) : _name(name) {}
protected:
    bool whileCond(const Contest& e) const override { return e.name == _name; }
    void first() override {}
};

struct Champ
{
    string name;
    int participants;
};

class ContestEnumerator : public Enumerator<Champ>
{
private:
    SeqInFileEnumerator<Contest>* _f;
    Champ _champ;
    bool _end;
public:
    ContestEnumerator(const string &fname) { _f = new SeqInFileEnumerator<Contest>(fname);}
    void first() override { _f->first(); next();}
    void next() override;
    bool end() const override {return _end;}
    Champ current() const override {return _champ;}
    ~ContestEnumerator(){ delete _f;}
};

void ContestEnumerator::next()
{
    if (_end = _f->end()) return;
    _champ.name = _f->current().name;
    ParticipantCnt pr2(_champ.name);
    pr2.addEnumerator(_f);
    pr2.run();
    _champ.participants = pr2.result();
}

class MaxParticipant : public MaxSearch<Champ,int>
{
    int func(const Champ& e) const override { return e.participants;}
};

int main()
{
    try{
    MaxParticipant pr;
    ContestEnumerator enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    if (pr.found())
        cout << "The Championship with most participants is " <<pr.optElem().name<<" in which there were "<<pr.opt()<<" participants."<<  endl;
    else
        cout << "There is no Championship!\n";
    }catch(SeqInFileEnumerator<Contest>::Exceptions ex)
    {
        cout<<"File does not exist!\n";
    }
    return 0;
}
