#pragma once
#include "Engine.h"
#include "FuelTank.h"
#include "Product.h"
enum Color{Blue,Yellow};
class Vehicle
{
    public:
        Vehicle();
        ///~Vehicle();
        bool checkFuel(int distance) const;
        void refuel();
        void startCar();
        void stopCar();


    private:
        double consumption;
        int capacity;
        Color color;
};
