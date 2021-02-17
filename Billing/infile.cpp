#include "infile.h"

std::istream &operator>>(std::istream &is,Sales &S)
{
    is >> S.cust >> S.item >> S.price >>S.cnt;
    return is;
}
infile::infile(const std::string &filename)
{
    _x.open(filename.c_str());
    if (_x.fail()) throw Open_Err;
}
void infile::next()
{
    if( !(_end = (abnorm==_sx) )){
        _curr.name = _dx.cust;
        _curr.Bill = 0;
        for (;norm == _sx && _dx.cust == _curr.name ;read() )
        {
            _curr.Bill += _dx.total();
        }
    }
}
void infile::read()
{
    _x >> _dx;
    if (_x.fail()) _sx = abnorm;
    else _sx = norm;
}
