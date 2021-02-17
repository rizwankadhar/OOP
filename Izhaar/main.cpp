#include <iostream>
#include <string>
using namespace std;
/*
int maxSubseq(int vec[], int n) {
	// Store the count of number of ones
	// from right to left in the array
	int suffix = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		if (vec[i] == 1)
		{
			suffix++;
			vec[i] = suffix;
		}
	}
	int res = 0;
	int zero = 0;
	for (int i = 0; i < n; i++)
	{
		if (vec[i] == 0)
			zero++;
		if (vec[i] > 0)
			res = max(res, zero + vec[i]);
	}
	return max(res, zero);
}
int main()
{
    // BAAABAB = 2
    // BBABAA = 3
    // AABBBB = 0
	int input[] = {0,0,1,1,1,1};
	int n = sizeof(input) / sizeof(input[0]);
	int lcs = maxSubseq(input, n);
	cout << n << "\n";
	cout << lcs << "\n";
	cout << (n-lcs);
	return 0;
}
*/
int maxSubseq(string s) {

	int n = s.length();
	int vec[n] = {0};
	for (int i=0;i<n;i++)
    {
        if (s.at(i) == 'B')
            vec[i] = 1;
    }

	int suffix = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		if (vec[i] == 1)
		{
			suffix++;
			vec[i] = suffix;
		}
	}
	int res = 0;
	int zero = 0;
	for (int i = 0; i < n; i++)
	{
		if (vec[i] == 0)
			zero++;
		if (vec[i] > 0)
			res = max(res, zero + vec[i]);
	}
	return max(res, zero);
}
int main()
{
    // BAAABAB = 2
    // BBABAA = 3
    // AABBBB = 0
	///int input[] = {0,0,1,1,1,1};
	///int n = sizeof(input) / sizeof(input[0]);
	int lcs = maxSubseq("AABBA");
	///cout << n << "\n";
	cout << lcs << "\n";
	///cout << (n-lcs);
	return 0;
}

