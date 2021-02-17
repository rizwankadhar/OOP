#pragma once


class FuelTank
{
    public:
        FuelTank(double petrol,double capac): fuel(petrol), capacity(capac) {}
        double getFuel() const {return fuel;}
        double getCapacity() const {return capacity;}
        void addFuel(double amount) {fuel += amount;}
        void consumeFuel(double amount) {fuel -= amount;}

    private:
        double fuel;
        double capacity;
};
