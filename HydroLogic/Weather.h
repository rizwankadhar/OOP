#pragma once
#include <string>

class Plain;
class Grassland;
class Lake;
class Weather
{
    public:
        Weather() {};
        Weather(int h);
        Weather* w;
         virtual Weather* transmute(Plain *p) = 0;
        virtual Weather* transmute(Grassland *p) = 0;
        virtual Weather* transmute(Lake *p) = 0;
        virtual void transform(Weather *w) = 0;
        int gethumid() const {return humidity;}
        void sethumid(int humid) {humidity = humid;}
        void changeHumid(int h) {humidity += h; }
        void settype(std::string str) {type = str;}
        virtual ~Weather() {}
    protected:
        std::string type;
        int humidity;



    private:
};

class Sunny : public Weather
{
///public:
   /// Sunny() {}
    ///Sunny(int humid) : Weather("Sunny",humid) {}
public:
    ///Sunny(int humid) : Weather(typ,humid) {}
    ///static Sunny* instance();
    Sunny() {}
    Weather* transmute(Plain *p) override;
    Weather* transmute(Grassland *p) override;
    Weather* transmute(Lake *p) override;
    ///void transform(Weather *w) override;
    ///static void destroy() ;
protected:
    ///Sunny(){}
private:
    ///static Sunny* _instance;
};

class Cloudy : public Weather
{
///public:
   /// Cloudy() {}
    ///Cloudy(int humid) : Weather("Cloudy",humid) {}
///static Cloudy* instance();
public:
    Cloudy() {}
    Weather* transmute(Plain *p) override;
    Weather* transmute(Grassland *p) override;
    Weather* transmute(Lake *p) override;
    ///static void destroy() ;
protected:
   /// Cloudy(){}
private:
    ///static Cloudy* _instance;
};

class Rainy : public Weather
{
//public:
  //  Rainy() {}
    ///Rainy(int humid) : Weather("Rainy",humid) {}
///static Rainy* instance();
public:
     Rainy() {}
    Weather* transmute(Plain *p) override;
    Weather* transmute(Grassland *p) override;
    Weather* transmute(Lake *p) override;
   /// static void destroy() ;
protected:
    ///Rainy(){}
private:
    ///static Rainy* _instance;
};

