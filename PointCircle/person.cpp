#include<iostream>
#include<string>
using namespace std;

class person
{
private:
    string name;
    int age;
    int id;
public:
    person()//constructor is used to put initial values whenever an object is created
    {
        name="Odai";
        age=25;
        id=123;
    }
    void set_name(string n)
    {
        name=n;
    }
    string get_name()
    {
        return name;
    }

    void set_age(int n)
    {
        age=n;
    }
    int get_age()
    {
        return age;
    }

    void set_id(int n)
    {
        id=n;
    }
    int get_id()
    {
        return id;
    }

   friend ostream &operator<<(ostream &out,const person &c);
   friend istream &operator>>(istream &in,const person &c);
};


int main()
{
    person odai;
    person rizwan;
    cout<<odai.get_name()<<endl;
    cout<<rizwan.get_name()<<endl;
    return 0;
}
