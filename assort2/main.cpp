#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include <string>
using namespace std;
///template < typename Item, typename Value = Item >
class assortment : public Summation<int,ostream>
{
    public:
    assortment(ostream* s):Summation<int,ostream>::Summation(s){
    }
    protected:
         string func(const int& e) const override{
            return (to_string(e)+" ");
         };

      bool  cond(const int& e) const override { return e%2==0 ; }
};
class assortToVector : public Summation<int , vector<int>>
{

public:
    assortToVector(vector<int> &v):Summation<int,vector<int>>::Summation(v){}
protected:
  int func(const int& e) const override{ return e;}
     bool  cond(const int& e) const { return e%2==0 ; }
};
int main()
{
    ///ofstream f("output.txt");

    assortment  pr(&cout);
    cout<<endl;
    SeqInFileEnumerator<int> myenor("input.txt");

    pr.addEnumerator(&myenor);

    pr.run();
    ///f.close();


/*
    vector<int> v;
    assortToVector pr2(v);

    SeqInFileEnumerator<int> myenor2("input.txt");

    pr2.addEnumerator(&myenor2);

    pr2.run();

    v=pr2.result();
cout<<endl;
    for(int i:v){
        cout<< i << ",";
    }
*/
    return 0;
}
