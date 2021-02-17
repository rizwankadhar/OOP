#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/linsearch.hpp"
#include "library/summation.hpp"
/*Write a program that decides if there is an even number in a text file
and gives back the sum of the odd numbers. The file can be opened only once and its content cannot be stored.
*/
using namespace std;

struct Result{
    int OddSum;
    bool containsEven;
    Result(): OddSum(0),containsEven(false) {}
    Result(int sum,bool even): OddSum(sum),containsEven(even) { }
};
class CheckNdAdd : public Summation<int,Result>
{
    Result func(const int& e) const override { return Result(e,e%2==0);}
    Result neutral() const override {return Result();}
    Result add( const Result& a, const Result& b) const override
    {
        return Result(b.containsEven?a.OddSum:a.OddSum+b.OddSum,a.containsEven||b.containsEven);
    }
};
int main()
{
    CheckNdAdd pr;
    SeqInFileEnumerator<int> enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    if (pr.result().containsEven)
        cout <<"yes"<<endl;
    cout <<pr.result().OddSum<<endl;
    return 0;
}
