#include "Weather.h"

Weather::Weather(int hum)
{
    if(hum<40)
    {
        w = new Sunny();
        //Sunny(hum);
        w->_humidity = hum; w->_name = "Sunny";
	}
	else if(hum>=40 && hum<=70)
    {
		if((hum-30)*3.3<50)
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
    else if(hum>70)
    {
		w = new Rainy();
		w->_humidity = 30; w->_name = "Rainy";
	}
}

void Weather::transform_weather()
{
    if(_humidity<40)
    {
        w = new Sunny();
        w->_humidity = _humidity; w->_name = "Sunny";
    }
    else if(_humidity>=40 && _humidity<=70)
    {
		if((_humidity-30)*3.3<50)
		{
			w = new Cloudy();
			w->_humidity = _humidity; w->_name = "Cloudy";
		}
		else
        {
			w = new Rainy();
			w->_humidity = 30; w->_name = "Rainy";
		}
    }
    else if(_humidity>70)
    {
        w = new Rainy();
        w->_humidity = 30; w->_name = "Rainy";
    }
}

