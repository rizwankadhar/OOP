#pragma once
#include "Weather.h"

using namespace std;

class Area

{
    protected:
		string name;
        int water;
        Area (const string &str, int e = 0);
	public:
	    virtual ~Area() {}
	    enum Exceptions{NEGATIVE_WATERLEVEL};
        virtual Area* transform() = 0;
		virtual void transmute(Weather* w) = 0;
	    string getname() { return name; }
		int getwater() { return water; }
        void setname(string t) { name = t; }
		void setwater(int wat) { water = wat; }
};

class Plain : public Area
{
	public:
		Plain(int w) : Area("Plain",w) {}
		void transmute(Weather* w) override;
		Area* transform() override;
};

class Grassland : public Area
{
	public:
		Grassland(int w) : Area("Grassland",w) {}
		void transmute(Weather* w) override;
		Area* transform() override;
};

class Lake : public Area
{
	public:
	    Lake(int w) : Area("Lake",w) {}
		void transmute(Weather* w) override;
		Area* transform() override;
};


