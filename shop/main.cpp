#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> /** for reading input of varying length*/

using namespace std;

/// Product

struct Product
{
    string name;
    int price;
    friend ostream &operator<<(ostream &os,const Product &p);
    friend istream &operator>>(istream &is,Product &p);
};

ostream &operator<<(ostream &os,const Product &p)
{
    os << p.name << " (" << p.price << " EUR)";
    return os;
}

istream &operator>>(istream &is,Product &p)
{
    is >> p.name >> p.price;
    return is;
}


/// Bill

struct Bill
{
    string customerName;
    vector<Product> products;

    int Total() const;
    friend ostream &operator<<
        (ostream &os,const Bill &b);
    friend istream &operator>>
        (istream &is,Bill &b);
};

int Bill::Total() const
{
    int s = 0;
    for (unsigned int i = 0 ; i < products.size() ; ++i)
    {
        s += products[i].price;
    }
    return s;
}

ostream &operator<<(ostream &os,const Bill &b)
{
    os << "Customer's name: " << b.customerName << endl;
    for (Product p : b.products) ///foreach loop
    {
        os << "\t" << p << endl; /// \t writes a tab
    }
    return os;
}

istream &operator>>(istream &is,Bill &b) /// variable is has to be a stringstream
{
    is>>b.customerName;
    Product p;
    b.products.clear();
    while (is >> p)
    {
        b.products.push_back(p);
    }
    return is;
}

/// methods and important data

enum Status{norm,abnorm};

void open (ifstream &f); /// safe opening

template <typename Item>
void read(Status &st,Item &e, ifstream &f); /// reading operation for any type of data (template)

int calcTotal(ifstream &f); /// result calculation



int main()
{
    ifstream f;
    open(f);
    cout << "\nToday's income: " << calcTotal(f) << " EUR.\n";
    f.close();
    return 0;
}

void open(ifstream &f) /// safe opening
{
    do
    {
        cout << "File's name: ";
        string fname; /// = "input.txt";
        cin >> fname;
        f.open(fname.c_str());
    } while (f.fail());
}

template <typename Item>
void read(Status &st,Item &e,ifstream &f)
{
    string line;
    getline(f,line,'\n'); /// there is only one bill's data in variable line
    if (f.fail() || line == "")
    {
        st = abnorm;
    }
    else
    {
        st = norm;
        stringstream ss(line); /// only one bill
        ss >> e;
        ss.clear();
    }

}

int calcTotal(ifstream &f)
{
    int s = 0;
    Status st;
    Bill e;
    ///t.first
    read<Bill>(st,e,f); ///using template with concrete datatype: Item = Bill

    while (st==norm) ///!t.end
    {
        s += e.Total();/// s = s+...
        read<Bill>(st,e,f); ///next
    }
    return s;
}
