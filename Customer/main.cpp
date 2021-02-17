#include "infile.h"
using namespace std;

int main()
{
    bool error = true;
    do {
        try {
            string filename;
            cout <<"Enter Filename: ";
            cin>>filename;

            infile t("inp.txt");
            for (t.first();!t.end();t.next())
            {
                if (t.current().bal< -1000)
                {
                    cout << t.current();
                }
                error = false;
            }catch (infile::Error err)
            {
                cout <<"File does not exist!\n";
            }
    }
    while (error);
    return 0;
}
