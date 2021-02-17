#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
using namespace std;
vector<int> FillFile(const string &filename);
bool maxSearch(const vector<int> v,int &maxHeight,int &maxInd);
int main()
{
    vector<int> v = FillFile("input.txt");
   int maxHeight,maxInd;
   if (maxSearch(v,maxHeight,maxInd))
   {
       cout <<"Max height is : "<<maxHeight;
       cout <<" at index : "<<maxInd+1<<endl;
   }
   else
   {
       cout<<"No Valley"<<endl;
   }
    return 0;
}
vector<int> FillFile(const string &filename)
{
    vector<int> v;
    int elem;
    fstream f(filename.c_str());
    if (f.fail())
    {
        cout<<"File does not exist\n";
        exit(1);
    }
    while (f >> elem)
    {
        v.push_back(elem);
    }
    f.close();
    return v;
}
bool maxSearch(const vector<int> v,int &maxHeight,int &maxInd)
{
    bool l = false;
    for (int i=1;i<v.size()-1;i++)
    {
        if (l && (v[i]<v[i-1] && v[i] < v[i+1]))
            {
                if (maxHeight<v[i])
                {
                    maxHeight  = v[i];
                    maxInd = i;
                }
            }
        else if (!l && (v[i]<v[i-1] && v[i] < v[i+1]))
                 {
                     maxHeight = v[i];
                     maxInd = i;
                     l = true;
                 }
    }
    cout<<maxHeight<<endl;
    return l;

}
