#include <iostream>
#include "library/enumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
/*Who is the best student of a course (student with the best average)? Name and one mark of a
student are stored in one line of the input text file. One student may have several marks
*/
using namespace std;
struct Mark{
    string name;
    int grade;
    friend istream &operator>>(istream &is,Mark &m)
    {
        is >>m.name >> m.grade;
        return is;
    }
};

struct Result{
    int Sum;
    int Cnt;
    Result() {}
    Result(int s,int c) : Sum(s), Cnt(c) {}
};
class SumResult : public Summation<Mark,Result>
{
private:
    string _name;
public:
    SumResult(const string name) : _name(name) { }
protected:
    Result func(const Mark& e) const override { return Result(e.grade,1);}
    Result neutral() const override { return Result(0,0);}
    Result add( const Result& a, const Result& b) const override { return Result(a.Sum+b.Sum,a.Cnt+1);}
    void first() override { }
    bool whileCond(const Mark &e) const override { return e.name == _name;}
};

struct Student{
    string name;
    double Avg;
};

class StudentEnumerator : public Enumerator<Student>
{
private:
    SeqInFileEnumerator<Mark>* _f;
    Student _student;
    bool _end;
    bool _empty;
public:
    StudentEnumerator(const string fname): _empty(true) { _f = new SeqInFileEnumerator<Mark>(fname);}
    void first() override { _f->first(); next(); if (!end()) _empty = false;}
    void next() override;
    bool end() const override { return _end;}
    Student current() const override { return _student;}
    bool isEmpty() const { return _empty;}
    ~StudentEnumerator() { delete _f;}
};
void StudentEnumerator::next()
{
    if (_end = _f->end()) return;
    _student.name = _f->current().name;
    SumResult pr(_student.name);
    pr.addEnumerator(_f);
    pr.run();
    if (pr.result().Cnt > 0)
        _student.Avg = double(pr.result().Sum)/pr.result().Cnt;
    else
        _student.Avg = 0;
}

class BestStudent : public MaxSearch<Student,double>
{
    double func(const Student &e) const override { return e.Avg;}
};



int main(int argc, char** argv)
{
    try{
        string filename;
        BestStudent pr;
        if (argc > 1) filename = argv[1];
        else filename = "input.txt";
        StudentEnumerator enor(filename);
        pr.addEnumerator(&enor);
        pr.run();
        if (pr.found())
             cout <<"Best Student is :"<<pr.optElem().name <<" whose Average is :"<<pr.opt() <<".\n";
        else
            cout <<"There is no student in file!\n";
    }catch(SeqInFileEnumerator<Mark>::Exceptions ex)
    {
        cout <<"File does not exist!";
        return 1;
    }
    return 0;
}
