#include "Driver.h"

using namespace std;
int main()
{
    Driver* dr = new Driver();
    dr->van = new Vehicle(5,10,Blue);
    dr->van->tank = new FuelTank(10.0,100.90);

    dr->doWork();
    return 0;
}
