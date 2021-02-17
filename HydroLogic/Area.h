#pragma once
#include "Weather.h"
class Sunny;
class Cloudy;
class Rainy;

class Area
{
    public:

        /*virtual ~Area();
        ///virtual Area* changeArea() = 0;
        ///virtual void changeWeather(Weather* w) = 0;
            virtual Area* transmute(Sunny *p) = 0;
        virtual Area* transmute(Cloudy *p) = 0;
        virtual Area* transmute(Rainy *p) = 0;
        ///virtual ~Ground() {}*/
        ///Area(std::string str,int w, int h);
        enum Exceptions{Negative_WaterLevel};
        std::string getname() const { return name; }
        int getWater() const {return water;}
        std::string getowner() const { return owner;}
        ///int getHumid() const {return humidity;}
        void setname(std::string str) { name = str;}
        void changeWater(int e) { water += e; }
        ///void changeHumid(int e) { humidity += e; }
        virtual void transmute(Weather* &weather) = 0;
        virtual void transform(Area* &a) = 0;
        virtual ~Area () {}
    protected:

        std::string name;
        std::string owner;
        int water;
        ///int humidity;
        Area(std::string str, std::string own, int e = 0);

    private:
};

class Plain : public Area
{
/*public:
    Plain(int wat) : Area("Plain",wat) {}
    Area* changeArea() override;
    void changeWeather(Weather* w) override;
*/
public:
    Plain(const std::string &str,const std::string own, int e = 0) : Area(str,own,e){}
    ///Plain(int w,int h) : name("Plain"), water(w), humidity(h) {}
    void transform(Area* &a) override;
    /*void transmute(Weather* &weather) override {
        weather = weather->transmute(this);
    }
};*/

class Grassland : public Area
{
/*public:
    Grassland(int wat) : Area("Grassland",wat) {}
    Area* changeArea() override;
    void changeWeather(Weather* w) override;
*/
public:
    Grassland(const std::string &str,std::string own,int e = 0) : Area(str, own, e){}
    void transform(Area* &a) override;
    void transmute(Weather* &weather) override {
        weather = weather->transmute(this);
    }
};

class Lake : public Area
{
/*public:
    Lake(int wat) : Area("Lake",wat) {}
    Area* changeArea() override;
    void changeWeather(Weather* w) override;
*/
public:
    Lake(const std::string &str,const std::string own, int e = 0) : Area(str,own, e){}
    void transform(Area* &a) override;
    void transmute(Weather* &weather) override {
        weather = weather->transmute(this);
    }
};
