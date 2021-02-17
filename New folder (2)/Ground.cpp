#include "Ground.h"
#include "Weather.h"

void Plain::change(Weather *w)
{
    if(w->get_name() == "Rainy")
    {
        water_amount = water_amount + 20;
        w->set_humidity(w->get_humidity() + 5);
    }
    else if(w->get_name() == "Cloudy") {water_amount = water_amount - 1;}
	else {water_amount = water_amount - 3;}
}

void Lakes::change(Weather *w)
{
    if(w->get_name() == "Rainy")
    {
        water_amount = water_amount + 20;
        w->set_humidity(w->get_humidity() + 15);
    }
    else if(w->get_name() == "Cloudy") {water_amount = water_amount - 3;}
    else {water_amount = water_amount + 10;}
}

void Grassland::change(Weather *w)
{
    if(w->get_name() == "Rainy")
    {
        water_amount = water_amount + 15;
        w->set_humidity(w->get_humidity() + 10);
    }
    else if(w->get_name() == "Cloudy") {water_amount = water_amount - 2;}
    else {water_amount = water_amount - 6;}
}

Ground* Plain::transform_ground()
{
	if(water_amount > 15) {return new Grassland(water_amount);}
	else {return new Plain(water_amount);}
}

Ground* Grassland::transform_ground()
{
    if(water_amount < 16) {return new Plain(water_amount);}
	else if(water_amount > 50) {return new Lakes(water_amount);}
	else {return new Grassland(water_amount);}
}

Ground* Lakes::transform_ground()
{
    if(water_amount < 51) {return new Grassland(water_amount);}
    else {return new Lakes(water_amount);}
}
