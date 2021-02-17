#include <iostream>
#include "library/enumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include "library/stringstreamenumerator.hpp"
/*Who is the best student of a course (student with the best average)?
Name and marks of one student are stored in one line of the input text file
*/
using namespace std;

struct Result{
    int Sum;
    int Cnt;
    Result(): Sum(0), Cnt(0) {}
    Result(int sum,int count): Sum(sum), Cnt(count) {}
};
class Average : public Summation<int,Result>
{
    Result func(const int& e) const override { return Result(e,1);}
    Result neutral() const override { return Result(); }
    Result add( const Result& a, const Result& b) const override {return Result(a.Sum+b.Sum,a.Cnt+1);}
};
struct Student{
    string name;
    double Avg;
    friend istream &operator>>(istream &is,Student &s);
};

istream &operator>>(istream &is,Student &s)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> s.name;
    StringStreamEnumerator<int> ssenor(ss);
    Average pr;
    pr.addEnumerator(&ssenor);
    pr.run();
    if (pr.result().Cnt > 0)
        s.Avg = double(pr.result().Sum)/pr.result().Cnt;
    else
        s.Avg = 0;
    return is;
}

class BestStudent : public MaxSearch<Student,double>
{
    double func(const Student& e) const override { return e.Avg;}
};

int main()
{
    BestStudent pr;
    SeqInFileEnumerator<Student> enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    if (pr.found())
        cout <<"Best Student is :"<<pr.optElem().name <<" whose Average is :"<<pr.opt() <<".\n";
    else
        cout <<"There is no student in file!\n";
    return 0;
}
