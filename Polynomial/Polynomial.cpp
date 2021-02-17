#include "Polynomial.h"
#include <iostream>
#include <math.h>

void Poly::setdegree(const int n)
{
        degree = n;
}
float Poly::getCoffi(int n) const
{
    float coff;
   if ( n > degree )
      coff = 0.0;
   else
      coff = _vec.at(degree - n);

    return coff;
}

std::ostream &operator<<(std::ostream &os, const Poly &p)
{
    int i;
    os << p.getCoffi(p.getDegree())<<"x^"<<p.getDegree();
    for (i = p.getDegree()-1;i>0;i--)
    {
        if (p.getCoffi(i)<0.0)
        {
            os << p.getCoffi(i)<<"x^"<<i;
        }
        else
        {
            os <<"+"<< p.getCoffi(i)<<"x^"<<i;
        }
    }
    if (p.getCoffi(i)< 0.0)
        os << p.getCoffi(i)<<"\n";
    else
        os <<"+"<<p.getCoffi(i)<<"\n";
   return os;
}
///std::ostream &operator>>(std::ostream &in, Poly &p)
void Poly::getPoly()
{

    float coffi;
    std::cout<<"Enter degree of the Polynomial : \n";
    std::cin>>degree;
    if (degree < 0) throw Poly::NEGATIVE_DEGREE;

    else {

    for (int i=degree;i>0;i--)
    {
        std::cout<<"Enter coefficient of x^"<<i<<":\n";
        std::cin>>coffi;
        fill(coffi);
    }
    std::cout<<"Enter constant : \n";
    std::cin>>coffi;
    fill(coffi);

    }
}
Poly operator+(const Poly &q, const Poly &p)
{
    Poly r;
    if (p.getDegree()>q.getDegree())
    {
        r.setdegree(p.getDegree());
    }
    else
    {
        r.setdegree(q.getDegree());
    }
    for (int i= r.getDegree();i>=0;i--)
    {

        r.fill(q.getCoffi(i)+p.getCoffi(i));
    }

    return r;
}
Poly operator*(const Poly &q, const Poly &p)
{
    Poly r;
    int a = q.getDegree();
    int b = p.getDegree();
    int arr[a+b+1]={0};
    r.setdegree(a+b);
    for (int i = 0;i<=a;i++)
    {
        for (int j = 0 ;j<=b;j++)
        {
            arr[i+j] += (q.getCoffi(i)*p.getCoffi(j));
        }
    }
    for (int i=a+b;i>=0;i--)
    {
        r.fill(arr[i]);
    }
    return r;
}
float Poly::eval(float value) const
{
   float r = _vec[0];
   for (float i=1;i <= degree;i++)
   {
       r = r*value + _vec[i];
   }
   return r;
}
