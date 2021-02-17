#ifndef GROUND_H
#define GROUND_H
#include "Weather.h"

using namespace std;

class Ground

{
    protected:
		string _name;
        int water_amount;
        Ground (const string &str, int e = 0) : _name(str), water_amount(e) {}
	public:
	    virtual ~Ground() {}
	    //methods
        virtual Ground* transform_ground() = 0;
		virtual void change(Weather* w) = 0;
	    //get
	    virtual string get_name() { return _name; }
		virtual int get_water() { return water_amount; }
	    //set
        virtual void set_name(string n) { _name = n; }
		virtual void set_water(int water) { water_amount = water; }
};

class Plain : public Ground
{
	public:
		Plain(int n) : Ground("Plain",n) {}
		void change(Weather* w) override;
		Ground* transform_ground() override;
};

class Grassland : public Ground
{
	public:
		Grassland(int n) : Ground("Grassland",n) {}
		void change(Weather* w) override;
		Ground* transform_ground() override;
};

class Lakes : public Ground
{
	public:
	    Lakes(int n) : Ground("Lakes",n) {}
		void change(Weather* w) override;
		Ground* transform_ground() override;
};

#endif // GROUND_H
