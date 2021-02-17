#ifndef HUNTER_H
#define HUNTER_H

#include "Trophy.h"
#include <vector>
class Hunter
{
    public:
        Hunter();
        Hunter(std::string name,int age, std::vector<Trophy*> trophy) : _name(name),_age(age),_trophies(trophy) {}
        std::string getname() const {return _name;}
        std::vector<Trophy*> getTrophy() const {return _trophies;}

    private:
        std::string _name;
        int _age;
        std::vector<Trophy*> _trophies;

};

#endif // HUNTER_H
