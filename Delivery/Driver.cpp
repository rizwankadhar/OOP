#include "Driver.h"
#include <iostream>
#include "Product.h"
void Driver::doWork()
{
    int c =0;
    while (c<van->getCapacity())
    {
        van->cargo.push_back(take());
        c++;
    }
    for(Product* p: van->cargo)
    {
        deliver(p);
    }
}
void Driver::deliver(Product* p)
{
    int dist = distance(van,p->getAddress());
    if (!(van->checkFuel(dist)))
    {
         std::cout<<"Fuel Level is low!...Refueling....\n";
        van->refuel();
         std::cout<<"Tank Full!\n";

    }
    std::cout<<"Taking product to destination..\n";
    van->drive(dist);
     std::cout<<"The product has been delivered to the address :"<<p->getAddress()<<"\n\n";
    van->cargo.erase(van->cargo.end()-1);
}
int Driver::distance(Vehicle* van,std::string address)
{

    return 10;
}
