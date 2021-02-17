#include <iostream>

using namespace std;
#include "library/seqinfileenumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/counting.hpp"


struct Data{
string first_name;
string last_name;
friend istream& operator>>(istream &is, Data &d);
};
istream& operator>>(istream &is, Data &d)
{
    is >> d.first_name >>d.last_name;
    return is;
}

class Frequency : public Counting<Data>
{
private:
    string _name;
public:
    Frequency(const string &firstname): _name(firstname) {}
protected:
    void first() override {}
    bool whileCond(const Data &e) const override { return  e.first_name == _name; }
};


struct Name_Frequency{
string name;
int freq;
};
class NameEnumerator : public Enumerator<Name_Frequency>
{
private:
    SeqInFileEnumerator<Data> *_f;
    Name_Frequency _curr ;
    bool _end;
public:
    NameEnumerator(const string &fname){
        _f = new SeqInFileEnumerator<Data>(fname);
    }
    ~NameEnumerator(){ delete _f; }
    void first() override { _f->first();  next(); }
    void next() override;
    Name_Frequency current() const override { return _curr; }
    bool end() const override { return _end; }
};

void NameEnumerator::next()
{
    if( (_end = _f->end()) ) return;

	_curr.name = _f->current().first_name;
    Frequency pr(_curr.name);
    pr.addEnumerator(_f);
    pr.run();
    _curr.freq = pr.result();
}
class MaxFreq : public MaxSearch<Name_Frequency,int>
{
protected:
    int func(const Name_Frequency &e) const { return e.freq; }
};

int main()
{
    try{
        MaxFreq pr2;
        NameEnumerator enor("input.txt");
        pr2.addEnumerator(&enor);
        pr2.run();
        if (pr2.found())
            cout << "Most repeated first name is " << pr2.optElem().name << " which is repeated " << pr2.opt() <<" times."<< endl;
        else
            cout << "There is no name in the file.\n";
    }catch (SeqInFileEnumerator<Data>::Exceptions e)
    {
        cout<<"This file does not exist!\n";
    }
    return 0;
}
