#pragma once

#include <fstream>
#include <iostream>

struct Customer{
    std::string name;
    int Bill;
    friend std::ostream &operator<<(std::ostream &os,const Customer &C);
};
struct Sales{
    std::string cust;
    std::string item;
    int price;
    int cnt;
    int total(){ return price*cnt;}
    friend std::istream &operator>>(std::istream &is,Sales &S);

};
enum Status{norm,abnorm};

class infile
{
    public:

        enum Error {Open_Err};
        infile(const std::string &filename);
        ~infile(){ _x.close();}
        void first() { read(); next();}
        void next();
        Customer current() const { return _curr;}
        bool end() const{ return _end;}

    private:
        std::ifstream _x;
        Sales _dx;
        Status _sx;
        Customer _curr;
        bool _end;

        void read();

};

