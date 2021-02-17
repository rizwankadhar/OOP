#ifndef TROPHY_H
#define TROPHY_H
#include <string>
/*A hunter (name and age are k
nown) has shot several trophies.
The description of a trophy consists of the species of the animal
(elephant, rhinoceros, or lion), the place and the date of the hunt,
the weight of the shot animal, and a special data: in case of elephant,
 the length of its tusks (in cm, 2 integers), in case of rhinoceros the
 weight of its horn, and for lions, their sex (male or female).
*/
///enum Sex{Male,Female};
class Trophy
{
    public:
        Trophy();
        virtual bool isLion() const {return false;}
        virtual bool isElephant() const {return false;}
        virtual bool isRhino() const {return false;}
        virtual bool isMale() const {return false;}


    protected:
        std::string _specie;
        std::string _place;
        std::string _date;
        int _weight;
        Trophy(std::string specie,std::string place, std::string date,int weight) : _specie(specie),_place(place),_date(date),_weight(weight) {}
    private:
};

class Elephant : public Trophy
{
protected:

    int left_tusk;
    int right_tusk;
public:

    Elephant(std::string place, std::string date,int weight,int left,int right ): Trophy("Elephant",place,date,weight) {left_tusk = left; right_tusk = right;}

    bool isElephant() const override {return true;}
};

class Lion : public Trophy
{
protected:
    std::string _sex;
public:

    Lion(std::string place, std::string date,int weight, std::string sex): Trophy("Elephant",place,date,weight) {_sex = sex;}

    bool isLion() const override {return true;}

    bool isMale() const override { return _sex == "Male";}
};


class Rhinoceros : public Trophy
{
protected:
    int horn_weight;
public:
    Rhinoceros(std::string place, std::string date,int weight,int horn): Trophy("Rhinoceros",place,date,weight) {horn_weight = horn;}
    bool isRhino() const override {return true;}
};
#endif // TROPHY_H
