#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/linsearch.hpp"
#include "library/enumerator.hpp"



using namespace std;

/**
A motorbike service has registered the repairs of the different motorcycles in a sequential input file.
One line of the file contains the customer’s name, the type of the motorbike, and the repairs: name-price pairs.
The file is ordered by customer names. You can assume that the file’s structure is correct.
One sample line of the file:
Customer1 YamahaAxis50 oilchange 20 motorblock 100 cablesealing 10.
How many customers have at least two motorbikes that had a service more expensive than 95 euros?

*/

struct Repair
{
    string name;
    int cost;
    friend istream& operator>>(istream &is, Repair &r)
    {
        is>>r.name >> r.cost;
        return is;
    }

};

struct Result
{
    bool above95;
    Result() : above95(false) {}
    Result(bool above) : above95(above) {}
};

class sumAll : public Summation<Repair,Result>
{
    Result func(const Repair& e) const override {
        return Result(e.cost > 95);
        }
    Result neutral() const override {return Result();}
    Result add(const Result& a, const Result& b) const override {
        return Result(a.above95 || b.above95);
        }
};
/*
class myCount : public Summation<Output,int>
{
    int func(const Result& e) const override {return e.co>95 ? 1 : 0;}
    int neutral() const override {return 0;}
    int add( const int& a, const int& b) const override { return a+b; }
};
*/
struct CustomerLine
{
    string customer;
    string motorbike;
    bool highcostcounter;
    friend istream& operator>>(istream &is, CustomerLine &o)
    {
        string line;
        getline (is,line,'\n');
        stringstream ss(line);
        ss>>o.customer>>o.motorbike;
        StringStreamEnumerator<Repair> ssenor(ss);
        sumAll pr;
        pr.addEnumerator(&ssenor);
        pr.run();
        o.highcostcounter = pr.result().above95;
        return is;
    }
};


class sumResult : public Summation<CustomerLine,int>
{
private:
    string _name;
public:
    sumResult(const string &str) : _name(str) {}
    int func(const CustomerLine& e) const override { return (e.highcostcounter?1:0);}
    int neutral() const override { return 0;}
    int add( const int& a, const int& b) const override { return a+b;}
    void first() override { }
    bool whileCond(const CustomerLine &e) const override { return e.customer == _name;}
};

struct Output{
    string name;
    bool highcost;
};
class myEnum : public Enumerator<Output>
{
    SeqInFileEnumerator<CustomerLine>* _f;
    Output _curr;
    bool _end;
public:
    myEnum(const string &file)  { _f = new SeqInFileEnumerator<CustomerLine>(file);}
    void first() override {_f->first();  next();}
    void next() override;
    bool end() const override { return _end;}
    Output current() const override {return _curr;}
    ~myEnum() { delete _f;}
};
void myEnum::next()
{
    if (_end = _f->end()) return;
    _curr.name = _f->current().customer;
    sumResult br(_curr.name);
    br.addEnumerator(_f);
    br.run();
    _curr.highcost = br.result() >= 2;
}

class bikes : public Summation<Output,int>
{
    int func(const Output& e) const override { return 1;}
    int neutral() const override { return 0;}
    int add( const int& a, const int& b) const override {  return a+b;}
    bool cond(const Output &e) const override { return e.highcost;}
};
int main()
{
    myEnum enor("input.txt");
    bikes pr;
    pr.addEnumerator(&enor);
    pr.run();
    cout <<pr.result()<<endl;

    return 0;
}
