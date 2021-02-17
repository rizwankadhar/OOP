#ifndef WEATHER_H
#define WEATHER_H
#include <string>

using namespace std;

class Weather
{
    protected:
        string _name;
        int _humidity;
        //Weather (const string &str, int e = 0) : _name(str), _humidity(e) {}
    public:
        //constructors
        Weather() {};
        Weather(int hum);
        Weather* w;
        virtual ~Weather() {}
        //method
        virtual void transform_weather();
        //get
        virtual string get_name() { return _name; }
        virtual int get_humidity() { return _humidity; }
        //set
        virtual void set_name(string name) { _name = name; }
        virtual void set_humidity(int humidity) { _humidity = humidity; }
};

class Rainy : public Weather
{
    public:
        Rainy() {}
        //Rainy(int h) : Weather("Rainy",h) {};
};

class Sunny : public Weather
{
    public:
        Sunny() {}
        //Sunny(int h) : Weather("Sunny",h) {};
};

class Cloudy : public Weather
{
    public:
        Cloudy() {}
        //Cloudy(int h) : Weather("Cloudy",h) {};
};

#endif // WEATHER_H
