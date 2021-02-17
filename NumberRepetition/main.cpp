#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include "library/counting.hpp"
#include "library/enumerator.hpp"
#include "library/maxsearch.hpp"
/*Integers are stored in a sequential input file sorted in ascending order. Count how many times each
number occurs in the file and write the (number, count) records into a sequential output file.*/
using namespace std;


struct Frequency{
    int number;
    int Count;
};

class CountOccurence : public Summation<int,int>
{
private:
    int _curr;
public:
    CountOccurence(const int &n) : _curr(n) {}
protected:
    int func(const int& e) const override { return 1;}
    int neutral() const override { return 0;}
    int add( const int& a, const int& b) const override { return a+b;}
    bool cond(const int& e) const override { return e == _curr; }
    void first() override {}
};

class IntEnumerator : public Enumerator<Frequency>
{
private:
    SeqInFileEnumerator<int>* _f;
    Frequency _frequency;
    bool _end;
    bool _empty;
public:
    IntEnumerator(const string &fname) : _empty(true) { _f = new SeqInFileEnumerator<int>(fname);}
    void first() override { _f->first(); next(); if (!end()) _empty = false ;}
    void next() override;
    bool end() const override { return _end;}
    Frequency current() const override { return _frequency;}
    ~IntEnumerator(){ delete _f;}
};

void IntEnumerator::next()
{
    if (_end = _f->end()) return;
    _frequency.number = _f->current();
    CountOccurence pr(_frequency.number);
    pr.addEnumerator(_f);
    pr.run();
    cout <<_frequency.number << " " << pr.result()<<endl;
    _frequency.Count = pr.result();
}

/*class WriteToFile : public Summation<Frequency,ostream>
{
public:
    WriteToFile(ostream *o) : Summation<Frequency,ostream>::Summation(o) { }
protected:
    string func(const Frequency& e) const override
     {
         return ("("+to_string(e.number) + "," + to_string(e.Count) + ")\n");
     }
};
*/
class Max : public MaxSearch<Frequency,int>
{
    int func(const Frequency& e) const override { return e.Count;}
};
int main()
{
    ///ofstream f("output.txt");
    ///WriteToFile pr(&cout);
    Max pr;
    IntEnumerator enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    cout << pr.optElem().number << " "<< pr.optElem().Count<<endl;
    return 0;
}
