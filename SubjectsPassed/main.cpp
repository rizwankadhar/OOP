#include <iostream>
#include "library/counting.hpp"
#include "library/enumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/linsearch.hpp"
#include "library/maxsearch.hpp"
using namespace std;
/*
In a text file, there are results of different courses belonging to several students.
One line consists of the name of the student (one word), the name of the course (one word),
then comment-mark pairs that the student has received during that course. One student may have
results in several lines of the file, but his/her marks are stored consecutively in the file
(it is ordered by student name). Which student has passed the least courses?
 A student passes a course if every mark it at least 2.
*/

struct Grade{
    string comment;
    int mark;
    friend istream &operator>>(istream &is,Grade &g)
    {
        is >> g.comment >> g.mark;
        return is;
    }
};

class CoursePassed : public LinSearch<Grade,true>
{
    bool cond(const Grade& e) const override {return e.mark >=2;}
};

struct Course{
    string student;
    string subject;
    bool passed;
    friend istream &operator>>(istream &is, Course &c);
};
istream &operator>>(istream &is, Course &c)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> c.student >>c.subject;
    CoursePassed pr;
    StringStreamEnumerator<Grade> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    c.passed = pr.found();
    return is;
}

struct Student{
    string name;
    int PassedCourses;
};

class countPassed : public Counting<Course>
{
private:
    string _name;
protected:
    bool cond(const Course &e) const override {return e.passed;}
    bool whileCond(const Course &e) const override { return e.student == _name;}
    void first() override {}
public:
    countPassed(const string &name) : _name(name) {}
};

class StudentEnumerator : public Enumerator<Student>
{
private:
    SeqInFileEnumerator<Course>* _f;
    Student _student;
    bool _end;
    bool _empty;
public:
    StudentEnumerator(const string fname) : _empty(true) {_f = new SeqInFileEnumerator<Course>(fname);}
    void first() override { _f->first(); next(); if (!end()) _empty = false;}
    void next() override;
    bool end() const override { return _end;}
    bool isEmpty() const {return _empty;}
    Student current() const override { return _student;}
    ~StudentEnumerator(){ delete _f;}
};

void StudentEnumerator::next()
{
    if (_end = _f->end()) return;
    _student.name = _f->current().student;
    countPassed pr(_student.name);
    pr.addEnumerator(_f);
    pr.run();
    _student.PassedCourses = pr.result();
}

class LeastPassed : public MaxSearch<Student,int,Less<int>>
{
    int func(const Student &e) const override { return e.PassedCourses;}
};



int main(int argc,char** argv)
{
    try{
        string filename;
        if (argc > 1) filename = argv[1];
        else filename = "empty.txt";
        LeastPassed pr;
        StudentEnumerator enor(filename);
        pr.addEnumerator(&enor);
        pr.run();
        if (pr.found())
        {
            cout <<pr.optElem().name << " has passed least courses that is: " <<pr.opt()<<" courses.\n";
        }
        else
        {
            cout <<"There is no data in the file!\n";
        }
    }catch(SeqInFileEnumerator<Course>::Exceptions e)
    {
        cout<<"Gimme a valid filename!!!\n";
    }
    return 0;
}
