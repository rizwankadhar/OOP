#include <iostream>
#include <vector>
using namespace std;

int singleNumber(vector<int>& nums)
{
    int single;
    for (int i : nums)
    {
        int count = 0;
        for (int j=0;j<nums.size();j++)
        {
            if (i == nums[j]) count++;
        }
        if (count == 1)
            single = i;
    }
    return single;
}

int main()
{
    vector<int> v = {2,2,1};
    cout <<singleNumber(v)<<endl;
    return 0;
}
