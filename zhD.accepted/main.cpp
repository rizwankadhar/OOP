#include <iostream>
#include "library/seqinfileenumerator.hpp"
#include "library/summation.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/linsearch.hpp"
/*The results of the participants of a high school sports championship were recorded in a text file.
One line of the file contains the name of the participant (a single word without spaces),
the identifier of the school (a single word without spaces, starts with the zip code),
then the places earned by the participant in the form of sport, place (a single word without space, natural number)
pairs. The data in a line are separated by spaces. The file is sorted by the identifier of the school.
You can assume that the file is correct. An example line of the file:
Peter 1063Szinyei run100 3 swimming500 1 highjump 1

For grade 3: Find a contestant who participated in high jump, and whose best place is a silver medal.
Also print the school the contestant is from, and the number of silver medals they've earned.
*/
using namespace std;

struct Contest
{
    string name;
    int rank;
    friend istream &operator>>(istream &is, Contest &c)
    {
        is >> c.name >> c.rank;
        return is;
    }
};

struct sumResult
{
    int bestRank;
    bool highJump;
    int noOfSilver;
    sumResult() {}
    sumResult(int bR,bool hJ, int nOS) : bestRank(bR), highJump(hJ), noOfSilver(nOS) {}
};

class readContestant : public Summation<Contest,sumResult>
{
    sumResult func(const Contest& e) const override { return sumResult(e.rank,e.name=="highjump",(e.rank==2)?1:0); }
    sumResult neutral() const override { return sumResult(999,false,0); }
    sumResult add( const sumResult& a, const sumResult& b) const override {return sumResult((a.bestRank<b.bestRank)?a.bestRank:b.bestRank,a.highJump||b.highJump,a.noOfSilver+b.noOfSilver);}
};

struct Contestant
{
    string name;
    string school;
    int bestRank;
    bool highJump;
    int noOfSilver;
    friend istream &operator>>(istream &is, Contestant &c)
    {
        string line;
        getline (is,line,'\n');
        stringstream ss(line);
        ss>>c.name>>c.school;
        StringStreamEnumerator<Contest> ssenor(ss);
        readContestant pr;
        pr.addEnumerator(&ssenor);
        pr.run();
        c.bestRank=pr.result().bestRank;
        c.highJump=pr.result().highJump;
        c.noOfSilver=pr.result().noOfSilver;
        return is;
    }
};

class MySearch : public LinSearch<Contestant,false>
{
    bool cond(const Contestant& e) const override { return e.highJump && e.bestRank == 2;}
};

int main()
{
    try
    {
        cout << "Student in highjump with silver as best:\n\n";
        SeqInFileEnumerator<Contestant> enor("input.txt");
        MySearch pr;
        pr.addEnumerator(&enor);
        pr.run();
        if (pr.found()) cout << pr.elem().name << " from " << pr.elem().school << " with " << pr.elem().noOfSilver << " silvers.\n";
    }
    catch (SeqInFileEnumerator<Contestant>::Exceptions err)
    {
        cerr<<"File not found!\n";
        return 1;
    }
    return 0;
}
