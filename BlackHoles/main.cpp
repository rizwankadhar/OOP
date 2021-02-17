#include <iostream>
#include "library/enumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/linsearch.hpp"
/*
Data of blackholes are stored in a text file. A
measurement consists of a date (YYYY.MM.DD format, string), the weight (in billion tonns, int) and
the distance from the Earth (in thousand light year, int). In one line, data is separated by tabs or
whitespace. The
dates in one line are in ascending order. The weight of one blackhole increases by time.
Several
stations can make measurements of the same blackhole; thus, the lines of the file consist of the
followings: blackhole ID, station ID, measurements. Like this, measurements of one blackhole can be
present in more than one line, but measurements of one station of one blackhole can be found in only
one line. The file is ordered by blackhole ID
CX896 SOYUZ 1978.09.22 6000 3000 1999.04.17 8500 2500 2003.11.03 9800 2800
CX896 NASA 1984.03.12 6000 3000 2003.11.23 8500 2500
SH231 SOYUZ 1986.10.17 6000 3000 2003.04.17 8500 2500 2008.11.03 9800 2800

List the average weight of those blackholes that were measured to be closer than 2700 thousand
light years by every station (that has made measurements of that blackhole) at least once. Average
weight is calculated from the last measured weights made by the stations.
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
    oneLine() : closer(false), weight(0) { }
    oneLine(bool cl,int w) : closer(cl),weight(w) { }
};
class sumALine : public Summation<Measurement,oneLine>
{
    oneLine func(const Measurement& e) const override { return oneLine(e.distance < 2700,e.weight);}
    oneLine neutral() const override { return oneLine();}
    oneLine add( const oneLine& a, const oneLine& b) const override { return oneLine(a.closer || b.closer,b.weight);}
};

struct Station{
    string ID;
    string station;
    bool isNear;
    int lastWeight;
    friend istream &operator>>(istream &is,Station &s);
};
istream &operator>>(istream &is,Station &s)
{
    string line;
    getline(is,line,'\n');
    stringstream ss(line);
    ss >> s.ID >> s.station;
    StringStreamEnumerator<Measurement> ssenor(ss);
    sumALine pr;
    pr.addEnumerator(&ssenor);
    pr.run();
    s.isNear = pr.result().closer;
    s.lastWeight = pr.result().weight;
    return is;
}
struct Result{
    bool close;
    int weight;
    int stations;
    Result() : close(true), weight(0), stations(0) {}
    Result(bool c,int w,int st) : close(c),weight(w), stations(st) { }
};
class CloserByAll : public Summation<Station,Result>
{
private:
    string _name;
public:
    CloserByAll(const string &str) : _name(str) {}
protected:
    Result func(const Station& e) const override { return Result(e.isNear,e.lastWeight,1);}
    Result neutral() const override { return Result();}
    Result add( const Result& a, const Result& b) const override { return Result(a.close && b.close,a.weight+b.weight,a.stations +1);}
    bool whileCond(const Station &e) const override { return e.ID == _name;}
    void first() override {}
};

struct BlackHole{
    string name;
    bool closeAll;
    double avg_weight;
};

class BlackHoleEnor : public Enumerator<BlackHole>
{
private:
    SeqInFileEnumerator<Station>* _f;
    BlackHole _bHole;
    bool _end;
    bool _empty;
public:
    BlackHoleEnor(const string &fname) : _empty(true) { _f = new SeqInFileEnumerator<Station>(fname);}
    void first() override { _f->first(); next(); if (!end()) _empty = false;}
    void next() override;
    bool end() const override {return _end;}
    bool isEmpty() const {return _empty;}
    BlackHole current() const override { return _bHole;}
   ~BlackHoleEnor() { delete _f;}
};

void BlackHoleEnor::next()
{
    if (_end = _f->end()) return;
    _bHole.name = _f->current().ID;
    CloserByAll pr(_bHole.name);
    pr.addEnumerator(_f);
    pr.run();
    _bHole.closeAll = pr.result().close;
    _bHole.avg_weight = double(pr.result().weight)/pr.result().stations;
}

class WriteOutput : public Summation<BlackHole,ostream>
{
public:
    WriteOutput(ostream *o) : Summation<BlackHole,ostream>(o) {}
protected:
    string func(const BlackHole &e) const override
    {
        ostringstream oss;
        oss << e.name <<" "<< e.avg_weight<<"\n";
        return oss.str();
    }
    bool cond(const BlackHole &e) const override { return e.closeAll;}
};

int main(int argc, char** argv)
{
    try{
        string filename;
        if (argc > 1) filename = argv[1];
        else filename = "input.txt";

        ofstream f("output.txt");
        WriteOutput pr(&f);
        BlackHoleEnor enor(filename);
        pr.addEnumerator(&enor);
        pr.run();
        if (enor.isEmpty())
        {
            cout <<"There is no blackhole in the file!\n";
        }
    }catch(SeqInFileEnumerator<Station>::Exceptions e)
    {
        cout <<"File not found!\n";
    }
    return 0;
}
