#pragma once
#include <string>

class Product
{
    public:
        Product(std::string name, int price) : _name(name), _price(price) {}
        std::string getName() const { return _name; }
        int getPrice() const { return _price; }
    private:
        std::string _name;
        int _price;
};
