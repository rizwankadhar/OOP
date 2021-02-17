#include <iostream>
#include "library/enumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
/*In a sequential input file, transactions of customers are stored. Each transaction contains the
customer’s ID, the transaction’s date, and the amount which is a signed integer (depending on the
type of the transaction: positive if it is a deposit and negative if it is e.g. a withdrawal). The file is
ordered by the customers’ ID. Find the highest balance among the negative balances.
Rizwan 12Jan18 1000
*/
using namespace std;

struct Transaction{
    string ID;
    int amount;
    friend istream &operator>>(istream &is,Transaction &t)
    {
        string date;
        is >>t.ID >> date >> t.amount;
        return is;
    }
};
struct Customer{
    string custID;
    int bal;
};

class Calculate : public Summation<Transaction,int>
{
private:
    string _iD;
public:
    Calculate(const string &id) : _iD(id) { }
protected:
    int func(const Transaction& e) const override { return e.amount;}
    int neutral() const override { return 0;}
    int add(const int& a, const int& b) const override { return a+b;}
    void first() override { }
    bool whileCond(const Transaction& e) const override { return e.ID == _iD;}
};

class BankEnor : public Enumerator<Customer>
{
private:
    SeqInFileEnumerator<Transaction>* _f;
    Customer _cust;
    bool _end;
    bool _empty;
public:
    BankEnor(const string &fname) : _empty(true) {_f = new SeqInFileEnumerator<Transaction>(fname);}
    void first() override { _f->first(); next(); if (!end()) _empty = false;}
    void next() override;
    bool end() const override { return _end;}
    Customer current() const override { return _cust;}
    bool isEmpty() const {return _empty;}
    ~BankEnor() { delete _f;}
};
void BankEnor::next()
{
    if (_end = _f->end()) return;
    _cust.custID = _f->current().ID;
    Calculate pr(_cust.custID);
    pr.addEnumerator(_f);
    pr.run();
    _cust.bal = pr.result();
}

class MaxNegative : public MaxSearch<Customer,int>
{
    int func(const Customer &e) const override { return e.bal;}
    bool cond(const Customer& e) const override { return e.bal < 0;}
};



int main(int argc, char** argv)
{
    try{
        string filename;
        if (argc > 1) filename = argv[1];
        else filename = "input.txt";
        MaxNegative pr;
        BankEnor enor(filename);
        pr.addEnumerator(&enor);
        pr.run();
        if (!enor.isEmpty())
        {
            if (pr.found())
            {
                cout <<"The ID of the customer with highest balance from negative balances is : "<<pr.optElem().custID <<" and the balance is: "<<pr.opt()<<".\n";
            }
            else
            {
                cout <<"Yuh bruh, everyone is rich there...There is no account with negative balance.";
            }
        }
        else
            {
            cout <<"Bruh...are you kiddin me ...File is empty!\n";
        }

    }catch(SeqInFileEnumerator<Transaction>::Exceptions e)
    {
        cout <<"Yo Bruh...Gimme a valid filename..!\n";
    }
    return 0;
}
