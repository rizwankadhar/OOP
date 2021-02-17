#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
using namespace std;

class Complex
{
    public:
        Complex(double r,double i)
        {
            _re = r;
            _im = i;
        }
        Complex ()
        {
            _re = 3.0;
            _im = 2.0;
        }
        double get_real() const;

        double get_imag() const;

        void set_real(double n);

        void set_imag(double n);

        void print() const { cout << "(" << _re << "+" << _im << "i)"; }

        friend ostream &operator<<(ostream &os,const Complex &c);


    private:
        double _re;
        double _im;
};

#endif // COMPLEX_H
