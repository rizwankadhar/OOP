#include <iostream>

using namespace std;
const int MaxC = 1000;
const int MaxD = 1000;
typedef struct DataL{
    string color;
    int country;
};
typedef struct CountFlags{
    string name;
    int cnt;
};

int main()
{
    int N;//color
    int M;//country
    DataL data[MaxC];
    ///int ColorStorage[MaxC+1];
    int Cnt=0;
    string AllColors[MaxC];
    cin>> N;
    cin>> M;
    for(int i=0;i<M;i++)
    {
        cin>>data[i].color;
        cin>>data[i].country;

    }
    ///Duplicate Checker
    for (int i=0;i<M;i++)
    {
        AllColors[Cnt] = data[i].color;
        Cnt++;

        for (int k=0;k<Cnt-1;k++)
        {
            if(AllColors[k] == data[i].color)
                Cnt--;
        }

    }

      cout <<"#\n"<<Cnt<<endl;


    CountFlags FlagCounting[MaxC];
    int ColorCounting = 0;
    for (int i=0;i<M;i++)
    {
        FlagCounting[ColorCounting].name = data[i].color;
        FlagCounting[ColorCounting].cnt = 0;
        for (int j=i;j<M;j++)
        {
            if (data[i].color == data[j].color)
                FlagCounting[ColorCounting].cnt++;
        }

        ColorCounting++;

        for (int k=0;k<ColorCounting-1;k++)
        {
            if (FlagCounting[k].name == data[i].color)
                ColorCounting--;
        }
    }
    cout <<"#\n";
    for (int i=0;i<ColorCounting;i++)
    {
        cout <<FlagCounting[i].name <<" "<<FlagCounting[i].cnt<<endl;
    }
    string oneFlag = "NONE";
    for (int i=0;i<ColorCounting;i++)
    {
        if (FlagCounting[i].cnt == 1)
            oneFlag = FlagCounting[i].name;
    }
    cout <<"#\n";
    cout <<oneFlag <<endl;

    int CountryFlags[MaxC] = {0};
    for (int i=0;i<M;i++)
    {
        CountryFlags[data[i].country]++;
    }
    int maxCountry = 1;
    int maxColors = CountryFlags[1];
    for (int i=2;i<=N;i++)
    {
        if (CountryFlags[i]> maxColors)
            {
                maxColors = CountryFlags[i];
                maxCountry = i;
            }
    }
    cout <<"#\n";
    cout <<maxCountry <<endl;


    return 0;
}
