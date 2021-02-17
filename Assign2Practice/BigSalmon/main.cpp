#include <iostream>
#include "library/enumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/linsearch.hpp"

/*James BigLakeChampionship Tuna 50 Salmon 20 Sardine 5 Tuna 100
Was there a championship where the largest caught fish was a salmon?
*/

using namespace std;

struct Fish{
    string type;
    int size;
    friend istream &operator>>(istream &is,Fish &f)
    {
        is>> f.type >> f.size;
        return is;
    }
};

class BigFish1Contest : public MaxSearch<Fish,int>
{
    int func(const Fish& e) const override { return e.size;}
};

struct Contest{
    string angler;
    string name;
    Fish bigFish;
    friend istream &operator>>(istream &is, Contest &c);
};
istream &operator>>(istream &is, Contest &c)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> c.angler >> c.name;
    BigFish1Contest pr;
    StringStreamEnumerator<Fish> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    if (pr.found())
        c.bigFish = pr.optElem();
    return is;
}

class OverAllBigFish : public MaxSearch<Contest,int>
{
private:
    string _name;
public:
    OverAllBigFish(const string &name) : _name(name) {}
protected:
    bool whileCond(const Contest& e) const override { return e.name == _name;}
    int func(const Contest& e) const override { return e.bigFish.size;}
    void first() override { }
};


/*class ChkSalmon : public Summation<Contest,bool>
{
private:
    string _name;
public:
    ChkSalmon(const string name) : _name(name) {}
protected:
    virtual Value func(const Item& e) const = 0;
    virtual Value neutral() const = 0;
    virtual Value add( const bool& a, const bool& b) const override {return a || b; }
};*/

struct Champ{
    string name;
    bool isSalmonBig;
};
class FishEnumerator : public Enumerator<Champ>
{
private:
    SeqInFileEnumerator<Contest>* _f;
    Champ _champ;
    bool  _end;
public:
    FishEnumerator(const string fname) { _f = new SeqInFileEnumerator<Contest>(fname);}
    void first() override { _f->first(); next();}
    void next() override;
    bool end() const override { return _end;}
    Champ current() const override {return _champ;}
    ~FishEnumerator(){ delete _f;}
};
void FishEnumerator::next()
{
    if (_end = _f->end()) return;
    _champ.name = _f->current().name;
    OverAllBigFish pr(_champ.name);
    pr.addEnumerator(_f);
    pr.run();
    _champ.isSalmonBig = (pr.optElem().bigFish.type == "Salmon");
}
 class isThereBigSalmon : public LinSearch<Champ>
 {
     bool cond(const Champ& e) const override { return e.isSalmonBig;}
 };

int main(int argc, char** argv)
{
    try{
        string filname;
    isThereBigSalmon pr2;
    if (argc > 1) filename = argv[1];
    else filaname = "input.txt";
    FishEnumerator enor(filname);
    pr2.addEnumerator(&enor);
    pr2.run();
    cout << argc<<endl;
    cout << argv[0] <<" " <<argv[1]<<endl;
    if (pr2.found())
        cout <<"Yes there is a Championship namely: "<<pr2.elem().name <<" in which Salmon was the biggest fish caught.\n";
    else
        cout <<"No there is no such Championship in which Salmon was the biggest fish caught.\n";
    }catch(SeqInFileEnumerator<Contest>::Exceptions ex)
    {
        cout<<"File does not exist!\n";
    }
    return 0;
}
