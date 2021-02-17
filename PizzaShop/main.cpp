#include <iostream>

#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
/*[2:31 PM] Várkonyi Teréz Anna
    1 order = Custemers's name, name of the pizza, size of the pizza, extra wishes (EC, EM, ES, EP)
Extra wish = 1 EUR
Small pizza costs = 10 EUR
​[2:31 PM] Várkonyi Teréz Anna
    Medium: 15
​[2:31 PM] Várkonyi Teréz Anna
    Large: 20
​[2:31 PM] Várkonyi Teréz Anna
    File ordered by customer's name
​[2:32 PM] Várkonyi Teréz Anna
    Today's order
​[2:32 PM] Várkonyi Teréz Anna
    Calculate: Today's income
​[2:33 PM] Várkonyi Teréz Anna
    Calculate the total income based on the file*/
struct order{
    string vevo_nev;
    string pizza_nev;
    string pizza_size;
    vector<string> extras;
    int bill() const;
    friend ostream &operator<<(ostream &os,const order &ord);
    friend istream &operator>>(istream &is, order &ord);
};
ostream &operator<<(ostream &os,const order &ord)
{
    os << "Customer:" <<ord.vevo_nev << " Pizza: "<<ord.pizza_nev<<" size: "<<ord.pizza_size<<"with extras: ";
    for (string ext : ord.extras)
    {
        os <<ext<< " ";
    }
}
istream &operator>>(istream &is, order &ord)
{
    is>>ord.vevo_nev >> ord.pizza_nev >> ord.pizza_size;
    string ext;
    ord.extras.clear();
    while (is >> ext)
    {
        ord.extras.push_back(ext);
    }
    return is;
}
int order::bill() const
{
    int sum = 0;
    if (pizza_size == "Small") sum += 10;
    else if (pizza_size == "Medium") sum += 15;
    else sum += 20;

    sum += extras.size();
}

enum Status{Norm,AbNorm};
void open(ifstream &f);
template <typename Item>
void read(Status &st, Item &e, ifstream &f);
int income(ifstream &f);
int main()
{
    ifstream f;
    open(f);
    cout << "Today's income is " << income(f) << " Euros\n";
    return 0;
}
void open(ifstream &f)
{
    do{
        string filename;
        cout<<"Enter Filename : ";
        cin>>filename;
        f.open(filename.c_str());
    }while (f.fail());
}
template <typename Item>
void read(Status &st, Item &e, ifstream &f)
{
    string line;
    getline(f,line,'\n');
    if (f.fail() || line == "")
    {
        st = AbNorm;
    }else
    {
        st = Norm;
        stringstream ss(line);
        ss >> e;
        ss.clear();
    }
}
int income(ifstream &f)
{
    int total = 0;
    Status st;
    order e;
    read<order>(st,e,f);

    while (st == Norm)
    {
        total += e.bill();
        read<order>(st,e,f);
    }
    return total;
}
