#include "PrQueue.h"

std::ostream &operator<<(std::ostream &os,const Item &it)
{
    os<< "Group name : "<<it.data<<", Points : "<<it.pr;
    return os;
}
std::istream &operator>>(std::istream &is,Item &it)
{
    is >> it.data >> it.pr;
    return is;
}
int PrQueue::maxindex() const
{
    int max = _vec[0].pr;
    int ind = 0;
    for (int i=1;i<_vec.size();i++)
    {
        if (_vec[i].pr > max)
        {
            max = _vec[i].pr;
            ind  = i;
        }
    }
    return ind;
}
Item PrQueue::max() const
{
    if (_vec.size()==0) throw EMPTY_PRQUEUE;
    return _vec[maxindex()];
}
Item PrQueue::remMax()
{
     if (_vec.size()==0) throw EMPTY_PRQUEUE;
     int ind = maxindex();
     Item it = _vec[ind];
     _vec[ind] = _vec.back();///_vec[_vec.size()-1]
     _vec.pop_back();
     return it;
}
