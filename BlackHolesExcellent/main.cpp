#include <iostream>
#include "library/enumerator.hpp"
#include "library/maxsearch.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/counting.hpp"
/*
Excellent level (grade 5): Consider the previous input file with the following modifications: Several
stations can make measurements of the same blackhole; thus, the lines of the file consist of the
followings: blackhole ID, station ID, measurements. Like this, measurements of one blackhole can be
present in more than one line, but measurements of one station of one blackhole can be found in only
one line. The file is ordered by blackhole ID.
Sample input file:

CX896 SOYUZ 1978.09.22 6000 3000 1999.04.17 8500 2500 2003.11.03 9800 2800
CX896 NASA 1984.03.12 6000 3000 2003.11.23 8500 2500
SH231 SOYUZ 1986.10.17 6000 3000 2003.04.17 8500 2500 2008.11.03 9800 2800

List the average weight of those blackholes that were measured to be closer than 2700 thousand
light years by every station (that has made measurements of that blackhole) at least once. Average
weight is calculated from the last measured weights made by the stations.

#include <iostream>
#include "../../library/summation.hpp"
#include "../../library/counting.hpp"
#include "../../library/seqinfileenumerator.hpp"
#include "../../library/stringstreamenumerator.hpp"
#include "../../library/maxsearch.hpp"
#include "../../library/linsearch.hpp"
*/
using namespace std;

struct Measurement{
    string date;
    int weight;
    int distance;
    friend istream &operator>>(istream &is, Measurement &m){
        is >> m.date >> m.weight >> m.distance;
        return is;
    }
};

struct Result{
    bool close;
    int lastweight;
    Result() : close(false), lastweight(0) { }
    Result(bool c, int w) : close(c), lastweight(w) { }
};

class SumResult : public Summation<Measurement,Result>
{
    Result func(const Measurement& e) const override { return Result(e.distance < 2700,e.weight);}
     Result neutral() const override { return Result();}
     Result add( const Result& a, const Result& b) const override { return Result(a.close || b.close,b.lastweight);}
};

struct Line{
    string blackhole;
    bool isClose;
    string station;
    int lastWeight;
    friend istream& operator>>(istream &is, Line &l){
        string str;
        getline(is,str);
        stringstream ss(str);
        ss >> l.blackhole;
        ss >> l.station;
        StringStreamEnumerator<Measurement> enor(ss);
        SumResult br;
        br.addEnumerator(&enor);
        br.run();
        l.lastWeight = br.result().lastweight;
        l.isClose = br.result().close;
        return is;
    }
};

struct BlackHole{
    bool closeAll;
    int weight;
    int count;
    BlackHole() : closeAll(true), weight(0), count(0) {}
    BlackHole(bool cl,int w,int c) : closeAll(cl), weight(w), count(c) {}
};

class LineSum : public Summation<Line,BlackHole>{
private:
    string _name;
public:
    LineSum(const string &name) : _name(name) { }
protected:
    BlackHole func(const Line &l)const override{return BlackHole(l.isClose,l.lastWeight,1);}
    BlackHole add(const BlackHole &a,const BlackHole &b)const override{return BlackHole(a.closeAll && b.closeAll,a.weight+b.weight,a.count+b.count);}
    BlackHole neutral()const override{return BlackHole();}
    bool whileCond(const Line &l)const override{return l.blackhole == _name;}
    void first()override {}
};

struct Hole{
    string name;
    bool isCloseAll;
    double avg;
};

class BlackHoleEnumerator : public Enumerator<Hole>{
private:
    SeqInFileEnumerator<Line>* _f;
    Hole _blackhole;
    bool _end;
public:
    BlackHoleEnumerator(const string &name){_f = new SeqInFileEnumerator<Line>(name);}
    ~BlackHoleEnumerator(){delete _f;}
    bool end()const override{return _end;}
    Hole current()const override {return _blackhole;}
    void first()override{_f->first();next();}
    void next()override;
};

void BlackHoleEnumerator::next(){
    if(_f->end()){
        _end=true;
    }
    else{
        _end = false;
        _blackhole.name = _f->current().blackhole;
        LineSum br(_blackhole.name);
        br.addEnumerator(_f);
        br.run();
        _blackhole.isCloseAll = br.result().closeAll;
        _blackhole.avg = (double)br.result().weight / br.result().count;
    }
}

class Write : public Summation<Hole,ostream>{
public:
    Write(ostream* o) : Summation<Hole,ostream> (o) { }
protected:
    string func(const Hole &e) const override {
        ostringstream oss(e.name);
        oss << e.name << " " << e.avg << endl;
        return oss.str();
    }
    bool cond(const Hole &e) const override { return e.isCloseAll;}
};

int main(){
    try{
        BlackHoleEnumerator enor("input.txt");
        Write w(&cout);
        w.addEnumerator(&enor);
        w.run();
    }catch(SeqInFileEnumerator<Line>::Exceptions exc){
        cout << "no file\n";
    }
    return 0;
}

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

using namespace std;


struct Measurement{
    string date;
    int weight;
    int distance;
    friend istream &operator>>(istream &is,Measurement &m)
    {
        is >> m.date >> m.weight >> m.distance;
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

struct CloseNdAvg{
    bool isClose;
    int last_weight;
    int noOfStations;
    CloseNdAvg() : isClose(true), last_weight(0), noOfStations(0) { }
    CloseNdAvg(bool close,int last,int nS) : isClose(close), last_weight(last), noOfStations(nS) { }
};

class Average : public Summation<Station,CloseNdAvg>
{
private:
    string _id;
public:
    Average(const string &id) : _id(id) {}
protected:
    CloseNdAvg func(const Station& e) const override { return CloseNdAvg(e.isNear,e.lastWeight,1);}
    CloseNdAvg neutral() const override { return CloseNdAvg();}
    CloseNdAvg add( const CloseNdAvg& a, const CloseNdAvg& b) const override
    {
        return CloseNdAvg(a.isClose && b.isClose,a.last_weight+b.last_weight,a.noOfStations + b.noOfStations);
    }
    bool whileCond(const Station &e) const override { return e.ID == _id;}
    void first() override { }
};

struct BlackHole{
    string name;
    bool closerAll;
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
    void first() override { _f->first(); next(); if (!end()) _empty=false;}
    void next() override;
    bool end() const override { return _end;}
    BlackHole current() const override { return _bHole;}
    bool isEmpty() const {return _empty;}
    ~BlackHoleEnor() { delete _f;}
};

void BlackHoleEnor::next()
{
    if (_end = _f->end() ) return;
    _bHole.name = _f->current().ID;
    Average pr(_bHole.name);
    pr.addEnumerator(_f);
    pr.run();
    _bHole.closerAll = pr.result().isClose;
    _bHole.avg_weight = double(pr.result().last_weight)/pr.result().noOfStations;
    /*_bHole.closerAll = pr.result().isClose;
    if (pr.result().noOfStations > 0)
    {
        _bHole.avg_weight = double(pr.result().last_weight)/pr.result().noOfStations;
    }
    else
    {
        _bHole.avg_weight = 0.0;
    }
   // cout <<_bHole.blackH <<" "<<_bHole.closerAll << " " <<_bHole.avg_weight<<endl;
}

class WriteOutPut : public Summation<BlackHole,ostream>
{
public:
    WriteOutPut(ostream *o) : Summation<BlackHole,ostream> (o) {}
protected:
    string func(const BlackHole& e) const override
    {
        ostringstream oss(e.name);
        oss <<e.name <<" " <<e.avg_weight<<"\n";
    }
    bool cond(const BlackHole& e) const override { return e.closerAll; }
};

int main()
{
    WriteOutPut pr(&cout);
    BlackHoleEnor enor("input.txt");
    pr.addEnumerator(&enor);
    pr.run();
    return 0;
}
*/
