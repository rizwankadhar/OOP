#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "Weather.h"
#include "Area.h"

using namespace std;


void create(const string &filename,vector<Area*> &ground, vector<Weather*> &season)
{
    ifstream f(filename);
    if(f.fail()) { cout << "Wrong file name!\n"; exit(1);}

    int n;
    f >> n;
    ground.resize(n);
    int humid;
    try {
    for( int i=0; i<n; ++i ){
        string mr;string name;char ch; int w;
        f >> mr >> name >> ch >> w;
        switch(ch){
            case 'P' : ground[i] = new Plain("Plain", name, w); break;
            case 'G' : ground[i] = new Grassland("Grassland",name, w); break;
            case 'L' : ground[i] = new Lake("Lake",name, w);   break;
        }
    }
    }catch (Area::Exceptions e)
    {
        cout <<"Water level can not be negative!\n";
    }
    f >> humid;
    cout << humid <<endl;
    ///Weather w = new Weather(humid);
    ///w->settype("Rainy");
    //w->sethumid(30);
    for (unsigned int i =0;i<10;i++)
    {
        cout << "Simulation :" <<i+1<<endl;

        for (Area* a : ground)
        {
            a->transmute(w);
            a->transform(a);
            cout << "Mr." <<a->getowner() <<" ";
            cout <<a->getname()<<" ";
            cout <<a->getWater()<<endl;
        }
        cout <<endl;
    }
    ///w->transform(w);

}



int main()
{
    vector<Area*> ground;
    vector<Weather*> season;
    create("in.txt",ground,season);

    return 0;
}
