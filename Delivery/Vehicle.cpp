#include "Vehicle.h"
bool Vehicle::checkFuel(int distance) const
{
    double need = distance*consumption;
    return need <= tank->getFuel();

}
void Vehicle::refuel()
{
    double deficit = tank->getCapacity()-tank->getFuel();
    tank->addFuel(deficit);
}
void Vehicle::drive(int dist)
{
    startCar();
    std::cout <<"Engine Started\n";
    tank->consumeFuel(dist*consumption);
    stopCar();
    std::cout <<"Engine Stopped\n";
}
void Vehicle::startCar()
{
    if (!(engine->isRunning()))
    {
        engine->start();
    }
}
void Vehicle::stopCar()
{
    if (engine->isRunning())
    {
        engine->stop();
    }
}
