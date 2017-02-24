#include <iostream>

using namespace std;

long long LCD(long long a, long long b);

inline void swap(long long * a, long long * b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

int main()
{
	long long a, b;
	cin >> a >> b;
	cout << LCD(a, b);
	system("pause");
	return 0;
}

long long LCD(long long a, long long b)
{
	if (b == a)
		return a;
	if (a > b && a % b == 0)
		return b;
	else if (b > a && b % a == 0)
		return a;
	while (a != 0 && b != 0)
	{
		if (a > b)
		{
			a = a % b;
		}
		else
		{
			b = b % a;
		}
	}
	return a + b;
}