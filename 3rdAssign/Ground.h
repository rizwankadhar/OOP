#pragma once
#include "Weather.h"

using namespace std;

class Ground

{
    protected:
		string name;
        int water;
        Ground (const string &str, int e = 0);
	public:
	    ~Ground() {}
	    enum Exceptions{NEGATIVE_WATERLEVEL};
        virtual Ground* transform() = 0;
		virtual void transmute(Weather* w) = 0;
	    string getname() { return name; }
		int getwater() { return water; }
        void setname(string t) { name = t; }
		void setwater(int wat) { water = wat; }
};

class Plain : public Ground
{
	public:
		Plain(int w) : Ground("Plain",w) {}
		void transmute(Weather* w) override;
		Ground* transform() override;
};

class Grassland : public Ground
{
	public:
		Grassland(int w) : Ground("Grassland",w) {}
		void transmute(Weather* w) override;
		Ground* transform() override;
};

class Lake : public Ground
{
	public:
	    Lake(int w) : Ground("Lake",w) {}
		void transmute(Weather* w) override;
		Ground* transform() override;
};


