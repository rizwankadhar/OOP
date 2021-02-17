#include <iostream>
#include "library/summation.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/linsearch.hpp"
#include "library/counting.hpp"

using namespace std;
struct Concert{
    string city;
    int type;
    int sold;
     friend istream &operator>>(istream &is, Concert &c)
        {
        is >> c.city >> c.type >> c.sold;
        return is;
        }
};

class indoor : public LinSearch<Concert>
{
    bool cond(const Concert &e) const override { return e.type == 0;}
};

struct Line{
    string name;
    string genre;
    bool atLeastOne;
    friend istream &operator>>(istream &is,Line &l);

};

istream &operator>>(istream &is,Line &l)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> l.name >> l.genre;
    StringStreamEnumerator<Concert> ssenor(ss);
    indoor pr;
    pr.addEnumerator(&ssenor);
    pr.run();
    l.atLeastOne = pr.found();
    ///cout <<l.name<< " " <<l.genre <<" "<<l.atLeastOne<<endl;
    return is;
}

class AddIndoor : public Counting<Line>
{
private:
    string _name;
public:
    AddIndoor(const string &name) : _name(name) { }
protected:
    bool cond(const Line &e) const override { return e.atLeastOne;}
    bool whileCond(const Line &e) const override { return e.name == _name;}
    void first() override { }
} ;

struct Band{
    string name;
    int indoors;
};

class BandEnor : public Enumerator<Band>
{
    private:
    SeqInFileEnumerator<Line>* _f;
    Band _curr;
    bool _end;
public:
    BandEnor(const string &fname) { _f = new SeqInFileEnumerator<Line>(fname);}
    void first() override {_f->first();  next(); }
    void next() override;
    bool end() const override { return _end;}
    Band current() const override {return _curr;}
    ~BandEnor() { delete _f;}
};
void BandEnor::next()
{
    if (_end = _f->end()) return;
    _curr.name = _f->current().name;
    AddIndoor pr(_curr.name);
    pr.addEnumerator(_f);
    pr.run();
    _curr.indoors = pr.result();
}
class OutPut : public Counting<Band>
{
    bool cond(const Band &e) const override { return e.indoors >=1;}
};

int main()
{
    OutPut pr;
    BandEnor enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();

    cout <<pr.result()<<endl;
    return 0;
}




