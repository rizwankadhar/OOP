#include <iostream>
#include "library/enumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
/*In a sequential input file, transactions of customers are stored. Each transaction contains the
customer’s ID, the transaction’s date, and the amount which is a signed integer (depending on the
type of the transaction: positive if it is a deposit and negative if it is e.g. a withdrawal). The file is
ordered by the customers’ ID. Find the customers whose balance is less than 0 and who have 2 or more withdrawls.
Rizwan 12Jan18 1000
*/
using namespace std;

struct Transaction{
    string ID;
    int amount;
    bool withdraw;
    friend istream &operator>>(istream &is,Transaction &t)
    {
        string date;
        is >>t.ID >> date >> t.amount;
        t.withdraw = t.amount < 0;
        return is;
    }
};

struct Account{
    string custID;
    int bal;
    int withdraws;
    Account() : custID(""), bal(0), withdraws(0) {}
    Account(string id,int tran,int wdr) : custID(id), bal(tran), withdraws(wdr) {}
};

class Calculate : public Summation<Transaction,Account>
{
private:
    string _iD;
public:
    Calculate(const string &id) : _iD(id) { }
protected:
    Account func(const Transaction& e) const override { return Account(e.ID,e.amount,e.withdraw?1:0);}
    Account neutral() const override { return Account();}
    Account add(const Account& a, const Account& b) const override { return Account(b.custID,a.bal + b.bal,a.withdraws + b.withdraws);}
    void first() override { }
    bool whileCond(const Transaction& e) const override { return e.ID == _iD;}
};
/*
struct Customer{
    string ID;
    int bal;
    int noOfWithdrawls;
};
*/
class BankEnor : public Enumerator<Account>
{
private:
    SeqInFileEnumerator<Transaction>* _f;
    Account _cust;
    bool _end;
    bool _empty;
public:
    BankEnor(const string &fname) : _empty(true) {_f = new SeqInFileEnumerator<Transaction>(fname);}
    void first() override { _f->first(); next(); if (!end()) _empty = false;}
    void next() override;
    bool end() const override { return _end;}
    Account current() const override { return _cust;}
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
    _cust = pr.result();
    /*_cust.bal = pr.result().bal;
    _cust.noOfWithdrawls = pr.result().withdraws;
    */
}

class WriteOutput : public Summation<Account,ostream>
{
public:
    WriteOutput(ostream *o) : Summation<Account,ostream> (o) {}
protected:
    string func(const Account& e) const override
    {
        ostringstream oss;
        oss <<"The customer with ID: "<<e.custID << " has the balance: "<<e.bal <<" and number of withdraws is "<<e.withdraws<<".\n";
        return oss.str();
    }
    bool cond(const Account& e) const override { return e.withdraws >= 2; }
};
int main(int argc,char** argv)
{
    try{
        string filename;
        if (argc > 1) filename = argv[1];
        else filename = "input.txt";

        WriteOutput pr(&cout);
        BankEnor enor(filename);
        pr.addEnumerator(&enor);
        pr.run();
        if (enor.isEmpty())
        {
            cout <<"Bruh...not wrote this code for empty files!";
        }
    }catch(SeqInFileEnumerator<Transaction>::Exceptions e)
    {
        cout <<"Am I a joke to you!!!!,,,gimme a valid filename.\n";
    }

    return 0;
}
