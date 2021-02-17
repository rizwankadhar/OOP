#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <vector>


class Poly
{
    public:
        enum ERROR {NEGATIVE_DEGREE};
        void fill(const float &n) { _vec.push_back(n);}
        int getDegree() const { return degree;}
        void setdegree(const int n);
        float getCoffi( int n ) const;
        float eval(float value) const;
        void getPoly();
        friend Poly operator+(const Poly &q, const Poly &p);
        friend Poly operator*(const Poly &q, const Poly &p);
        friend std::ostream &operator<<(std::ostream &out, const Poly &p);
        ///friend std::ostream &operator>>(std::ostream &in, Poly &p);

    private:
        int degree;
        std::vector<float> _vec;
};

#endif // POLYNOMIAL_H
