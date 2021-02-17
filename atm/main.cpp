#include <fstream>
#include <sstream>
#include <iostream>

#include "customer.h"
#include "center.h"

using namespace std;

void createBanks(const string &fileName, Center* &center,vector<Customer> &customers);
int findCustomer(const string &name, const vector<Customer> &customers);


int main()
{
    Center* c = new Center();
    vector<Customer> customers;
    createBanks("input/banks.txt",c,customers);
    ATM* atm = new ATM("valahol", c);
    for (Customer cust : customers)
    {
        try
        {
            Card* card = cust.giveCard();
            cout << cust.getName() << "'s old balance: " << c->getBalance(card->_bankCode,card->_cardNo) << endl;
            cust.withdraw(atm);
            cout << "\tSuccess!\n";
            cout << cust.getName() << "'s new balance: " << c->getBalance(card->_bankCode,card->_cardNo) << endl;
        }
        catch (ATM::Errors ex)
        {
            if (ex==ATM::FEW_MONEY)
            {
                cout << "\tFew money!\n";
            }
            else if (ex==ATM::WRONG_PIN_CODE)
            {
                cout << "\tWrong pin code!\n";
            }
        }
    }

    delete c;
    delete atm;

    return 0;
}

int findCustomer(const string &name, const vector<Customer> &customers)
{
    for (unsigned int i=0;i<customers.size();++i)
    {
        if (customers[i].getName() == name) return i;
    }
    return -1;
}


void createBanks(const string &fileName,Center* &center,vector<Customer> &customers)
{
    ifstream f(fileName.c_str()); /// banks.txt-ben a bankok nevei
    string bankName;
    while(f >> bankName)
    {
        Bank* bank = new Bank(bankName);
        center->registrates(bank);
        ifstream bankStream(("input/"+bankName+".txt").c_str()); ///bankn�v.txt-ben a sz�mlasz�mok �gyf�ln�vvel, egyenleggel �s a hozz�tartoz� k�rty�kkal
        string line;
        getline(bankStream,line,'\n');
        while (!bankStream.fail()) /// sz�ml�k beolvas�sa
        {
            stringstream ss(line);
            string accountNo,owner;
            int balance;
            ss >> owner >> accountNo >> balance; ///�gyf�ln�v, sz�mlasz�m, egyenleg beolvas�sa
            int customerIndex = findCustomer(owner,customers); ///megn�zz�k, van-e m�r ilyen �gyf�l a customers vektorban
            if (customerIndex == -1) /// ha nincs, push_back
            {
                customerIndex = customers.size();
                customers.push_back(Customer(owner));
            }
            Account* acc = bank->createAccount(accountNo,balance); /// l�trehozzuk a sz�ml�t
            string cn,p;
            while(ss >> cn >> p) /// a sz�ml�hoz tartoz� k�rty�k beolvas�sa: k�rtyasz�m �s pin
            {
                Card* card = new Card(bankName,cn,p);
                acc->addCard(card); /// k�rtya hozz�rendel�se a sz�ml�hoz
                customers[customerIndex].takeCard(card); ///k�rtya hozz�rendel�se az �gyf�lhez
            }
            getline(bankStream,line,'\n');
        }
        bankStream.close();
    }
    f.close();
}
