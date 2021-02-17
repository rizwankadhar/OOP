#pragma once
#include "store.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

class Customer
{
    public:
        Customer(const std::string &fname);
        void purchase(const Store &store);

    private:
        std::string _name;
        std::vector<std::string> _list;
        std::vector<Product*> _cart;

        bool linsearch(std::string name, Department* r, Product* &product) const;
        bool minsearch(std::string name, Department* r, Product* &product) const;
};
