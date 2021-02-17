#pragma once
#include <vector>
#include "Engine.h"
#include "FuelTank.h"
#include "Product.h"
enum Color{Blue,Yellow};
class Vehicle
{
    public:
        Vehicle(double consum,int capa, Color clr): consumption(consum), capacity(capa), color(clr) {}
        FuelTank* tank;
        Engine* engine;
        std::vector<Product*> cargo;
        bool checkFuel(int distance) const;
        int getCapacity() const {return capacity;}
        void refuel();
        void drive(int dist);
        void startCar();
        void stopCar();

    private:
        double consumption;
        int capacity;

        Color color;
};
