#include <iostream>
#include "library/enumerator.hpp"
#include "library/counting.hpp"
#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
/* a file contains results of students. Every line has name of student, name of subject and result of
student in given subject. File is ordered by student names. Find the student who obtained most 5s in total.
Print number of 5s as well.
Example Line of file:
Adam literature 4
*/
using namespace std;

struct Result{
    string student;
    string subject;
    int grade;
    friend istream &operator>>(istream &is, Result &r)
    {
        is >> r.student >> r.subject >> r.grade;
        return is;
    }
};

class FiveCounter : public Counting<Result>
{
private:
    string _name;
public:
    FiveCounter(const string &name) : _name(name) {}
protected:
    bool cond(const Result& e) const override { return e.grade == 5;}
    bool whileCond(const Result &e) const override { return e.student == _name;}
    void first() override { }
};

struct Student{
    string name;
    int Fives;
};

class StudentEnumerator : public Enumerator<Student>
{
private:
    SeqInFileEnumerator<Result>* _f;
    Student _student;
    bool _end;
    bool _empty;
public:
    StudentEnumerator(const string fname): _empty(true) { _f = new SeqInFileEnumerator<Result>(fname);}
    void first() override { _f->first();next(); if (!end()) _empty = false;}
    void next() override;
    bool end() const override {return _end;}
    bool isEmpty() const {return _empty;}
    Student current() const override { return _student;}
};
void StudentEnumerator::next()
{
    if (_end=_f->end()) return;
    _student.name = _f->current().student;
    FiveCounter pr(_student.name);
    pr.addEnumerator(_f);
    pr.run();
   _student.Fives = pr.result();
}

class MaxFives : public MaxSearch<Student,int>
{
    int func(const Student& e) const override { return e.Fives;}
};

int main(int argc,char** argv)
{
    try{
        MaxFives pr;
        string filename;
        if (argc > 1)
            filename = argv[1];
        else
            filename = "input.txt";
        StudentEnumerator enor(filename);
        pr.addEnumerator(&enor);
        pr.run();
        if (pr.found())
            cout << "The student who obtained most 5s is: "<<pr.optElem().name <<" with "<<pr.opt()<<" Fives.\n";
        else if (enor.isEmpty())
            cout <<"There is none!\n";
    }catch(SeqInFileEnumerator<Result>::Exceptions ex)
    {
        cout <<"There is no such file!";
        return 1;
    }
    return 0;
}
