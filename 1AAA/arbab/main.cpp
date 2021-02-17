#include <iostream>
#include "../library/stringstreamenumerator.hpp"
#include "../library/seqinfileenumerator.hpp"
#include "../library/enumerator.hpp"
#include "../library/summation.hpp"
#include "../library/counting.hpp"
#include "../library/linsearch.hpp"
#include "../library/maxsearch.hpp"
using namespace std;



struct pillow
{
    string type;
    int number;
    friend istream&operator>>(istream&is,pillow &p){
        is>>p.type>>p.number;
        return is;
    }
};



class sum_pillow:  public Summation<pillow,int>{




   int func(const pillow& e) const override{return e.number;}
    int neutral() const override {return 0;}
    int  add( const int& a, const int& b) const override{return a+b;}
  };




struct store
{
    string email;
    string name;
    int total;
    friend istream&operator>>(istream&is,store &p);
};
istream&operator>>(istream&is,store &p){



    string line;
    getline(is,line,'\n');



    stringstream ss(line);
    ss>>p.email>>p.name;



    StringStreamEnumerator<pillow> lineEnor(ss);
    sum_pillow pr;



    pr.addEnumerator(&lineEnor);



    pr.run();



    p.total = pr.result();



    return is;
}
class highest_per_customer: public MaxSearch<store,int>
{
    int func(const store& e ) const override{ return e.total;}



};
struct Result{
    string name;
    int morethan10;



    Result():name(""),morethan10(0){}
    Result(const string &n,int p):name(n),morethan10(p){}
};
class Sum_All:public Summation <store,Result>
{
public:
    Sum_All(const string& sname ):_name(sname){}
private:
    string _name;
    Result func(const store& e) const override{return Result(e.name,1);}
     Result neutral() const override{return Result();}
     Result add( const Result& a, const Result& b) const override{
        return (Result(b.name,a.morethan10+b.morethan10));
     }
    void first() override{}
    bool whileCond(const store& e){
        return e.name==_name;
    }
};
///ENUMERATE ALL DATA
class DATA_ENUMERATOR : public Enumerator<Result>
{
private:
    SeqInFileEnumerator<store>* _f;
    Result _current;
    bool _end;
    bool _empty;
public:
    DATA_ENUMERATOR(const string& fname):_empty(true)
    {
        _f=new SeqInFileEnumerator<store>(fname);
    }
    ~DATA_ENUMERATOR()
    {
    delete _f;
    }
    void first() override
    {
        _f->first();next(); if (!end()) _empty=false;
    }
    Result current() const override {return _current;}



    bool end() const override{return _end;}
    bool getEmpty()const {return _empty;}
    void next() override{



        if (_end=_f->end()) return;
        _current.name=_f->current().name;



        Sum_All pr(_current.name);
        pr.addEnumerator(_f);



        pr.run();



        _current=pr.result();
    }
};



class PRINT :public Summation<Result,ostream>{
public:
    PRINT(ostream *o):Summation<Result,ostream> (o) { }
    private:
    std::string func(const Result& e) const override
    {
        ostringstream oss(e.name);
        oss<<e.name<<" is store with highest  number n 10 cushion buyer\nNumber of Customer who bought "<<e.morethan10<<endl;



        return oss.str();
    }



      bool  cond(const Result& e) const  override{ return e.morethan10>10  ; }
};




//class highest_pillows:public Summation<store,ostream>
//{
//public:
//    highest_pillows(ostream* s):Summation<store,ostream>::Summation(s){
//    }
//protected:
//    string func(const store& s) const override
//    {
//        stringstream os(s.name);
//        os<<"MAXIMUM PER CUSTOMER\n";
//        os<<s.email<<" : "<<s.store<<" : "<<s.total
//    return os.str();
//    }
//};



int main(int argc,char** argv)
{
try{
    string fname;
    if(argc>1)
        fname=argv[1];
    else
        fname="input2.txt";
  DATA_ENUMERATOR enor(fname);
cout<<"store has the highest number of customers who bought at least 10 cushionss\n";
  PRINT pr(&cout);
  pr.addEnumerator(&enor);
  pr.run();
  if(enor.getEmpty()) cout<<"THERE IS NONE \n";
}
catch(SeqInFileEnumerator<store>::Exceptions ex) {
        cout<<"FILE DOSNT EXIST !"<<endl;
        return 1;



}
    return 0;
}
