#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include "Ground.h"
#include "Weather.h"

using namespace std;

struct Landlord
{
    int water_amount;
    string name;
    Ground* ground;
};

void create(const string &str, vector<Landlord> &landlords, int &humidity)
{
    ifstream f(str);
    if(f.fail())
    {
        cout << "Wrong file name!\n";
        exit(1);
    }
    else if(f.peek() == ifstream::traits_type::eof())
    {
        cout <<"File is empty!";
        exit(1);
    }
    int N;
    f >> N;
    f.ignore();
    for (int i=0; i<N; ++i)
    {
        try{
            Landlord l;
            string line;
            getline(f,line,'\n');
            stringstream ss(line);
            string mr; char ch;
            ss >> mr >> l.name >> ch>> l.water_amount;
            switch(ch){
                case 'P' : l.ground = new Plain(l.water_amount); break;
                case 'G' : l.ground = new Grassland(l.water_amount); break;
                case 'L' : l.ground = new Lake(l.water_amount); break;
            }

            landlords.push_back(l);
        }catch(Ground::Exceptions e)
        {
            cout << "Amount of stored water cannot be negative!" << endl;
            exit(1);
        }
    }
    f >> humidity;
}
bool Simulate(vector<Landlord> &landlords,int humidity)
{
    Weather simul(humidity);
    Weather* weather_given = simul.w;

    for (int i=0; i<10; ++i)
    {
        cout << "\n\nSimulation No:" << i+1 <<endl;;

        for (int j=0; j<landlords.size();++j)
        {
            landlords[j].ground->transmute(weather_given);
            if(landlords[j].ground->getwater()>=0)
            {
                landlords[j].ground = landlords[j].ground->transform();
                cout << "Mr " << landlords[j].name << " ";
                cout << landlords[j].ground->getname() << " ";
                cout << landlords[j].ground->getwater() << endl;
            }
            else
            {
                cout << "Amount of stored water cannot be negative!" << endl;
                return false;
            }
        }
        weather_given->transform();
        weather_given = weather_given->w;
    }
    return true;
}
void maxLand(vector<Landlord> owners,string &LandLord,int &maxWater)
{
    maxWater = owners[0].ground->getwater();/// ->getwater();
    LandLord = owners[0].name;///->getowner();
    for (Landlord o: owners)
    {
        if (o.ground->getwater() > maxWater)
        {
            maxWater = o.ground->getwater();
            LandLord = o.name;
        }
    }
}

int main()
{
    string LandLord;
    int maxWater;
    int humidity;
    vector<Landlord> landOwnerz;
    create("inp.txt",landOwnerz,humidity);

    if (Simulate(landOwnerz,humidity))
    {
        maxLand(landOwnerz,LandLord,maxWater);
        cout << "\nMr."<< LandLord <<" has the most water after 10 simulations that is :"<<maxWater<<"Km^3."<< endl;
    }
    else
    {
        cout <<"Simulation process was not completed!\n";
    }

    return 0;
}
