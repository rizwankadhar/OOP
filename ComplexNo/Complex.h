#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>

class Complex
{
    public:
        Complex(){ _real = 0; _imaginary=0; }
        Complex(double real,double imaginary): _real(real), _imaginary(imaginary)
        {
           /// _real = real;
            ///_imaginary = imaginary;
        }
        void print() const { std::cout << "(" << _real << "," << _imaginary<< ")"; }

        ///friend std::ostream &operator<<(std::ostream &os,const Complex &c);

    private:
        double _real;
        double _imaginary;
};

#endif // COMPLEX_H
