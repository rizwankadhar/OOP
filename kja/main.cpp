#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <sstream>
#include "Area.h"
#include "Weather.h"

using namespace std;

struct Owner
{
    string name;
    Area* area;
};

void create(const string &str, vector<Owner> &landOwners, int &humidity)
{
    ifstream f(str);
    if(f.fail())
    {
        cout << "Wrong file name!\n";
        exit(1);
    }
    int N;
    f >> N;
    f.ignore();
    for (int i=0; i<N; ++i)
    {
        try{
            Owner l;
            string line;
            getline(f,line,'\n');
            stringstream ss(line);
            string mr;
            char ch;
            int water;
            ss >> mr >> l.name >> ch >> water;
            switch(ch){
                case 'P' : l.area = new Plain(water); break;
                case 'G' : l.area = new Grassland(water); break;
                case 'L' : l.area = new Lake(water); break;
            }

            landOwners.push_back(l);
        }catch(Area::Exceptions e)
        {
            cout << "Amount of water cannot be negative!" << endl;
            exit(1);
        }
    }
    f >> humidity;
}
bool Simulate(vector<Owner> &landlords,int humidity)
{
    Weather simulated(humidity);
    Weather* currentWeather = simulated.w;

    for (int i=0; i<10; i++)
    {
        cout << "\n\nSimulation No:" << i+1 <<endl;

        for (int j=0; j<landlords.size();j++)
        {
            landlords[j].area->transmute(currentWeather);
            if(landlords[j].area->getwater()>=0)
            {
                landlords[j].area = landlords[j].area->transform();
                cout << "Mr " << landlords[j].name << " ";
                cout << landlords[j].area->getname() << " ";
                cout << landlords[j].area->getwater() << endl;
            }
            else
            {
                cout << "Water level has fallen below zero!\n\n" << endl;
                return false;
            }
        }
        currentWeather->transform();
        currentWeather = currentWeather->w;
    }
    return true;
}


void maxLand(vector<Owner> owners,string &LandLord,int &maxWater)
{
    maxWater = owners[0].area->getwater();
    LandLord = owners[0].name;
    for (Owner o: owners)
    {
        if (o.area->getwater() > maxWater)
        {
            maxWater = o.area->getwater();
            LandLord = o.name;
        }
    }
}

#define NORMAL_MODE
#ifdef NORMAL_MODE


int main()
{
    string LandLord;
    int maxWater;
    int humidity;

    vector<Owner> landOwnerz;


    create("input.txt",landOwnerz,humidity);

    if (Simulate(landOwnerz,humidity))
    {
        maxLand(landOwnerz,LandLord,maxWater);
        cout << "\nMr."<< LandLord <<" has the most water after 10 simulations that is :"<<maxWater<<"Km^3."<< endl;
    }
    else
    {
        cout <<"Unfortunately, Simulation process could not be completed!\n";
    }



    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("First LandLord is max", "inp.txt")
{
    string LandLord;
    int maxWater;
    int humidity;

    vector<Owner> landOwnerz;
    create("inp.txt",landOwnerz,humidity);
    if (Simulate(landOwnerz,humidity))
    {
        maxLand(landOwnerz,LandLord,maxWater);
        CHECK(LandLord == "Bean");
        CHECK(maxWater == 286);
    }

}

TEST_CASE("Last Landlord is max","in.txt")
{
    string LandLord;
    int maxWater;
    int humidity;

    vector<Owner> landOwnerz;
    create("in.txt",landOwnerz,humidity);
    Simulate(landOwnerz,humidity);
    maxLand(landOwnerz,LandLord,maxWater);
    CHECK(LandLord == "Tocsi");
    CHECK(maxWater == 279);
}



TEST_CASE("Their is only 1 landlord","in5.txt")
{
    string LandLord;
    int maxWater;
    int humidity;

    vector<Owner> landOwnerz;
    create("in5.txt",landOwnerz,humidity);
    Simulate(landOwnerz,humidity);
    maxLand(landOwnerz,LandLord,maxWater);
    CHECK(LandLord == "Hannan");
    CHECK(maxWater == 32);
}
TEST_CASE("Max landlord is in middle","input.txt")
{
    string LandLord;
    int maxWater;
    int humidity;

    vector<Owner> landOwnerz;
    create("input.txt",landOwnerz,humidity);
    Simulate(landOwnerz,humidity);
    maxLand(landOwnerz,LandLord,maxWater);
    CHECK(LandLord == "Amad");
    CHECK(maxWater == 289);
}

TEST_CASE("Simulate Function working","inp.txt")
{
    string LandLord;
    int maxWater,humidity;
    vector<Owner> landOwnerz;
    create("inp.txt",landOwnerz,humidity);

    CHECK(Simulate(landOwnerz,humidity));
}


TEST_CASE("Water level has fallen below 0 during simulation","in3.txt")
{
    string LandLord;
    int maxWater,humidity;
    vector<Owner> landOwnerz;
    create("in3.txt",landOwnerz,humidity);

    CHECK_FALSE(Simulate(landOwnerz,humidity));
}


TEST_CASE("Exception Handling")
{
    try{
        vector<Owner> landOwnerz;
        landOwnerz.push_back({"Rizwan",new Plain(-5)});
    }catch(Area::Exceptions e)
    {
        CHECK(e == Area::NEGATIVE_WATERLEVEL);
    }
}
TEST_CASE("Testing transform function of Weather by using a Plain"){
    vector<Owner> landOwnerz;
    Weather simulated(78);
    Weather* currentWeather = simulated.w;
    landOwnerz.push_back({"A",new Plain(13)});
    landOwnerz[0].area->transmute(currentWeather);
    currentWeather->transform();
    currentWeather = currentWeather->w;
    CHECK(currentWeather->gettype() == "Sunny");
    CHECK(currentWeather->gethumid() == 35);
}
TEST_CASE("Testing transform function of Weather by using a Grassland"){
    vector<Owner> landOwnerz;
    Weather simulated(78);
    Weather* currentWeather = simulated.w;
    landOwnerz.push_back({"A",new Grassland(45)});
    landOwnerz[0].area->transmute(currentWeather);
    currentWeather->transform();
    currentWeather = currentWeather->w;
    CHECK(currentWeather->gettype() == "Cloudy");
    CHECK(currentWeather->gethumid() == 40);
}
TEST_CASE("Testing transform function of Weather by using a Lake"){
    vector<Owner> landOwnerz;
    Weather simulated(56);
    Weather* currentWeather = simulated.w;
    landOwnerz.push_back({"A",new Lake(68)});
    landOwnerz[0].area->transmute(currentWeather);
    currentWeather->transform();
    currentWeather = currentWeather->w;
    CHECK(currentWeather->gettype() == "Cloudy");
    CHECK(currentWeather->gethumid() == 45);
}
TEST_CASE("Testing transform and transmute functions of both Area and Weather by using a Plain"){
    vector<Owner> landOwnerz;
    Weather simulated(78);
    Weather* currentWeather = simulated.w;
    landOwnerz.push_back({"A",new Plain(12)});
    landOwnerz[0].area->transmute(currentWeather);
    landOwnerz[0].area = landOwnerz[0].area->transform();
    currentWeather->transform();
    currentWeather = currentWeather->w;
    CHECK(landOwnerz[0].area->getname() == "Grassland");
    CHECK(landOwnerz[0].area->getwater() == 32);
    CHECK(currentWeather->gettype() == "Sunny");
    CHECK(currentWeather->gethumid() == 35);
}
TEST_CASE("Testing transform and transmute functions of both Area and Weather by using a Grassland"){
    vector<Owner> landOwnerz;
    Weather simulated(77);
    Weather* currentWeather = simulated.w;
    landOwnerz.push_back({"A",new Grassland(27)});
    landOwnerz[0].area->transmute(currentWeather);
    landOwnerz[0].area = landOwnerz[0].area->transform();
    currentWeather->transform();
    currentWeather = currentWeather->w;
    CHECK(landOwnerz[0].area->getname() == "Grassland");
    CHECK(landOwnerz[0].area->getwater() == 42);
    CHECK(currentWeather->gettype() == "Cloudy");
    CHECK(currentWeather->gethumid() == 40);
}
TEST_CASE("Testing transform and transmute functions of both Area and Weather by using a Lake"){
    vector<Owner> landOwnerz;
    Weather simulated(75);
    Weather* currentWeather = simulated.w;
    landOwnerz.push_back({"A",new Lake(56)});
    landOwnerz[0].area->transmute(currentWeather);
    landOwnerz[0].area = landOwnerz[0].area->transform();
    currentWeather->transform();
    currentWeather = currentWeather->w;
    CHECK(landOwnerz[0].area->getname() == "Lake");
    CHECK(landOwnerz[0].area->getwater() == 76);
    CHECK(currentWeather->gettype() == "Cloudy");
    CHECK(currentWeather->gethumid() == 45);
}


TEST_CASE("Testing Simulate function on Plain")
{
    vector<Owner> landOwnerz;
    landOwnerz.push_back({"Rizwan",new Plain(13)});
    CHECK_FALSE(Simulate(landOwnerz,78));
}
TEST_CASE("Testing Simulate function on Grassland")
{
    vector<Owner> landOwnerz;
    landOwnerz.push_back({"Rizwan",new Grassland(36)});
    Simulate(landOwnerz,78);
    CHECK(landOwnerz[0].area->getwater() == 32);
}
TEST_CASE("Testing simulate function on Grassland  when water level falls below 0")
{
    vector<Owner> landOwnerz;
    landOwnerz.push_back({"Rizwan",new Grassland(8)});
    CHECK_FALSE(Simulate(landOwnerz,34));
}
TEST_CASE("Testing simulate function on Lake")
{
    vector<Owner> landOwnerz;
    landOwnerz.push_back({"Rizwan",new Lake(57)});
    Simulate(landOwnerz,78);
    CHECK(landOwnerz[0].area->getwater() == 50);
}
TEST_CASE("Testing transmute and transform functions on a vector of Owners")
{
    vector<Owner> landOwnerz;
    landOwnerz.push_back({"Rizwan",new Lake(57)});
    landOwnerz.push_back({"Fahad",new Plain(14)});
    landOwnerz.push_back({"Ramzan",new Grassland(43)});
    landOwnerz.push_back({"Jutt",new Grassland(34)});
    landOwnerz.push_back({"Kadhar",new Lake(68)});
    Simulate(landOwnerz,78);
    CHECK(landOwnerz[0].area->getwater()== 257);
    CHECK(landOwnerz[1].area->getwater()== 204);
    CHECK(landOwnerz[2].area->getwater()== 238);
    CHECK(landOwnerz[3].area->getwater()== 224);
    CHECK(landOwnerz[4].area->getwater()== 268);
}





#endif
