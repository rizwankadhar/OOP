#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "library/enumerator.hpp"
#include "library/seqinfileenumerator.hpp"
#include "library/stringstreamenumerator.hpp"
#include "library/summation.hpp"
#include "library/maxsearch.hpp"
#include "library/counting.hpp"
using namespace std;
struct Data_part
{
    int mins;
    int sec;
    int dis;
    int score;

    friend istream & operator >> (istream &is, Data_part &part)
        {
            is>> part.mins>> part.sec>>part.dis>>part.score;
            return is;
        }// reading operator
};

struct Player// for each line
{
    string name;
    int total;
        Player(string nm,int ttotal)
        {
            name = nm;
            total = ttotal;

        }// constructor
        Player() { name = ""; total = 0;}// default constructor
};

class getPlayer : public Counting<Data_part>
{
    public:
        ///Player func (const Data_part& e) const override{return }
        ///Player neutral() const override {return Player(0);}// neutral element(inital element)
        bool cond(const Data_part& e) {return (e.score > 0);}
        /*Player add(const Player p1, const Player p2) const override
        {
            return Player(p1.total+p2.total);
        }*/

};// for getting the total number of success shot

class Line// how to read from the line
{
public:
    string name1;
    string name2;
    string city;
    int total_success;
    friend istream & operator >> (istream &is , Line &line )// we need to define a reading operator for reading the stream
        {
            string str;
            getline(is,str);// put the stream into the string
            stringstream ss(str);// take out the data int the string
            ss >> line.name1 >> line.name2>>line.city;// we need to first read the name and the subject
            getPlayer gs1;
            StringStreamEnumerator<Data_part> enor(ss);
            gs1.addEnumerator(&enor);
            gs1.run();
            line.total_success = gs1.result();

            return is;
            }// if we do not write
};// now we get the number of success shot in each line

// now we do the grouping
struct Player_g
{
    string name1;

    int suc_shot;
};

class getPlayer_g : public Summation<Line,int>
{
private:
    string _name;
    public :getPlayer_g(const string&name):_name(name){};
    protected:
        int func(const Line &e) const override { return e.total_success;}
        int neutral() const override { return 0;}
        int add(const int &a, const int &b) const override { return a+b;}
        bool whileCond(const Line&e) const override {return e.name1 ==_name;}
        void first() override {}
};


class finalPlayerenum : public Enumerator<Player_g>// this is the enumerator that we need to define, to calculate the final gpa of each line because there is not such default thing in the template liberay
{
    private:
        SeqInFileEnumerator<Line> *_f;
        Player_g _finalPlayer;
        bool _end;
    public:
        finalPlayerenum(const string &fname) {_f = new SeqInFileEnumerator<Line>(fname);}

        void first() override {_f->first(),next();}
        void next() override;
        Player_g current() const override {return _finalPlayer;}
        bool end() const override{return _end;}

};



void finalPlayerenum :: next()
{
    if(_f->end())
    {
        _end = true;
    }else
    {
        _end=false;
        _finalPlayer.name1 = _f->current().name2;
        getPlayer_g gs(_finalPlayer.name1);
        gs.addEnumerator(_f);
        gs.run();
        ///_finalPlayer.name=gs.result().name1;
         _finalPlayer.suc_shot= gs.result();


    }

}// calculating the final suc shot


class getAnswer : public MaxSearch<Player_g,int>
{
    public:
        int func(const Player_g &e) const override{return e.suc_shot;}
        ///bool cond (const finalPlayer&e) const override {return true;}
};

int main()
{
     try
    {
        finalPlayerenum enor ("input.txt");
        getAnswer ga;
        ga.addEnumerator(&enor);
        ga.run();
        if(ga.found())
        {
            cout << "The highest shot is " << ga.optElem().name1 <<" "<<ga.optElem().suc_shot<<endl;
        }

    }
    catch(SeqInFileEnumerator<Line>::Exceptions exception)
    {
        cout<< "Can not open file!!"<<endl;
    }

}
