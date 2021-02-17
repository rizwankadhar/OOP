#include <iostream>
#include "Complex.h"

using namespace std;
Complex add(Complex a,Complex b);
void sub(Complex a,Complex b,Complex &c);
Complex prod(Complex a,Complex b);
void divide(Complex a,Complex b,Complex &c);
int main()
{
    Complex r;
    Complex c(2,3);
    Complex d(3,4);

    r = add(c,d);
    r.print();
    cout<<endl;
    sub(c,d,r);
    r.print();
    r = prod(c,d);
    r.print();
    divide(c,d,r);
    r.print();
    return 0;
}
Complex add(Complex a,Complex b)
{
    Complex c;
    c.set_real(a.get_real()+b.get_real());
    c.set_imag(a.get_imag()+b.get_imag());
    return c;
}
void sub(Complex a,Complex b,Complex &c)
{
    c.set_real(a.get_real()-b.get_real());
    c.set_imag(a.get_imag()-b.get_imag());
}
Complex prod(Complex a,Complex b)
{
    Complex c;
    double a_r = a.get_real();
    double  a_i = a.get_imag();
    double b_r = b.get_real();
    double b_i = b.get_imag();
    c.set_real(a_r*b_r - a_i*b_i);
    c.set_imag(a_r*b_i + a_i*b_r);
    return c;
}
void divide(Complex a,Complex b,Complex &c)
{
    double a_r = a.get_real();
    double  a_i = a.get_imag();
    double b_r = b.get_real();
    double b_i = b.get_imag();
    c.set_real((a_r*b_r + a_i*b_i)/(b_r*b_r + b_i*b_i)) ;
    c.set_imag((a_i*b_r - a_r*b_i)/(b_r*b_r + b_i*b_i));
    cout<<endl;
    cout<<(a_r*b_r + a_i*b_i)/(b_r*b_r + b_i*b_i)<<endl;

}

