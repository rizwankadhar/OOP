#include "Outfile.h"

Outfile::Outfile(const std::string &filename)
{
    _f.open(filename.c_str());
    if (_f.fail())
    {
        throw OPEN_ERROR;
    }
}
void write(Cactus &c)
{

}
Outfile::~Outfile()
{
    _f.close();
}
