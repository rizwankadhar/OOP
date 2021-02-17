#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;
vector<int> getinput(const string &filename);
bool maxS(const vector<int> v,int &maxH,int maxI);

int main()
{
    vector<int> v  = getinput("in.txt");
    int maxH,maxI;
    if (maxS(v,maxH,maxI))
    {
        cout<<"yes\n";
    }
    return 0;
}
vector<int> getinput(const string &filename)
{
    vector<int> v;
    int elem;
    ifstream f;///(filename.c_str());
    f.open("in.txt");
    if (f.fail())
    {
        cout<<"File does not exist";
        exit(1);
    }
    while (f>>elem)
    {
        v.push_back(elem);
    }
    f.close();
    return v;
}
bool maxS(const vector<int> v,int &maxH,int maxI)
{
   bool l = false;
   for (int i=1;i<v.size()-1;i++)
   {
       if (v[i]<v[i-1] && v[i]<v[i+1])
       {
           maxH = v[i];
           maxI = i;
           l = true;
       }
   }
   return l;
}
