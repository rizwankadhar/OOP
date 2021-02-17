#ifndef PETROLPUMP_H
#define PETROLPUMP_H
#include <vector>
#include <iostream>

using namespace std;
class Driver;
class Cash_Desk;
class Pump;

class PetrolPump
{
    public:
        PetrolPump();
        ~PetrolPump();
        void refuel(Driver d);
        double getprice() { return unitprice;}

    private:
        double unitprice;

        vector<Pump> pumps;
        vector<Cash_Desk> cash;
};
class Cash_Desk
{
    public:
        Cash_Desk();
        ~Cash_Desk();
        void pay();

        PetrolPump getStation() { return station;}
        Pump getPump() { return pump;}
        void setcash(double bill) { cash = bill;}

    private:
        double cash;
        PetrolPump station;
        Pump pump;
};
class Pump
{
    public:
        Pump();
        ~Pump();
        void fill(Driver d);
        double getdisplay() { return display;}
        void setDisplay(double am) { display = am;}

    private:
        double display;
};

class Driver
{
    public:
        Driver();
        ~Driver();
        void refuel();
        double getamnt() { return amount;}

    private:
        double amount;
};


#endif // PETROLPUMP_H
