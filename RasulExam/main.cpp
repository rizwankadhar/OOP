/*
The ACM programming competition is held each year since 1977 on three levels: national, regional,
and global for the best of the best. The students participate in groups of three, and solve 5-8 problems.
They can choose any programming language for each problem. They have to turn in their solutions to check
whether they are correct, and receive an answer shortly.

To produce statistics about the competition, varius data is stored in a text file. One line of the
file contains the year of the competition (an integer), the identifier of the competition
(single word without spaces), then the data about the problems as (programming language, number of correct
problems) pairs. The programming language is a word without spaces. The number of correct problems written
in that programming language is an integer. The file is ordered according to the year of the competition.
The data in a line are separated by spaces. You can assume that the file is correct. An example line of the
file (the data of the 2020 Hungarian ACM national programming competition):

2020 HACM Pascal 42 Java 38 C++ 82 Haskell 76 Python 12

For grade 5: Give a year where for each competition in that year, at most 3 correct solutions
were obtained in Fortran (0 solutions is also possible and satisfies the condition).

*/
#include <iostream>
#include "library/enumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/counting.hpp"
#include "library/linsearch.hpp"
#include "library/maxsearch.hpp"

using namespace std;

struct Problem{
    string name;
    int correct;
    friend istream& operator>>(istream &is, Problem &p){
        is >> p.name >> p.correct;
        return is;
    }
};
/*
struct LineOfProblems{
    bool isThereFortran;
    bool atMost3;
    LineOfProblems() : isThereFortran(true), atMost3(true) { }
    LineOfProblems(bool i, bool a) : isThereFortran(i), atMost3(a) { }
};

class isFortranWith31 : public Summation<Problem>{
    Genre func(const Line &f) const override{return Genre(f.genre,f.indoors);}
    Genre add(const Genre &a,const Genre &b)const override{return Genre(b.name,a.indoors+b.indoors);}
    Genre neutral()const override{return Genre();}
    bool cond(const Problem &p) const override {return (p.name=="Fortran" && p.correct <=3);}
};
*/
class isFortranWith3 : public LinSearch<Problem,true>{
    bool cond(const Problem &p) const override {return (p.name != "Fortran" ) || (p.name=="Fortran" && p.correct <=3);}
};

struct Line{
    string year;
    string competition;
    bool isThere;
    friend istream& operator>>(istream &is, Line &l){
        string ln;
        getline(is,ln);
        stringstream ss(ln);
        ss >> l.year;
        ss >> l.competition;
        StringStreamEnumerator<Problem> enor(ss);
        isFortranWith3 br;
        br.addEnumerator(&enor);
        br.run();
        l.isThere = br.found();
        return is;
    }
};

class Searching : public Summation<Line,bool>{
private:
    string _name;
public:
    Searching(const string &fname) : _name(fname) { }
protected:
    bool whileCond(const Line &l) const override { return l.year == _name ;}
    bool func(const Line &l) const override{return l.isThere;}
    bool add(const bool &a,const bool &b)const override{return a&&b;}
    bool neutral()const override{return true;}
    void first()override {}
};

struct Year{
    string year;
    bool isThere;
};

class CompetitonEnumerator : public Enumerator<Year>{
private:
    SeqInFileEnumerator<Line>* _f;
    Year _year;
    bool _end;
    bool _empty;
public:
    CompetitonEnumerator(const string &fname) : _empty(true) { _f = new SeqInFileEnumerator<Line>(fname);}
    ~CompetitonEnumerator(){delete _f;}
    void first() override {_f->first();  next();  if (!end()) _empty = false; }
    void next() override;
    bool end() const override {return _end;}
    bool isEmpty() const { return _empty;}
    Year current()const override {return _year;}
};

void CompetitonEnumerator::next(){
    if(_f->end()){
        _end = true;
    }
    else{
        _end = false;
        _year.year = _f->current().year;
        Searching pr(_year.year);
        pr.addEnumerator(_f);
        pr.run();
        _year.isThere = pr.result();
    }
}

class Finding : public LinSearch<Year>{
    bool cond(const Year &y)const override {return y.isThere;}
};

/// 2020 HACM Pascal 42 Java 38 C++ 82 Haskell 76 Python 12

int main(int argc,char** argv){
     try{
        string filename;
        if (argc > 1)
            filename = argv[1];
        else
            filename = "test0.txt";

        CompetitonEnumerator enor(filename);
        Finding pr;
        pr.addEnumerator(&enor);
        pr.run();

        if (enor.isEmpty()){
            cout <<"There is no competition in the file!\n";
        }
        else if (pr.found()){
            cout << " " << pr.elem().year <<"\n";
        }
        else{
            cout <<" There is no such year\n";
        }
    }catch(SeqInFileEnumerator<Line>::Exceptions e){
        cout <<"File not found!";
        return 1;
    }
    return 0;
}
