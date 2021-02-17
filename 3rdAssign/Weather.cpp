#include "Weather.h"

Weather::Weather(int hum)
{
    if(hum<40)
    {
        w = new Sunny();
        w->sethumid(hum);
        w->settype("Sunny");
	}
    else if (hum > 70)
    {
        w = new Rainy();
        w->sethumid(30);
        w->settype("Rainy");
    }
	else if(hum>=40 && hum<=70)
    {
		if((hum-30)*3.3<50)
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
    else if(humidity>70)
    {
        w = new Rainy();
        w->sethumid(30);
        w->settype("Rainy");
    }
    else
    {
		if((humidity-30)*3.3<50)
		{
			w = new Cloudy();
            w->sethumid(humidity);
            w->settype("Cloudy");
		}
		else
        {
			w = new Rainy();
            w->sethumid(30);
            w->settype("Rainy");
		}
    }

}

