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
        virtual void transform();
        string gettype() { return type; }
        int gethumid() { return humidity; }
        void settype(string str) { type = str; }
        void sethumid(int humid) { humidity = humid; }
};

class Rainy : public Weather
{
public:
    static Rainy* instance();
    static void destroy() ;

    Rainy() {}
private:
    static Rainy* _instance;
};

class Sunny : public Weather
{
public:
    static Sunny* instance();
    static void destroy();
    Sunny() {}
private:
    static Sunny* _instance;
};

class Cloudy : public Weather
{
public:
    static Cloudy* instance();
    static void destroy() ;

    Cloudy() {}
private:
    static Cloudy* _instance;
};





