#include "Complex.h"

double Complex::get_real() const
{
    return _re;
}
double Complex::get_imag() const
{
    return _im;
}
void Complex::set_real(double n)
{
    _re = n;
}
void Complex::set_imag(double n)
{
    _im = n;
}
ostream &operator<<(ostream &os,const Complex &c)
{
    os << "(" << c._re << "+" << c._im << "i)";
    return os;
}
