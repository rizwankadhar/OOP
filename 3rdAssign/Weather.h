#pragma once
#include <string>

using namespace std;

class Weather
{
    protected:
        string type;
        int humidity;
    public:
        Weather() {};
        Weather(int hum);
        Weather* w;
        virtual ~Weather() {}
        void transform();
        string gettype() { return type; }
        int gethumid() { return humidity; }
        void settype(string name) { type = name; }
        void sethumid(int humid) { humidity = humid; }
};

class Rainy : public Weather
{
    public:
        Rainy() {}
};

class Sunny : public Weather
{
    public:
        Sunny() {}
};

class Cloudy : public Weather
{
    public:
        Cloudy() {}
};

