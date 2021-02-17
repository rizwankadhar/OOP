#include <iostream>
#include "gardener.h"

using namespace std;

int main()
{
    Garden* garden = new Garden(5);
    Gardener* gardener = new Gardener(garden);

    gardener->_garden->plant(1, Potatoe::instance(), 3);
    gardener->_garden->plant(2, Pea::instance(), 11);
    gardener->_garden->plant(4, Pea::instance(), 3);
    gardener->_garden->plant(5, Rose::instance(), 4);

    cout << "A betakarithato parcellak azonositoi: ";
    for( int i : gardener->_garden->canHarvest(14)){
        cout << i << " ";
    }
    cout << endl;

    delete garden;
    delete gardener;

    return 0;
}
