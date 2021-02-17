#include "PetrolPump.h"

void PetrolPump::refuel(Driver d)
{
    cout <<d.getamnt()<<endl;
}
void Pump::fill(Driver d)
{
    setDisplay(d.getamnt());
}
void Cash_Desk::pay()
{
    double bill;
    bill = station.getprice()*pump.getdisplay();
    setcash(bill);
}
