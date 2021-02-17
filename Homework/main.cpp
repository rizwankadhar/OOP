#include <iostream>
#include "Hunter.h"
/*A hunter (name and age are k
nown) has shot several trophies.
The description of a trophy consists of the species of the animal
(elephant, rhinoceros, or lion), the place and the date of the hunt,
the weight of the shot animal, and a special data: in case of elephant,
 the length of its tusks (in cm, 2 integers), in case of rhinoceros the
 weight of its horn, and for lions, their sex (male or female).
 Create a method for the hunter which calculates how many male lions he/she has shot.
*/

using namespace std;

int main()
{

    vector<Trophy*> trophy;
    trophy.push_back(new Elephant("Thar","2019",200,10,11));
    trophy.push_back(new Lion("Thal","2017",130,"Male"));
    trophy.push_back(new Lion("Africa","2012",145,"Female"));
    trophy.push_back(new Elephant("Balochistan","2009",260,7,7));
    trophy.push_back(new Rhinoceros("Kashmir","2005",280,67));
    trophy.push_back(new Rhinoceros("Mangla","2016",198,34));
    trophy.push_back(new Lion("Punjab","2018",130,"Male"));
    Hunter* H1 = new Hunter("Haider",35,trophy);
    int cnt = 0;
    for (Trophy* T: H1->getTrophy())
    {
        if (T->isLion())
            cnt++;
    }
    ///cout <<"Mr."<<H1->getname()<<" has shot "<< cnt<<" Male Lions during his hunting career."<<endl;

    return 0;
}
