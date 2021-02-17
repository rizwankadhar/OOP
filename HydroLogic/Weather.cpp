#include "Weather.h"
#include "Area.h"

/*Sunny* Sunny::_instance = nullptr;
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
*/
Weather::Weather(int h)
{
    if (h > 70)
    {
        ///this->type = "Rainy";
        ///this->sethumid(30);
        this = new Sunny();
        w->settype("Rainy");
        w->sethumid(h);
    }else if (h < 40)
    {
        this->type = "Sunny";
        this->sethumid(h);
    }
    else if ((h-30)*3.3 >= 100)
    {
        this->type = "Rainy";
        this->sethumid(h);
    }
    else
    {
        this->type = "Cloudy";
        this->sethumid(h);
    }
}
Weather* Sunny::transmute(Plain *p)
{
    p->changeWater(-3);
    return this;
}

Weather* Sunny::transmute(Grassland *p)
{
    p->changeWater(-6);
    return this;
}

Weather* Sunny::transmute(Lake *p)
{
    p->changeWater(-10);
    return this;
}

///CLoudy
/*Cloudy* Cloudy::_instance = nullptr;
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
*/
Weather* Cloudy::transmute(Plain *p)
{
    p->changeWater(-1);
    return this;
}

Weather* Cloudy::transmute(Grassland *p)
{
    p->changeWater(-2);
    return this;
}

Weather* Cloudy::transmute(Lake *p)
{
    p->changeWater(-3);
    return this;
}

///Rainy

/*Rainy* Rainy::_instance = nullptr;
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
*/
Weather* Rainy::transmute(Plain *p)
{
    p->changeWater(20);
    this->changeHumid(5);
    /*if (p->getWater() > 15)
    {
        p = new Grassland("Grassland",p->getWater(),p->getHumid());
    }*/
    return this;
}

Weather* Rainy::transmute(Grassland *p)
{
    p->changeWater(15);
    this->changeHumid(10);
    return this;
}

Weather* Rainy::transmute(Lake *p)
{
    p->changeWater(20);
    this->changeHumid(15);
    return this;
}
/*Weather::Weather(int humid)
{
    if(humid<40)
    {
        w = new Sunny();
        //Sunny(hum);
        w->_humidity = hum; w->_name = "Sunny";
	}
	else if(humid>=40 && humid<=70)
    {
		if((humid-30)*3.3<50)
		{
			w = new Cloudy();
			w->_humidity = hum; w->_name = "Cloudy";
		}
		else
        {
			w = new Rainy();
			w->_humidity = 30; w->_name = "Rainy";
		}
    }
    else if(humid>70)
    {
		w = new Rainy();
        w->_humidity = 30; w->_name = "Rainy";
	}
}

void Weather::changeWeather()
{
     if(humidity<40)
    {
         w = new Sunny();
        //Sunny(hum);
        w->_humidity = hum; w->_name = "Sunny";
        ///w = new Sunny(humidity);
        //Sunny(hum);
        ///w->_humidity = hum; w->_name = "Sunny";
	}
	else if(humidity>=40 && humidity<=70)
    {
		if((humidity-30)*3.3<50)
		{
			w = new Cloudy(humidity);
			///w->_humidity = hum; w->_name = "Cloudy";
		}
		else
        {
			w = new Rainy(humidity);
			///w->_humidity = 30; w->_name = "Rainy";
		}
    }
    else if(humidity>70)
    {
		w = new Rainy(humidity);
		///w->_humidity = 30; w->_name = "Rainy";
	}
}
*/
