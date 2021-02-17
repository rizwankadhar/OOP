#include <iostream>
#include "library/linsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/intervalenumerator.hpp"
#include "library/summation.hpp"
/*Which is the first repetitive item of an array?*/
using namespace std;

class addToVector : public Summation<int,vector<int>>
{
    int func(const int& e) const override { return e;}
};

class InnerSearch : public LinSearch<int>
{
private:
    vector<int> _v;
    int _n;
public:
    InnerSearch(const vector<int> v,const int& n) : _v(v), _n(n) {}
protected:
    bool cond(const int &e) const override { return _v[_n] == _v[e];}
};

class OuterSearch : public LinSearch<int>
{
private:
    vector<int> _x;
public:
    OuterSearch(const vector<int> v) : _x(v) {}
protected:
    bool cond(const int &e) const override
    {
        InnerSearch pr(_x,e);
        IntervalEnumerator enor(0,e-1);
        pr.addEnumerator(&enor);
        pr.run();
        return pr.found();
    }
};
int main(int argc, char** argv)
{
    try{
        string filename;
        if (argc > 1) filename = argv[1];
        else filename = "input.txt";
        vector<int> v;
        addToVector pr;
        SeqInFileEnumerator<int> enor(filename);
        pr.addEnumerator(&enor);
        pr.run();
        v = pr.result();

        OuterSearch pr2(v);
        IntervalEnumerator enor1(1,v.size()-1);
        pr2.addEnumerator(&enor1);
        pr2.run();
        if (pr2.found())
        {
            cout <<"The first repetitive item of array is: "<<v[pr2.elem()]<<".\n";
        }
        else
        {
            cout <<"Your file has unique numbers bruh!!\n";
        }


    }catch(SeqInFileEnumerator<int>::Exceptions e)
    {
        cout<<"This aint a file!!!!\n";
    }
    return 0;
}
