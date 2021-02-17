#include "infile.h"


int main()
{
    try {
    cout <<"Enter filename: ";
    string filename;
    cin >> filename;
    infile t(filename);
    double c = 0;
    double sum = 0;
    for (t.first();!t.end();t.next())
    {
        sum += t.current();
        c++;
    }
    if (c != 0 )
    {
        sum /= c;
    }
    cout <<"On average, every hunter has shot "<< sum <<" animal(s).\n";
    }catch (infile::Error er)
    {
        cout <<"File does not exist!\n";
    }
    return 0;
}
