#include <iostream>
#include "library/enumerator.hpp"
#include "library/linsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/summation.hpp"
/*The results of the participants of a high school sports championship were recorded in a text file.
One line of the file contains the name of the participant (a single word without spaces),
the identifier of the school (a single word without spaces, starts with the zip code),
then the places earned by the participant in the form of sport, place (a single word without space,
natural number) pairs. The data in a line are separated by spaces.
The file is sorted by the identifier of the school. You can assume that the file is correct. An example line of the file:
Peter 1063Szinyei run100 3 swimming500 1 highjump 1

For grade 3: Find a contestant who participated in high jump, and whose best place is a silver medal.
Also print the school the contestant is from, and the number of silver medals they've earned
*/


using namespace std;

struct Sport{
    string name;
    int position;
    friend istream &operator>>(istream &is,Sport &s)
    {
        is >> s.name >> s.position;
        return is;
    }
};

/*class HighJumped : public LinSearch<Sport>
{
    bool cond(const Sport &e) const override {return e.name == "highjump";}
};

class isSilverHighest : public MaxSearch<Sport,int,Less>
{
    int func(const Sport& e) const override { return e.position; }
};
*/
struct Result{
    bool tookHighJump;
    int bestPlace;
    int silvers;
    Result() : tookHighJump(false),bestPlace(100),silvers(0) { }
    Result(bool hJ,int bP,int sil) : tookHighJump(hJ),bestPlace(bP),silvers(sil) { }
};

class readContest : public Summation<Sport,Result>
{
    Result func(const Sport& e) const override { return Result(e.name=="highjump",e.position,e.position==2?1:0);}
    Result neutral() const override {return Result();}
    Result add( const Result& a, const Result& b) const override { return Result(a.tookHighJump||b.tookHighJump,a.bestPlace<b.bestPlace?a.bestPlace:b.bestPlace,a.silvers+b.silvers);}
};

struct Contestant{
    string name;
    string school;
    bool highJump;
    int bestRank;
    int silMedals;
    friend istream &operator>>(istream &is,Contestant &c);
};
istream &operator>>(istream &is,Contestant &c)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >>c.name >>c.school;
    readContest pr;
    StringStreamEnumerator<Sport> ssenor(ss);
    pr.addEnumerator(&ssenor);
    pr.run();
    c.highJump = pr.result().tookHighJump;
    c.bestRank = pr.result().bestPlace;
    c.silMedals = pr.result().silvers;
    return is;
}


class SearchContestant : public LinSearch<Contestant>
{
    bool cond(const Contestant& e) const override {return e.highJump && e.bestRank == 2;}
};

/*istream &operator>>(istream &is, Contestant &c)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> c.student >> c.school;
    HighJumped highjumpPr;
    isSilverHighest silverPr;
    StringStreamEnumerator<Sport> ssenor(ss);
    highjumpPr.addEnumerator(&ssenor);
    silverPr.addEnumerator(&ssenor);
    highjumpPr.run();
    silverPr.run();

}*/
int main()
{
    SearchContestant pr;
    SeqInFileEnumerator<Contestant> enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    if (pr.found())
        cout << pr.elem().name << " from " << pr.elem().school << " with " << pr.elem().silMedals << " silvers.\n";
    return 0;
}
