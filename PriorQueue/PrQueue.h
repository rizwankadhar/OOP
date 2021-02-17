#ifndef PRQUEUE_H
#define PRQUEUE_H

#include <iostream>
#include <string>
#include <vector>

struct Item
{
    std::string data;
    int pr;
    Item():data(""),pr(0) { }
    Item(const std::string &Data,int Pr): data(Data),pr(Pr) { }
    friend std::ostream &operator<<(std::ostream &os,const Item &it);
    friend std::istream &operator>>(std::istream &is,Item &it);
    bool operator == (const Item &it)
    {
        return (it.data==data && it.pr==pr);
    }
};
class PrQueue
{
    public:
        enum ERROR { EMPTY_PRQUEUE};
        bool isEmpty() const {return (_vec.size()==0);}
        void Clear() { _vec.clear();}
        void add(const Item &it) { _vec.push_back(it);}
        Item max() const;
        Item remMax();



    private:
        std::vector<Item> _vec;
        int maxindex() const;
};

#endif // PRQUEUE_H
