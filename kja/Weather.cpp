#include "Weather.h"

Rainy* Rainy::_instance = nullptr;
Rainy* Rainy::instance()
{
    if(_instance == nullptr) {
        _instance = new Rainy();
    }
    return _instance;
}
void Rainy::destroy()
{
    if ( nullptr!=_instance ) delete _instance;
}

Cloudy* Cloudy::_instance = nullptr;
Cloudy* Cloudy::instance()
{
    if(_instance == nullptr) {
        _instance = new Cloudy();
    }
    return _instance;
}
void Cloudy::destroy()
{
    if ( nullptr!=_instance ) delete _instance;
}
Sunny* Sunny::_instance = nullptr;
Sunny* Sunny::instance()
{
    if(_instance == nullptr) {
        _instance = new Sunny();
    }
    return _instance;
}
void Sunny::destroy()
{
    if ( nullptr!=_instance ) delete _instance;
}
Weather::Weather(int hum)
{
    if(hum<40)
    {
        w = new Sunny();
        w->sethumid(hum);
        w->settype("Sunny");
    }
	else if(hum > 70)
    {
        w = new Rainy();
        w->sethumid(30);
        w->settype("Rainy");
    }
    else
    {
		if((hum-30)*3.3 >= 50)
		{
			w = new Rainy();
			w->sethumid(30);
            w->settype("Rainy");
		}
		else
        {
			w = new Cloudy();
			w->sethumid(hum);
            w->settype("Cloudy");
		}
	}
}

void Weather::transform()
{

    if(humidity<40)
    {
        w = new Sunny();
        w->sethumid(humidity);
        w->settype("Sunny");
    }
    else if(humidity > 70)
    {
        w = new Rainy();
        w->sethumid(30);
        w->settype("Rainy");
    }
    else
    {
        if((humidity-30)*3.3 >= 50)
		{
			w = new Rainy();
			w->sethumid(30);
            w->settype("Rainy");
		}
		else
        {
			w = new Cloudy();
			w->sethumid(humidity);
            w->settype("Cloudy");
		}
    }
}

