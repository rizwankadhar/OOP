#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream f;
    f.open("inp.txt");
    if (f.fail())
    {
        cout<<"fail";
    }
    else
    {
        cout<<"pass:";
    }

    return 0;
}
