#include <iostream>
#include "library/enumerator.hpp"
#include "library/linsearch.hpp"
#include "library/summation.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
/*The results of the participants of a high school sports championship were recorded in a text file.
One line of the file contains the name of the participant (a single word without spaces),
the identifier of the school (a single word without spaces, starts with the zip code),
then the places earned by the participant in the form of sport, place (a single word without space,
natural number) pairs. The data in a line are separated by spaces. The file is sorted by the identifier
of the school. You can assume that the file is correct. An example line of the file:
Peter 1063Szinyei run100 3 swimming500 1 highjump 1

For grade 3: Find a contestant who participated in high jump, and whose best place is a silver medal.
Also print the school the contestant is from, and the number of silver medals they've earned.
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
struct Result{
    bool highJump;
    int best;
    int silvers;
    Result() : highJump(false), best(999), silvers(0) {}
    Result(bool hj,int b,int sil) :  highJump(hj), best(b), silvers(sil) {}
};

class SumResult : public Summation<Sport,Result>
{
    Result func(const Sport& e) const override { return Result(e.type == "highjump",e.place,e.place==2?1:0);}
   Result neutral() const override { return Result();}
   Result add( const Result& a, const Result& b) const override { return Result(a.highJump || b.highJump,b.best < a.best?b.best:a.best,a.silvers + b.silvers);}
};

struct Student{
    string name;
    string school;
    bool highJump;
    bool isSilverBest;
    int noOfSilvers;
    friend istream &operator>>(istream &is,Student &s);
};
istream &operator>>(istream &is,Student &s)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> s.name >> s.school;
    StringStreamEnumerator<Sport> ssenor(ss);
    SumResult pr;
    pr.addEnumerator(&ssenor);
    pr.run();
    s.highJump = pr.result().highJump;
    s.isSilverBest = pr.result().best == 2;
    s.noOfSilvers = pr.result().silvers;
    return is;
}

class WriteOutput : public Summation<Student,ostream>
{
public:
    WriteOutput(ostream *o) : Summation<Student,ostream>(o) {}
protected:
    string func(const Student &e) const override
    {
        ostringstream oss
        (e.name);
        oss << e.name << " from "<<e.school<<" has participated in highjump and earned silver as best place and they have earned "<<e.noOfSilvers <<" silvers.\n";
        return oss.str();
    }
};
int main()
{
    WriteOutput pr(&cout);
    SeqInFileEnumerator<Student> enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    return 0;
}
