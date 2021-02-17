#include <iostream>
#include "library/counting.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/maxsearch.hpp"


/*The results of the National Angler's Championship is stored in a text file.
Each line of the file contains the identifier of the participant and the championship
(strings without whitespace), and the list of the caught fish, which are stored as pairs:
(the kind of the fish, the size of the fish). The kind of the fish is a string without
whitespace, its size is a natural number. The data in a line are separated by whitespace.
The lines of the text file are sorted according to the name of the championship. You can assume that the text file is correct.
An example for a line of the text file:
James BigLakeChampionship Tuna 50 Salmon 20 Sardine 5 Tuna 100
At which championship has the most fish been caught
*/
using namespace std;



struct Fish{
    string name;
    int size;
    friend istream &operator>>(istream &is, Fish &f)
    {
        is >> f.name >> f.size;
        return is;
    }
};

class FishCount : public Counting<Fish> {};

struct Contest{
    string angler;
    string name;
    int catches;
    friend istream &operator>>(istream &is,Contest &C);
};

istream &operator>>(istream &is,Contest &C)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> C.angler >> C.name;
    FishCount pr;
    StringStreamEnumerator<Fish> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    C.catches = pr.result();
    return is;
}



struct Champ{
    string name;
    int Cnt;
};

class AllFish : public Summation<Contest,int>
{
private:
    string _name;
public:
    AllFish(const string &name) : _name(name) {}
protected:
    int func(const Contest& e) const override {return e.catches;}
    int neutral() const override { return 0;}
    int add( const int& a, const int& b) const override { return a+b;}
    bool whileCond(const Contest& e) const override { return e.name == _name; }
    void first() override { }

};

class FishEnumerator : public Enumerator<Champ>
{
private:
    SeqInFileEnumerator<Contest>* _f;
    Champ _champ;
    bool _end;
public:
    FishEnumerator(const string &fname) { _f = new SeqInFileEnumerator<Contest>(fname);}
    ~FishEnumerator(){ delete _f;}
    void first() override { _f->first(); next();}
    void next() override;
    bool end() const override {return _end;}
    Champ current() const override { return _champ;}
};
void FishEnumerator::next()
{
    if (_end = _f->end()) return;
    _champ.name = _f->current().name;
    AllFish pr2(_champ.name);
    pr2.addEnumerator(_f);
    pr2.run();
    _champ.Cnt = pr2.result();
}

class MaxFish : public MaxSearch<Champ,int>
{
protected:
    int func(const Champ& e) const override { return e.Cnt;}
};

int main()
{
    try{

    MaxFish pr3;
    FishEnumerator fenor("input.txt");
    pr3.addEnumerator(&fenor);
    pr3.run();
    cout << "Maximum Fish has been caught at " << pr3.optElem().name <<" which is "<<pr3.opt()<<"\n";
    }catch (SeqInFileEnumerator<Contest>::Exceptions e)
    {
        cout <<"File not found!\n";
    }
    return 0;
}
