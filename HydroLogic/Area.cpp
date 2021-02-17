#include "Area.h"
Area::Area(std::string str, std::string own, int e)
{
    if (e < 0) throw Negative_WaterLevel;
    name = str;
    owner = own;
    water = e;
}
void Plain::transform(Area* &a)
{
    if (a->getWater() > 15)
        a->setname("Grassland");
}
void Grassland::transform(Area* &a)
{
    if (a->getWater() > 50)
        a->setname("Lake");
    else if(a->getWater() < 16)
        a->setname("Plain");
}
void Lake::transform(Area* &a)
{
    if (a->getWater() < 51)
        a->setname("Grassland");
}
