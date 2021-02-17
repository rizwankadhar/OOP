#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/selection.hpp"
#include "library/summation.hpp"
/*Sum up the the odd numbers between the first two even numbers in a text file*/

using namespace std;

class FindFstEven : public Selection<int>
{
    bool cond(const int &e) const override { cout <<e<<endl;return e % 2 == 0 || _enor->end();}
};
class SumOdd : public Summation<int>
{
     int func(const int& e) const override { return e;}
     int neutral() const override { return 0;}
     int add(const int& a, const int& b) const override {return a+b;}
     bool whileCond(const int &e) const override { return e % 2 == 1; }
     void first() override {_enor->next(); }
};
int main(int argc, char** argv)
{
    try{
        string filename;
        if (argc > 1) filename = argv[1];
        else filename = "input.txt";

        FindFstEven pr;
        SeqInFileEnumerator<int> enor(filename);
        pr.addEnumerator(&enor);
        pr.run();

        SumOdd pr2;
        pr2.addEnumerator(&enor);
        pr2.run();
        cout <<"The sum of Odd numbers between first two even numbers is :"<<pr2.result()<<".\n";
    }catch(SeqInFileEnumerator<int>::Exceptions e)
    {
        cout <<"This aint a file!!.\n";
    }
    return 0;
}
