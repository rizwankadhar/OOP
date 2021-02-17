#include "Polynomial.h"
#include <fstream>
using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

class Menu{
    public:
        void run();


    private:
        void MenuDisplay();

        void addition();
        void product();
        void evaluate();
};
int main()
{
    Menu m;
    m.run();
    return 0;
}
void Menu::run()
{
    int n = 0;
    do{
        MenuDisplay();
        cout << endl << ">>>>" ; cin >> n;
        switch(n){
            case 1: addition();
                    break;
            case 2: product();
                    break;
            case 3: evaluate();
                    break;

        }
    }while(n!=0);
}
void Menu::MenuDisplay()
{
     cout << endl << endl;
     cout << " 0. - Quit" << endl;
     cout << " 1. - Add Polynomials" << endl;
     cout << " 2. - Multiply Polynomials" << endl;
     cout << " 3. - Evaluate a Polynomial" << endl;
}

void Menu::addition()
{
    Poly p1,p2;
    try {
        p1.getPoly();
        p2.getPoly();
        cout<<"The resultant Polynomial is :"<<p1+p2<<endl;
    }catch (Poly::ERROR err){
    if (err == Poly::NEGATIVE_DEGREE)
        cout<<"Degree can not be negative!\n";
    else
        cout<<"Un-handled Exception!\n";
    }
}
void Menu::product()
{
    Poly p1,p2,p3;
    try{
    p1.getPoly();
    p2.getPoly();
    p3 = p1*p2;
    cout<<"The resultant Polynomial is :"<<p3<<endl;
    }catch (Poly::ERROR err){
    if (err == Poly::NEGATIVE_DEGREE)
        cout<<"Degree can not be negative!\n";
    else
        cout<<"Un-handled Exception!\n";
    }
}
void Menu::evaluate()
{
    Poly p1;
    try{
    p1.getPoly();
    float value;
    cout<<"Enter the value of the variable: ";
    cin>>value;
    cout<<"The value of the Polynomial is :"<<p1.eval(value);
    }catch (Poly::ERROR err){
    if (err == Poly::NEGATIVE_DEGREE)
        cout<<"Degree can not be negative!\n";
    else
        cout<<"Un-handled Exception!\n";
    }
}

#else
#define CATCH_CONFIG_MAIN
#include "Catch.hpp"

TEST_CASE("Setting and getting degree and Coefficients of polynomial", "") {

    Poly p;
    p.setdegree(3);
    p.fill(3);
    p.fill(2);
    p.fill(1);
    p.fill(3);
    CHECK(p.getDegree()==3);
    CHECK(p.getCoffi(3)==3);
    CHECK(p.getCoffi(2)==2);
    CHECK(p.getCoffi(1)==1);
    CHECK(p.getCoffi(0)==3);
}
TEST_CASE("Adding","")
{
    Poly p,q,r;
    p.setdegree(1);
    p.fill(1);
    p.fill(2);
    q.setdegree(1);
    q.fill(1);
    q.fill(2);
    r = p+q;
    CHECK(r.getDegree() ==1);
    CHECK(r.getCoffi(1)==2);
    CHECK(r.getCoffi(0)==4);
}
TEST_CASE("Multiplication","")
{
    Poly p,q,r;
    p.setdegree(1);
    p.fill(1);
    p.fill(2);
    q.setdegree(1);
    q.fill(1);
    q.fill(2);
    r = p*q;
    CHECK(r.getDegree() ==2);
    CHECK(r.getCoffi(2)==1);
    CHECK(r.getCoffi(1)==4);
    CHECK(r.getCoffi(0)==4);
}
TEST_CASE("Evaluation","")
{
    Poly p;
    p.setdegree(2);
    p.fill(2);
    p.fill(1);
    p.fill(2);
    CHECK(p.eval(2) ==12);

}
TEST_CASE("Assignment Testing","")
{
    Poly p,q,r;
    p.setdegree(1);
    p.fill(1);
    p.fill(2);
    q = p;

    CHECK(p.getDegree() == q.getDegree());
    CHECK(p.getCoffi(1)== q.getCoffi(1));
    CHECK(p.getCoffi(0)== q.getCoffi(0));

    r = q = p;
    CHECK(p.getDegree() == r.getDegree());
    CHECK(p.getCoffi(1)== r.getCoffi(1));
    CHECK(p.getCoffi(0)== r.getCoffi(0));

    p = p;
    CHECK(p.getDegree() == 1);
    CHECK(p.getCoffi(1)== 1);
    CHECK(p.getCoffi(0)== 2);

}
TEST_CASE("Copying","")
{
    Poly p,q;
    p.setdegree(2);
    p.fill(2);
    p.fill(1);
    p.fill(2);
    q = p;

    CHECK(q.getDegree() == p.getDegree());
    CHECK(q.getCoffi(2)== p.getCoffi(2));
    CHECK(q.getCoffi(1)== p.getCoffi(1));
    CHECK(q.getCoffi(0)== p.getCoffi(0));

}
/*TEST_CASE("Exception","")
{
    Poly p;
    try{
        p.setdegree(-2);
    }catch (Poly::ERROR err){
    CHECK(err == Poly::NEGATIVE_DEGREE);
    }

}
*/
#endif
