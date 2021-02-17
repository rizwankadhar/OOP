#include "PrQueue.h"
#include <fstream>
#include <stdlib.h>
using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

void readFromFile(const string &filename, PrQueue &PQ);
void printToConsole(PrQueue &PQ);
int main()
{
    PrQueue PQ;
    readFromFile("input.txt",PQ);
    printToConsole(PQ);
    try
    {
        cout << PQ.remMax();
    }
    catch (PrQueue::ERROR err)
    {
        if (err == PrQueue::EMPTY_PRQUEUE)
        {
            cout<<" Empty PR Queue doesnot have max\n";
        }
    }
    cout << "hello\n";
    return 0;
}
void readFromFile(const string &filename, PrQueue &PQ)
{
    ifstream f(filename.c_str());
    if (f.fail())
    {
        cout << " File does not exist!\n";
        exit(1);
    }
    Item it;
    while (f >> it)
    {
        PQ.add(it);
    }
    f.close();
}
void printToConsole(PrQueue &PQ)
{
    while (!PQ.isEmpty())
    {
        cout << PQ.remMax() << endl;
    }
}
#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("isEmpty")
{
    PrQueue PQ;
    CHECK_THROWS(PQ.remMax());
    CHECK(PQ.isEmpty());
    Item it1("it1",4);
    Item it2("it2",3);
    Item it3("it3",5);
    PQ.add(it1);
    CHECK_FALSE(PQ.isEmpty());
    PQ.add(it2);
    PQ.add(it3);
}
#endif
