#pragma once

#include <iostream>
#include <fstream>

struct Balance{
    std::string acc;
    int bal;
    friend std::ostream &operator<<(std::ostream &os,const Balance &B);
};

struct Customer{
    std::string acc;
    std::string date;
    int amount;
    friend std::ostream &operator>>(std::ostream &os, Customer &C);

};
enum Status {norm, abnorm};
class infile
{
    public:
        enum Error {Open_Error};
        infile(const std::string &filename);
        ~infile() {x.close();}
        void first() { read(); next(); }
        void next();

        Balance current() const {return curr;}

        bool end() const { return endd;}

    private:
        std::ifstream x;
        Customer dx;
        Status sx;
        Balance curr;
        bool endd;

        void read();
};
