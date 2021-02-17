#include "Angler.h"

using namespace std;

string max(string filename)
{
    EnorAngler t(filename);
    string angler ="";
    int cnt = 0;
    t.first();

    for ( ;!t.end(); t.next())
    {
        if (t.current().tuna_cnt > cnt)
        {
            cnt = t.current().tuna_cnt;
            angler = t.current().name;
        }
    }
    return angler;
}
#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    string filename;
    cout <<"Enter filename:";
    cin>>filename;
    if (max(filename) == "")
        cout << "Empty File/No angler caught Tuna"<<endl;
    else
        cout << max(filename)<<endl;
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "Catch.hpp"

///Max Search
TEST_CASE("Empty file", "empty.txt")
{
    CHECK(max("empty.txt")=="");
}
TEST_CASE("1 angler", "t1.txt")
{
    CHECK(max("t1.txt")== "Hassan");
}
TEST_CASE("More anglers with Tuna", "t2.txt")
{
    CHECK(max("t2.txt")== "Ahtisham");
}
TEST_CASE("First angler has caught most Tuna", "t2.txt")
{
    CHECK(max("t2.txt")== "Ahtisham");
}
TEST_CASE("Last angler has caught most Tuna", "t3.txt")
{
    CHECK(max("t3.txt")== "Baqir");
}
TEST_CASE("More than 1 anglers caught equal Tunas", "t4.txt")
{
    CHECK(max("t4.txt")== "Baqir");
}
TEST_CASE("No angler caught Tuna", "t5.txt")
{
    CHECK(max("t5.txt")== "");
}
///Summation
TEST_CASE("No Tuna", "t5.txt")
{
    EnorAngler t("t5.txt");
    t.first();
    CHECK(t.current().tuna_cnt == 0);
}
TEST_CASE("1 angler 1 contest", "t1.txt")
{
    EnorAngler t("t1.txt");
    t.first();
    CHECK(t.current().tuna_cnt == 1);
}
TEST_CASE("1 angler more contests", "t1.txt")
{
    EnorAngler t("t5.txt");
    t.first();
    CHECK(t.current().tuna_cnt == 0);
}
TEST_CASE("No Tuna on first but rest", "t6.txt")
{
    EnorAngler t("t6.txt");
    t.first();
    CHECK(t.current().tuna_cnt == 4);
}
TEST_CASE("No Tuna on last but rest", "t7.txt")
{
    EnorAngler t("t7.txt");
    t.first();
    CHECK(t.current().tuna_cnt == 4);
}
TEST_CASE("No catch at any contest", "t5.txt")
{
    EnorAngler t("t5.txt");
    t.first();
    CHECK(t.current().tuna_cnt == 0);
}
TEST_CASE("Tuna at one of the contests", "t8.txt")
{
    EnorAngler t("t8.txt");
    t.first();
    CHECK(t.current().tuna_cnt == 1);
}
TEST_CASE("Tuna on some of the contests", "t7.txt")
{
    EnorAngler t("t7.txt");
    t.first();
    CHECK(t.current().tuna_cnt == 4);

}
TEST_CASE("Tuna on all of the contests", "t9.txt")
{
    EnorAngler t("t9.txt");
    t.first();
    CHECK(t.current().tuna_cnt == 3);

}
///Counting
TEST_CASE("A line without Catch", "t5.txt")
{
    EnorData t("t5.txt");
    t.first();
    CHECK(t.current().tunas == 0);
}
TEST_CASE("A line with 1 catch", "t4.txt")
{
    EnorData t("t4.txt");
    t.first();
    CHECK(t.current().tunas == 0);
}
TEST_CASE("A line with multiple catches", "t9.txt")
{
    EnorData t("t9.txt");
    t.first();
    CHECK(t.current().tunas == 1);
}
TEST_CASE("A line where first catch is Tuna", "t10.txt")
{
    EnorData t("t10.txt");
    t.first();
    CHECK(t.current().tunas == 3);
}
TEST_CASE("A line where last catch is Tuna", "t10.txt")
{
    EnorData t("t7.txt");
    t.first();
    CHECK(t.current().tunas == 1);
}
TEST_CASE("A line without Tuna", "t6.txt")
{
    EnorData t("t6.txt");
    t.first();
    CHECK(t.current().tunas == 0);
}
TEST_CASE("A line with 1 Tuna", "t1.txt")
{
    EnorData t("t1.txt");
    t.first();
    CHECK(t.current().tunas == 1);
}
TEST_CASE("A line with multiple Tuna", "t10.txt")
{
    EnorData t("t10.txt");
    t.first();
    CHECK(t.current().tunas == 3);
}

#endif
