#include "infile.h"
istream &operator>>(istream &is, Prey &p)
{
    is >> p.hunter >>p.specie >> p.weight;
    return is;
}
infile::infile(const string &filename)
{
    _x.open(filename.c_str());
    if (_x.fail()) throw Open_Error;
}
void infile::next()
{
    if (!(_end = (abnorm == _sx)))
    {
        string name  = _dx.hunter;
        _curr = 0;
        for (; norm == _sx && name == _dx.hunter;read())
        {
            _curr++;
        }
    }
}
void infile::read()
{
    _x >> _dx;
    _sx = _x.fail() ? abnorm : norm;
}
