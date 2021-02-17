#include <iostream>
#include "library/enumerator.hpp"
#include "library/linsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
/*
The results of the participants of a high school sports championship were recorded in a text file.
One line of the file contains the name of the participant (a single word without spaces),
the identifier of the school (a single word without spaces, starts with the zip code),
then the places earned by the participant in the form of sport, place (a single word without space,
natural number) pairs. The data in a line are separated by spaces. The file is sorted by the identifier
of the school. You can assume that the file is correct. An example line of the file:
Peter 1063Szinyei run100 3 swimming500 1 highjump 1

For grade 5: Enumerate the schools from which there were at least 10 contestants who participated
in high jump. Also print the number of total participants from each of these schools.
*/

using namespace std;

struct Sport{
    string type;
    int place;
    friend istream &operator>>(istream &is,Sport &s)
    {
        is >> s.type >> s.place;
        return is;
    }
};
class HighJumpCheck : public LinSearch<Sport>
{
    bool cond(const Sport &e) const override { return e.type == "highjump";}
};

struct Student{
    string name;
    string school;
    bool highJump;
    friend istream &operator>>(istream &is,Student &s);
};
istream &operator>>(istream &is,Student &s)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> s.name >> s.school;
    StringStreamEnumerator<Sport> ssenor(ss);
    HighJumpCheck pr;
    pr.addEnumerator(&ssenor);
    pr.run();
    s.highJump = pr.found();
    return is;
}
struct SchoolResult{
    string name;
    int highJumpers;
    int participants;
    SchoolResult() : name(""), highJumpers(0), participants(0) {}
    SchoolResult(string sch, int hJ,int p) : name(sch), highJumpers(hJ), participants(p) { }
};

class SumResult : public Summation<Student,SchoolResult>
{
private:
    string _name;
public:
    SumResult(const string &name) : _name(name) {}
protected:
    SchoolResult func(const Student& e) const override { return SchoolResult(e.school,e.highJump?1:0,1);}
     SchoolResult neutral() const override { return SchoolResult();}
     SchoolResult add( const SchoolResult& a, const SchoolResult& b) const override { return SchoolResult(b.name,a.highJumpers+b.highJumpers,a.participants + b.participants); }
    bool whileCond(const Student &e) const override { return e.school == _name;}
    void first() override { }
};
/*
struct School{
    string name;
    int highJumpCnt;
    int studentCnt;
};
*/
class SchoolEnumerator : public Enumerator<SchoolResult>
{
private:
    SeqInFileEnumerator<Student>* _f;
    SchoolResult _school;
    bool _end;
    bool _empty;
public:
    SchoolEnumerator(const string &fname) : _empty(true) { _f = new SeqInFileEnumerator<Student>(fname);}
    void first() override { _f->first(); next();  if (!end()) _empty = false;}
    void next() override;
    bool end() const override { return _end;}
    SchoolResult current() const override { return _school;}
    bool isEmpty() const { return _empty;}
    ~SchoolEnumerator() { delete _f;}
};
void SchoolEnumerator::next()
{
    if (_end = _f->end()) return;
    _school.name = _f->current().school;
    SumResult pr(_school.name);
    pr.addEnumerator(_f);
    pr.run();
    _school = pr.result();
    //_school.highJumpCnt = pr.result().highJumpers;
    //_school.studentCnt = pr.result().participants;

}

class WriteOutput : public Summation<SchoolResult,ostream>
{
public:
    WriteOutput(ostream *o) : Summation<SchoolResult,ostream>(o) {}
protected:
    string func(const SchoolResult &e) const override
    {
        ostringstream oss(e.name);
        oss << e.name <<" has more than 10 high jumpers that is :"<<e.highJumpers <<" and their total participants were : "<<e.participants<<".\n";
        return oss.str();
    }
    bool cond(const SchoolResult &e) const override { return e.highJumpers >= 10;}
};
int main(int argc,char** argv)
{
    try{
        string filename;
        if (argc > 1) filename = argv[1];
        else filename = "input.txt";

        WriteOutput pr(&cout);
        SchoolEnumerator enor(filename);
        pr.addEnumerator(&enor);
        pr.run();

        if (enor.isEmpty())
        {
            cout <<"The file is empty!\n";
        }
    }catch(SeqInFileEnumerator<Student>::Exceptions e)
    {
        cout <<"Bruh.....this aint a file!!!!\n";
    }
    return 0;
}
