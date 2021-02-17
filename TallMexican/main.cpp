#include <iostream>
#include "Infile.h"
#include "Outfile.h"

using namespace std;

bool Task(const string &filename,Cactus &elem);

int main()
{
    Cactus TallMex;
    if (Task("input.txt",TallMex))
    {
         cout<<"Tallest Mexican is : \n"<<TallMex<<endl;
    }
    else
    {
        cout <<"There is no Mexican Cactus in the file.\n";
    }

    return 0;
}
bool Task(const string &filename, Cactus &elem)
{
    try
    {
        Infile f("input.txt");
        f.first();
        bool l = false;
        int max = f.current().height;
        elem = f.current();
        while (!f.end())
        {
            if (l && f.current().home == "Mexico")
            {
                if (f.current().height>max)
                {
                    max = f.current().height;
                    elem = f.current();
                }
            }
            else if (!l && f.current().home== "Mexico")
            {
                l = true;
                max = f.current().height;
                elem = f.current();
            }
            f.next();
        }
        return l;
    }catch (Infile::Error exp)
    {
        cout << "File does not exist\n";
        exit(1);
    }
}
