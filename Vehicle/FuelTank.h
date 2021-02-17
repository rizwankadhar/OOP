#pragma once


class FuelTank
{
    public:
        FuelTank();
        ///~FuelTank();
        double getFuel() const {return fuel;}
        double getCapacity() const {return capacity;}
        void addFuel(double amount);
        void consumeFuel(double amount);

    private:
        double fuel;
        double capacity;
};
