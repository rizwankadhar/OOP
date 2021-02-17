#include <iostream>
#include "library/intervalenumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/selection.hpp"
#include "library/summation.hpp"
#include "library/enumerator.hpp"
/*Sum up the the odd numbers found in a text file, that can be found after the first even file.*/
using namespace std;

class FindEven : public Selection<int>
{
    bool cond(const int &e) const override { return e % 2 == 0 || _enor->end();}
};
class SumOdd : public Summation<int>
{
    int func(const int &e) const override { return e;}
    int neutral() const override {return 0;}
    int add( const int& a, const int& b) const override {return a+b;}
    bool cond(const int& e) const override { return e % 2 == 1;}
    void first() override { }
};

int main(int argc,char** argv)
{
    try{
        string filename;
        if (argc > 1) filename = argv[1];
        else filename = "input.txt";
        FindEven pr;
        SeqInFileEnumerator<int> enor(filename);
        pr.addEnumerator(&enor);
        pr.run();
        ///int sum = 0;
        SumOdd pr2;
        pr2.addEnumerator(&enor);
        pr2.run();
        ///sum = pr2.result();
        cout <<pr2.result()<<endl;

    }catch(SeqInFileEnumerator<int>::Exceptions e)
    {
        cout <<"File does not exist!!!\n";
    }
    return 0;
}
