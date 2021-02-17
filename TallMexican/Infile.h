#ifndef INFILE_H
#define INFILE_H

#include <iostream>
#include <fstream>
#include <stdlib.h>

struct Cactus
{
    std::string name;
    std::string home;
    std::string color;
    int height;
    friend std::ostream &operator<<(std::ostream &os, const Cactus &c);
    friend std::istream &operator>>(std::istream &is, Cactus &c);
};
class Infile
{
    public:
        enum Status{norm,abnorm};
        enum Error{OPEN_ERROR};
        Infile(const std::string &filename);
        void first() { next();}
        void next();
        Cactus current() const {return _e; }
        bool end() const {return _st == abnorm;}
        ~Infile();


    private:
        std::ifstream _f;
        Status _st;
        Cactus _e;
};

#endif // INFILE_H
