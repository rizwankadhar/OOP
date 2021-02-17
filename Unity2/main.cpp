#include <iostream>
#include "library/linsearch.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/enumerator.hpp"
#include "library/seqinfileenumerator.hpp"
/*
The results of the participants of a high school sports championship were recorded in
a text file. One line of the file contains the name of the participant (a single word
without spaces), the identifier of the school (a single word without spaces, starts with
the zip code), then the places earned by the participant in the form of sport, place
(a single word without space, natural number) pairs. The data in a line are separated by
spaces. The file is sorted by the identifier of the school. You can assume that the file
is correct. An example line of the file:
Peter 1063Szinyei run100 3 swimming500 1 highjump 1

For grade 5: Enumerate the schools from which there were at least 10
contestants who participated in high jump. Also print the number of total participants from each of these schools.
*/
using namespace std;

struct Sport{
    string type;
    int place;
    friend istream &operator>>(istream &is, Sport &s)
    {
        is >> s.type >> s.place;
        return is;
    }
};
class HighJumped : public LinSearch<Sport>
{
    bool cond(const Sport& e) const override { e.type == "highjump";}
};

struct Student{
    string name;
    string school;
    bool highJump;
    friend istream &operator>>(istream &is, Student &s);
};
istream &operator>>(istream &is, Student &s)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> s.name >>s.school;
    StringStreamEnumerator<Sport> ssenor(ss);
    HighJumped pr;
    pr.addEnumerator(&ssenor);
    pr.run();
    s.highJump = pr.found();
    return is;
}

struct Result{
    string school;
    int highJumpers;
    int participants;
    Result() : school(""), highJumpers(0), participants(0) {}
    Result(string sch,int Hj, int part) : school(sch), highJumpers(Hj), participants(part) { }
};

class SumResult : public Summation<Student,Result>
{
private:
    string _name;
public:
    SumResult(const string name) : _name(name) { }
protected:
    Result func(const Student& e) const override { return Result(e.school,e.highJump?1:0,1);}
    Result neutral() const override { return Result();}
    Result add( const Result& a, const Result& b) const override { return Result(b.school,a.highJumpers + b.highJumpers,a.participants + b.participants);}
    bool whileCond(const Student &e) const override { return e.school == _name;}
    void first() override { }
};

class SchoolEnor : public Enumerator<Result>
{
private:
    SeqInFileEnumerator<Student>* _f;
    Result _result;
    bool _end;
public:
    SchoolEnor(const string &fname) { _f = new SeqInFileEnumerator<Student>(fname);}
    void first() override { _f->first();  next();}
    void next() override;
    bool end() const override {return _end;}
    Result current() const override {return _result;}
    ~SchoolEnor() { delete _f;}
};

void SchoolEnor::next()
{
    if (_end = _f->end()) return;
    _result.school = _f->current().school;
    SumResult pr(_result.school);
    pr.addEnumerator(_f);
    pr.run();
    _result = pr.result();
}

class WriteOutput : public Summation<Result,ostream>
{
public:
    WriteOutput(ostream* o) : Summation<Result,ostream> (o) {}
protected:
    string func(const Result& e) const override
    {
        ostringstream oss(e.school);
        oss << e.school<<" " <<e.highJumpers <<" " <<e.participants<<"\n";
        return oss.str();
    }
    bool cond(const Result& e) const override { return e.highJumpers >= 10; }
};


int main()
{
    try{
    WriteOutput pr(&cout);
    SchoolEnor enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    }catch(SeqInFileEnumerator<Student>::Exceptions e)
    {
        cout <<"File not found!\n";
    }
    return 0;
}
