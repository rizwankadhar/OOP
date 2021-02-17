#include <iostream>
#include "library/enumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/counting.hpp"
#include "library/linsearch.hpp"
/*
A motorbike service has registered the repairs of the different motorcycles in a textfile.
 One line of the file contains the customer’s name, the type of the motorbike,
 and the repairs: name-price pairs. The file is ordered by customer names.
 You can assume that the file’s structure is correct. One sample line of the file:
Customer1 YamahaAxis50 oilchange 20 motorblock 100 cablesealing 10

For grade 5: How many customers have at least two motorbikes that had a service more expensive than 95 euros?

*/
using namespace std;

struct Repair{
    string type;
    int price;
    friend istream &operator>>(istream &is,Repair &r)
    {
        is >>r.type >> r.price;
        return is;
    }
};

class ServiceCost : public LinSearch<Repair>
{
    bool cond(const Repair &e) const override { return e.price > 95;}
};

struct oneBike{
    string owner;
    string type;
    bool morethan95;
    friend istream &operator>>(istream &is, oneBike &b);
};
istream &operator>>(istream &is, oneBike &b)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> b.owner >> b.type;
    StringStreamEnumerator<Repair> ssenor(ss);
    ServiceCost pr;
    pr.addEnumerator(&ssenor);
    pr.run();
    b.morethan95 = pr.found();
    return is;
}

class CountExpensive : public Counting<oneBike>
{
private:
    string _name;
public:
    CountExpensive(const string &name) : _name(name) { }
protected:
    bool cond(const oneBike &e) const override { return e.morethan95;}
    bool whileCond(const oneBike &e) const override { return e.owner == _name;}
    void first() override { }
};

struct Customer{
    string name;
    int junkBikes;
};

class BikeEnumerator : public Enumerator<Customer>
{
private:
    SeqInFileEnumerator<oneBike>* _f;
    Customer _cust;
    bool _end;
    bool _empty;
public:
    BikeEnumerator(const string &fname) : _empty(true) { _f = new SeqInFileEnumerator<oneBike>(fname);}
    void first() override {_f->first();  next();  if (!end()) _empty = false; }
    void next() override;
    bool end() const override { return _end;}
    Customer current() const override {return _cust;}
    bool isEmpty() const { return _empty;}
    ~BikeEnumerator() { delete _f;}

};

void BikeEnumerator::next()
{
    if (_end = _f->end()) return;
    _cust.name = _f->current().owner;
    CountExpensive pr(_cust.name);
    pr.addEnumerator(_f);
    pr.run();
    _cust.junkBikes = pr.result();
}

class atLeast2Bikes : public Counting<Customer>
{
    bool cond(const Customer &e) const override { return e.junkBikes >= 2;}
};

int main(int argc,char** argv)
{
    try{
        string filename;
        if (argc > 1)
            filename = argv[1];
        else
            filename = "test1.txt";

        BikeEnumerator enor(filename);
        atLeast2Bikes pr;
        pr.addEnumerator(&enor);
        pr.run();

        if (enor.isEmpty())
        {
            cout <<"There is no bike in the file!\n";
        }
        else if (pr.result() == 0)
        {
            cout <<"There was no customer who has at least two motorbikes that had a service more expensive than 95 euros.\n";
        }
        else
        {
            cout <<"There are(is) "<<pr.result() <<" customer(s) who have at least two motorbikes that had a service more expensive than 95 euros.\n";
        }
    }catch(SeqInFileEnumerator<oneBike>::Exceptions e)
    {
        cout <<"File not found!";
        return 1;
    }
    return 0;
}
