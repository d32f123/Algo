#include <iostream>
#include <algorithm>
#include <bitset>
#include <stack>
#include <limits.h>

using namespace std;

int main()
{
	int K, k, min = INT_MAX;
	cin >> K;
	int * a = new int[K];
	for (int i = 0; i < K; i++)
	{
		cin >> k;
		a[i] = k;
	}
	bitset<20> bits = (0); //current bitset
	bitset<20> prev = (0); //previous bitset
	stack<int> s1; // stack for first sum
	stack<int> s2; // stack for secnd sum
	s1.push(a[0]);
	for (int i = 1; i < K; ++i)
		s1.push(s1.top() + a[i]);
	while (bits.to_ulong() < pow(2, K) - 1)
	{
		prev = bits;
		bits = bits.to_ulong() + 1;
		for (int i = 0; i < K; ++i)
			if (bits[i] != prev[i])
			{
				if (bits[i] == 1)
				{
					s1.pop();
				}
				else
				{
					s2.pop();
				}
			}
		for (int i = K - 1; i >= 0; --i)
		{
			if (bits[i] != prev[i])
			{
				if (bits[i] == 1)
				{
					if (s2.empty())
						s2.push(a[K - i - 1]);
					else
						s2.push(s2.top() + a[K - i - 1]);
				}
				else
				{
					if (s1.empty())
						s1.push(a[K - i - 1]);
					else
						s1.push(s1.top() + a[K - i - 1]);
				}
			}
		}
		int t;
		if (s1.empty())
			t = s2.top();
		else if (s2.empty())
			t = s1.top();
		else
			t = s1.top() - s2.top();
		t = abs(t);
		if (t < min)
			min = t;
	}
	cout << min;
	return 0;
}