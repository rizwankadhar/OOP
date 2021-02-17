#include "department.h"



Department::Department(const std::string &fname)
{
    std::ifstream f(fname);
    int i;
    std::string s;
    while (f >> s >> i) {
        ///Product* p = new Product(s,i);
        _stock.push_back(new Product(s,i));
    }
}

void Department::takeOutFromStock(Product* product)
{
    bool l = false;
    int ind;
    for( unsigned int i = 0; !l && i < _stock.size(); ++i) {
        l = _stock[i] == product;
        ind = i;
    }
    if (l)  _stock.erase(_stock.begin()+ind);
}


