#include <iostream>
#include "library/summation.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/linsearch.hpp"
/*
The results of the participants of a high school sports championship were recorded
in a text file. One line of the file contains the name of the participant
(a single word without spaces), the identifier of the school (a single word
without spaces, starts with the zip code), then the places earned by the participant
in the form of sport, place (a single word without space, natural number) pairs.
The data in a line are separated by spaces. The file is sorted by the identifier of the school.
You can assume that the file is correct. An example line of the file:
Peter 1063Szinyei run100 3 swimming500 1 highjump 1

For grade 3: Find a contestant who participated in high jump, and whose best place is a
silver medal. Also print the school the contestant is from, and the number of silver medals they've earned.
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

struct Student{
    bool HighJump;
    int bestPlace;
    int noOfSilvers;
    Student() : HighJump(false), bestPlace(999), noOfSilvers(0) {}
    Student(bool Hj,int bP,int sil) : HighJump(Hj), bestPlace(bP), noOfSilvers(sil) {}
};

class SumResult : public Summation<Sport,Student>
{
    Student func(const Sport& e) const override { return Student(e.type=="highjump",e.place,e.place == 2?1:0); }
     Student neutral() const override { return Student();}
     Student add( const Student& a, const Student& b) const override { return Student(a.HighJump || b.HighJump, b.bestPlace < a.bestPlace?b.bestPlace:a.bestPlace,a.noOfSilvers + b.noOfSilvers); }
};

struct Line{
    string name;
    string school;
    bool HighJump;
    int bestPlace;
    int silvers;
    friend istream &operator>>(istream &is,Line &l);
};

istream &operator>>(istream &is,Line &l)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> l.name >> l.school;
    StringStreamEnumerator<Sport> ssenor(ss);
    SumResult pr;
    pr.addEnumerator(&ssenor);
    pr.run();
    l.HighJump = pr.result().HighJump;
    l.bestPlace = pr.result().bestPlace;
    l.silvers = pr.result().noOfSilvers;
    return is;
}

class Output : public LinSearch<Line>
{
    bool cond(const Line& e) const override { return e.bestPlace == 2;}
};


int main()
{
    Output pr;
    SeqInFileEnumerator<Line> enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    if (pr.found())
    {
        cout <<pr.elem().name <<" " <<pr.elem().school<<" " <<pr.elem().silvers<<endl;
    }
    return 0;
}
