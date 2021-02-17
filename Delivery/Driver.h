#pragma once
#include "Vehicle.h"

class Driver
{
    public:
        Product* prod;
        Vehicle* van;
        void doWork();
        Product* take() {return new Product("10");}
        void deliver(Product* p);
        int distance(Vehicle* van,std::string address);


    private:
};
