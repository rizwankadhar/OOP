#include "Area.h"
#include "Weather.h"

Area::Area(const string &str, int e)
{
    if (e < 0) throw NEGATIVE_WATERLEVEL;
    name = str;
    water = e;
}

void Plain::transmute(Weather *w)
{
    if(w->gettype() == "Rainy")
    {
        water += 20;
        w->sethumid(w->gethumid() + 5);
    }
    else if(w->gettype() == "Cloudy")
    {
        water -= 1;
    }
	else
    {
        water -= 3;
    }
}

void Lake::transmute(Weather *w)
{
    if(w->gettype() == "Rainy")
    {
        water += 20;
        w->sethumid(w->gethumid() + 15);
    }
    else if(w->gettype() == "Cloudy")
    {
        water -= 3;
    }
    else
    {
        water += 10;
    }
}

void Grassland::transmute(Weather *w)
{
    if(w->gettype() == "Rainy")
    {
        water += 15;
        w->sethumid(w->gethumid() + 10);
    }
    else if(w->gettype() == "Cloudy")
    {
        water -= 2;
    }
    else
    {
        water -= 6;
    }
}

Area* Plain::transform()
{
	if(water > 15 && water <= 50)
    {
        return new Grassland(water);
    }
	else if (water <= 15)
    {
        return new Plain(water);
    }
    else if (water > 50)
    {
        return new Lake(water);
    }
}

Area* Grassland::transform()
{
    if(water < 16)
    {
        return new Plain(water);
    }
	else if(water > 50)
    {
        return new Lake(water);
    }
	else
    {
        return new Grassland(water);
    }
}

Area* Lake::transform()
{
    if(water <= 50 && water > 15)
    {
        return new Grassland(water);
    }
    else if (water <= 15)
    {
        return new Plain(water);
    }
    else
    {
        return new Lake(water);
    }
}
