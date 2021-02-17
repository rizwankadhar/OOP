#include <iostream>
#include "library/enumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/seqinfileenumerator.hpp"
/*We store the transactions of the customers of a bank in a sequential input file. A transaction
contains the account number of the customer, the date of the transaction, and the amount of the
transaction (integer, positive: deposit, negative: withdraw). The transactions are sorted by the
account number of the customer. Write the account numbers and balances of customers who have
less than -1000 Euros into a sequential output file.*/
using namespace std;


struct Transaction{
    string accountNo;
    string date;
    int amount;
    friend istream &operator>>(istream &is,Transaction &tr)
    {
        is >> tr.accountNo >> tr.date >> tr.amount;
        return is;
    }
};

struct Accounts{
    string account;
    int balance;
    Accounts () : account(""), balance(0) {}
    Accounts(string acc,int bal) : account(acc),balance(bal) { }
};

class sumAmount : public Summation<Transaction,Accounts>
{
private:
    string _acc;
public:
    sumAmount(const string acc) : _acc(acc) {}
protected:

    Accounts func(const Transaction& e) const override { return Accounts(e.accountNo,e.amount);}
    Accounts neutral() const override { return Accounts();}
    Accounts add( const Accounts& a, const Accounts& b) const override
    {
        return Accounts(b.account,a.balance+b.balance);
    }
    bool whileCond(const Transaction &e) const override { return e.accountNo == _acc;}
    void first() override { }
};

class TransactionEnor : public Enumerator<Accounts>
{
private:
    SeqInFileEnumerator<Transaction>* _f;
    Accounts _account;
    bool _end;
    bool _empty;
public:
    TransactionEnor(const string &fname) : _empty(true) { _f = new SeqInFileEnumerator<Transaction>(fname);}
    void first() override { _f->first(); next(); if (!end()) _empty = false;}
    void next() override;
    bool end() const override { return _end;}
    Accounts current() const override { return _account;}
    ~TransactionEnor() { delete _f;}
    bool isEmpty() const { return _empty;}
};

void TransactionEnor::next()
{
    if (_end = _f->end()) return;
    _account.account = _f->current().accountNo;
    sumAmount pr(_account.account);
    pr.addEnumerator(_f);
    pr.run();
    _account.balance = pr.result().balance;
}

class printToConsole : public Summation<Accounts,ostream>
{
public:
    printToConsole(ostream* o) : Summation<Accounts,ostream >::Summation(o) { }
protected:
    string func(const Accounts& e) const override
    {
        ostringstream oss;
        oss << "(" << e.account <<"," << e.balance<<")\n";
        return oss.str();
    }
    bool cond(const Accounts& e) const override { return e.balance < -1000;}
};
int main(int argc,char** argv)
{
    try{
        string filename;
        ofstream f("output.txt");
        printToConsole pr(&f);
        if (argc > 1) filename = argv[1];
        else filename = "input.txt";
        TransactionEnor enor(filename);
        pr.addEnumerator(&enor);
        pr.run();
        if (enor.isEmpty())
        {
            cout <<"There is no Transaction in the file!\n";
        }
    }catch(SeqInFileEnumerator<Transaction>::Exceptions ex)
    {
        cout <<"File does not exist!\n";
    }
    return 0;
}
