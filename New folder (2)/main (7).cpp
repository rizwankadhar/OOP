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

void create(const string &str, vector<Landlord> &landlords)
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
    int n, humidity;
    f >> n;
    f.ignore();
    for (int i=0; i<n; ++i)
    {
        Landlord l;
        string line;
        landlords.push_back(l);
        getline(f,line,'\n');
        stringstream ss(line);
        string Mr; char ch;
        ss >> Mr >> landlords[i].name >> ch;
        switch(ch){
            case 'P' : landlords[i].ground = new Plain(n); break;
            case 'G' : landlords[i].ground = new Grassland(n); break;
            case 'L' : landlords[i].ground = new Lakes(n); break;
        }
        ss >> landlords[i].water_amount;
        landlords[i].ground->set_water(landlords[i].water_amount);
        if(landlords[i].ground->get_water()<0)
        {
            cout << "Amount of stored water cannot be negative!" << endl;
            exit(1);
        }
    }
    f >> humidity;

    Weather simul(humidity);
    Weather* weather_given = simul.w;

    for (unsigned int i=1; i<=10; ++i)
    {
        cout << endl;
        cout << endl;
        cout << "Simulation:" << i <<endl;;
        cout << endl;
        cout << endl;

        for (unsigned int j=0; j<landlords.size();++j)
        {
            landlords[j].ground->change(weather_given);
            if(landlords[j].ground->get_water()>=0)
            {
                landlords[j].ground = landlords[j].ground->transform_ground();
                cout << "Mr " << landlords[j].name << " ";
                cout << landlords[j].ground->get_name() << " ";
                cout << landlords[j].ground->get_water() << endl;
            }
            else
            {
                cout << "Amount of stored water cannot be negative!" << endl;
                exit(1);
            }
        }
        weather_given->transform_weather();
        weather_given = weather_given->w;
    }
}

int main()
{
    vector<Landlord> l;
    create("3.txt",l);

    ///Max Search

    int max_val = l[0].ground->get_water();
    string max_landlord = l[0].name;
    for (unsigned int i=1; i<l.size(); ++i)
    {
        if (max_val < l[i].ground->get_water())
        {
            max_val = l[i].ground->get_water();
            max_landlord = l[i].name;
        }
    }
        cout << "\nMost water has Landlord: " << "Mr " << max_landlord << endl;
        cout << "Water amount: " << max_val << endl;

    return 0;
}

