#include <iostream>
#include "library/counting.hpp"
#include "library/enumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
using namespace std;
/*The results of the National Angler's Championship is stored in a text file.
Each line of the file contains the identifier of the participant and the championship
(strings without whitespace), and the list of the caught fish, which are stored as pairs:
(the kind of the fish, the size of the fish). The kind of the fish is a string without
whitespace, its size is a natural number. The data in a line are separated by whitespace.
The lines of the text file are sorted according to the name of the championship. You can assume that the text file is correct.
An example for a line of the text file:
James BigLakeChampionship Tuna 50 Salmon 20 Sardine 5 Tuna 100
At how many championships has no fish been caught.
*/

struct Fish{
    string type;
    int size;
    friend istream &operator>>(istream &is,Fish &f)
    {
        is >> f.type >> f.size;
    }
};
class FishCnt : public Counting<Fish> { } ;

struct Contest{
    string angler;
    string name;
    bool caught;
    friend istream &operator>>(istream &is,Contest &c);
};
istream &operator>>(istream &is,Contest &c)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> c.angler >> c.name;
    FishCnt pr;
    StringStreamEnumerator<Fish> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    c.caught = (pr.result() == 0);
    return is;
}

struct Champ{
    string name;
    bool fishcaught;
};

class NoFish : public Summation<Contest,bool>
{
private:
    string _name;
public:
    NoFish(const string &name) : _name(name) {}
protected:
    bool func(const Contest& e) const override {return e.caught;}
    bool neutral() const override { return true;}
    bool add( const bool& a, const bool& b) const override { return a && b;}
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
    FishEnumerator(const string fname) { _f = new SeqInFileEnumerator<Contest>(fname);}
    ~FishEnumerator() { delete _f;}
    void first() override { _f->first(); next(); }
    void next() override;
    bool end() const override { return _end;}
    Champ current() const override { return _champ;}
};
void FishEnumerator::next()
{
    if (_end = _f->end()) return;
    _champ.name = _f->current().name;
    NoFish pr2(_champ.name);
    pr2.addEnumerator(_f);
    pr2.run();
    _champ.fishcaught = pr2.result();
}
class ZeroFish : public Counting<Champ>
{
protected:
    bool cond(const Champ& current) const override { return current.fishcaught; }
};

int main()
{
    try{
    ZeroFish pr3;
    FishEnumerator fenor("input.txt");
    pr3.addEnumerator(&fenor);
    pr3.run();
    cout << "The number of championships with zero fish caught is :"<<pr3.result() <<endl;
    }catch (SeqInFileEnumerator<Contest>::Exceptions ex)
    {
        cout <<"File does not exist!\n";
    }
    return 0;
}
