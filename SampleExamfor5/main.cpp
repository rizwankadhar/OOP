#include <iostream>
#include "library/enumerator.hpp"
#include "library/linsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"

/*Enumerate the schools from which there were at least 10 contestants who participated in high
 jump. Also print the number of total participants from each of these schools.
 Peter 1063Szinyei run100 3 swimming500 1 highjump 1*/

using namespace std;

struct Sport{
    string name;
    int rank;
    friend istream &operator>>(istream &is,Sport &s)
    {
        is >>s.name >>s.rank;
        return is;
    }
};

class HighJumped : public LinSearch<Sport>
{
    bool cond(const Sport &e) const override { return e.name == "highjump";}
};

struct Contestant{
    string name;
    string school;
    bool HighJump;
    friend istream &operator>>(istream &is,Contestant &c);
};
istream &operator>>(istream &is,Contestant &c)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> c.name >>c.school;
    HighJumped pr;
    StringStreamEnumerator<Sport> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    c.HighJump = pr.found();
    return is;
}

struct SumResult{
    string schoolName;
    int HighJumpers;///Conditional Summation
    int participants;///Summation
    SumResult() : schoolName (""),HighJumpers(0), participants(0) {}
    SumResult(string school,int hJ,int parti) : schoolName(school),HighJumpers(hJ), participants(parti) {}
};

class sumAll : public Summation<Contestant,SumResult>
{
private:
    string _name;
public:
    sumAll(const string name) : _name(name) {}
protected:
    SumResult func(const Contestant& e) const override { return SumResult(e.school,e.HighJump?1:0,1);}
    SumResult neutral() const override { return SumResult();}
    SumResult add( const SumResult& a, const SumResult& b) const override
    {
        return SumResult(b.schoolName,a.HighJumpers+b.HighJumpers,a.participants+b.participants);
    }
    void first() override { }
    bool whileCond(const Contestant &e) const override { return e.school == _name;}
};

struct School{
    string name;
    int HighJumpCnt;
    int StudentsCnt;
};

class SchoolEnumerator : public Enumerator<School>
{
private:
    SeqInFileEnumerator<Contestant>* _f;
    School _school;
    bool _end;
    bool _empty;
public:
    SchoolEnumerator(const string fname): _empty(true) { _f = new SeqInFileEnumerator<Contestant>(fname);}
    void first() override  { _f->first();next(); if (!end()) _empty = false;}
    void next() override;
    bool end() const override { return _end;}
    School current() const override { return _school;}
    bool isEmpty() const { return _empty;}
    ~SchoolEnumerator() { delete _f;}
};

void SchoolEnumerator::next()
{
    if (_end = _f->end()) return;
    _school.name = _f->current().school;
    sumAll pr(_school.name);
    pr.addEnumerator(_f);
    pr.run();
    _school.HighJumpCnt = pr.result().HighJumpers;
    _school.StudentsCnt = pr.result().participants;
}

class Output : public Summation<School,ostream>
{
public:
    Output(ostream *o) : Summation<School,ostream> (o) {}
protected:
    string func(const School& e) const override
    {
        stringstream ss;
        ss << e.name <<", has "<<e.HighJumpCnt<<" highjumpers and their "<<e.StudentsCnt<<" students participated.\n";
        return ss.str();
    }
    bool cond(const School& e) const override { return e.HighJumpCnt >=10; }
};

int main(int argc,char** argv)
{
    try{
        string filename;
        Output pr(&cout);
        if (argc > 1)
            filename = argv[1];
        else
            filename = "input.txt";

        SchoolEnumerator enor(filename);
        pr.addEnumerator(&enor);
        pr.run();
        if (enor.isEmpty())
        cout <<"There is no such School!\n";
    }catch(SeqInFileEnumerator<Contestant>::Exceptions ex)
    {
        cout <<"File does not exist!\n";
        return 13;
    }
    return 0;

}



















