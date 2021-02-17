#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>

using namespace std;
vector<int> getinput(const string &file);
int frequent(const vector<int> v,int &freq,int &cnt);
int main()
{
    vector<int> v = getinput("input.txt");
    int freq,cnt;
    int mostfreq = frequent(v,freq,cnt);
    cout<<mostfreq<<endl;

    return 0;
}
vector<int> getinput(const string &file)
{
    vector<int> v;
    int elem;
    fstream f(file.c_str());
    if (f.fail())
    {
        cout<<"File does not exist!\n";
        exit(1);
    }
    while (f >> elem)
    {
        v.push_back(elem);
    }
    f.close();
    return v;
}
int frequent(const vector<int> v,int &freq,int &cnt)
{
    cnt = 0;
    for (int i=0;i<v.size();i++)
    {
        int frequency = 0;
        for (int j=0;j<v.size();j++)
        {
            if (v[i]==v[j])
            {
                frequency++;
            }
        }
        if (frequency>cnt)
        {
            cnt = frequency;
            freq = v[i];
        }
    }
    return freq;
}
