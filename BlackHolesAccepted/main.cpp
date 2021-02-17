#include <iostream>
#include "library/enumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
/*
Data of blackholes are stored in a text file. Each line of the file starts with
the ID of a blackhole (string without whitespace), which is followed by measurements. A
measurement consists of a date (YYYY.MM.DD format, string), the weight (in billion tonns, int) and
the distance from the Earth (in thousand light year, int). In one line, data is separated by tabs or
whitespace. We can assume that data of one blackhole can be found in only one line of the file. The
dates in one line are in ascending order. The weight of one blackhole increases by time.
SH231 1986.10.17 6000 3000 2003.04.17 8500 2500 2008.11.03 9800 2800
Give a blackhole (ID) the last weight of which is the highest from those which were measured
anytime to be closer than 2700 thousand light years from the Earth.
*/
using namespace std;

struct Measurement{
    string date;
    int weight;
    int distance;
    friend istream &operator>>(istream &is,Measurement &m)
    {
        is >>m.date >> m.weight >> m.distance;
        return is;
    }
};

struct oneLine{
    bool closer;
    int weight;
    oneLine() : closer(false),weight(0) { }
    oneLine(bool cl,int w) : closer(cl),weight(w) { }
};
class sumALine : public Summation<Measurement,oneLine>
{
    oneLine func(const Measurement& e) const override { return oneLine(e.distance < 2700,e.weight);}
    oneLine neutral() const override { return oneLine();}
    oneLine add( const oneLine& a, const oneLine& b) const override { return oneLine(a.closer || b.closer,b.weight);}
};

struct BlackHole{
    string ID;
    bool isClose;
    int lastWeight;
    friend istream &operator>>(istream &is,BlackHole &bh);
};
istream &operator>>(istream &is,BlackHole &bh)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> bh.ID;
    StringStreamEnumerator<Measurement> ssenor(ss);
    sumALine pr;
    pr.addEnumerator(&ssenor);
    pr.run();
    bh.isClose = pr.result().closer;
    bh.lastWeight = pr.result().weight;
    return is;
}


class MaxWeight : public MaxSearch<BlackHole,int>
{
    int func(const BlackHole &e) const override { return e.lastWeight;}
    bool cond(const BlackHole &e) const override { return e.isClose;}
};

int main(int argc,char** argv)
{
    try{
        string filename;
        if (argc > 1) filename = argv[1];
        else filename = "input.txt";


        MaxWeight pr;
        SeqInFileEnumerator<BlackHole> enor(filename);
        pr.addEnumerator(&enor);
        pr.run();

        if (pr.found())
        {
            cout <<pr.optElem().ID<<" has maximum weight from those which were measured anytime to be closer than 2700 thousand light years from the Earth and its weight is: "<< pr.opt() <<" billion tons.\n";
        }
        else
        {
            cout <<"No BlackHole was closer to earth.\n";
        }
    }catch(SeqInFileEnumerator<BlackHole>::Exceptions e)
    {
        cout <<"File not found!\n";
    }
    return 0;
}
