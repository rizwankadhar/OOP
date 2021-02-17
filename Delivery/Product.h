#pragma once
#include <string>
#include <iostream>
class Product
{
    public:
        Product(const std::string adrs) {address = adrs;}
        std::string getAddress() const {return address;}

    private:
        std::string address = "10";

};


