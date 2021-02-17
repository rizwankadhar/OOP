
#include "infile.h"

using namespace std;

int main()
{

    bool error = true;
    do {
            try{
                string filename;
                cout << "Enter File name: ";
                cin>>filename;
                infile t(filename);
                for ( t.first(); !t.end(); t.next())
                {

                    cout <<"Customer name : "<< t.current().name << " Total Bill: " <<t.current().Bill <<endl;
                }
                error = false;
            }catch (infile::Error err)
            {
                cout <<"File does not exist!\n";
            }
    }while (error);
    return 0;
}
