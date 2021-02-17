#include "Infile.h"
#include <stdlib.h>

std::ostream &operator<<(std::ostream &os, const Cactus &c)
{
    os << " Name: "<<c.name<<std::endl;
    os << " Home : "<<c.home<<std::endl;
    os << " Flower Color: " << c.color<<std::endl;
    os << " Average Height : "<<c.height<<std::endl;
    return os;
}
std::istream &operator>>(std::istream &is, Cactus &c)
{
    std::string line;
    getline(is,line,'\n');
    c.name = line;
    getline(is,line,'\n');
    c.home = line;
    getline(is,line,'\n');
    c.color = line;
    getline(is,line,'\n');
    c.height = atoi(line.c_str());
    return is;
}

Infile::Infile(const std::string &filename)
{
    _f.open(filename.c_str());
    if (_f.fail())
    {
        throw OPEN_ERROR;
    }
}

Infile::~Infile()
{
    _f.close();
}
void Infile::next()
{
    if (_f >> _e) _st = norm;///same as _f.fail() _st = abnorm;
    else _st = abnorm;

}
