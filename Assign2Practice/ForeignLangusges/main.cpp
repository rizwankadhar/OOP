#include <iostream>

using namespace std;
const int MaxPersons = 1000;
const int maxM = 2000;
const int MaxLang = 10;
typedef struct Languages{
    int personId;
    string language;
}PersonLang;
typedef struct lang{
    string name;
    int Cnt;
}langCnt;

int main()
{
    PersonLang PersonLangpair[maxM];
    int M,N;
    cin >>N>>M;
    for (int i=0;i<M;i++)
    {
        cin>>PersonLangpair[i].personId;
        cin>>PersonLangpair[i].language;
    }
    string Lang[maxM];
    ///Task1
    int Cnt = 0;
    for (int i=0;i<M;i++)
            {
            Lang[Cnt] = PersonLangpair[i].language;
            Cnt++;

            for (int k=0;k<Cnt-1;k++)
            {
                if (PersonLangpair[i].language == Lang[k])
                {
                    Cnt--;
                }
            }
        }
        cout <<"#\n"<<Cnt<<endl;
        ///Task2
        int languageCnt[MaxPersons] = {0};
        langCnt EachLangScore[1000];
        int languageCounting = 0;
        for (int i=0;i<M;i++)
        {
            languageCnt[PersonLangpair[i].personId]++;
            EachLangScore[languageCounting].name = PersonLangpair[i].language;
            EachLangScore[languageCounting].Cnt = 0;
            for (int j=i;j<M;j++)
            {
                if (PersonLangpair[i].language == PersonLangpair[j].language)
                    EachLangScore[languageCounting].Cnt++;

            }
            languageCounting++;

            for (int k=0;k<languageCounting-1;k++)
                {
                    if (PersonLangpair[i].language == EachLangScore[k].name)
                    {
                        languageCounting--;
                    }
                }

        }
        cout <<"#\n";
    for (int i=1;i<=N;i++)
        {
            if (languageCnt[i]>0)
                cout<< i <<" "<<languageCnt[i]<<endl;
        }


    int maxLanguage = EachLangScore[0].Cnt;
    string maxSpoken = EachLangScore[0].name;
    for (int i=1;i<languageCounting;i++)
    {
        if (EachLangScore[i].Cnt > maxLanguage)
        {
            maxLanguage = EachLangScore[i].Cnt;
            maxSpoken = EachLangScore[i].name;
        }
    }
    cout <<"#\n";
    cout << maxSpoken <<endl;
    int ZeroLang=-1;
    for (int i=1;i<=N;i++)
    {
        if (languageCnt[i]== 0)
            ZeroLang = i;
    }
    cout <<"#\n";
    cout <<ZeroLang<<endl;
    return 0;
}
