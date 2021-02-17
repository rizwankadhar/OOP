#include "infile.h"

std::ostream &operator<<(std::ostream &os,const Balance &B)
{
    os << "The account number :"<<B.acc <<" has balance less than -1000 euros that is : "<<B.bal<<" euros.\n";
    return os;

}
std::istream &operator>>(std::istream &is, Customer &C)
{
    is >> C.acc >> C.date >>C.amount;
    return is;

}
infile::infile(const std::string &filename)
{
    x.open(filename.c_str());
    if (x.fail()) throw Open_Error;
}
void infile::next()
{
    if (!(endd = ( sx == abnorm)))
    {
        curr.acc = dx.acc;
        curr.bal = 0;
        for ( ; sx ==norm && curr.acc == dx.acc; read())
        {
            curr.bal += dx.amount;
        }
    }
}
void infile::read()
{
    sx =  (x >> dx) ? norm : abnorm;
}

