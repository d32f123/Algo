#include <iostream>

using namespace std;

long long LCD(long long a, long long b);

int main()
{
	long long a, b;
	cin >> a >> b;
	cout << LCD(a, b);
	return 0;
}

long long LCD(long long a, long long b)
{
	return b ? LCD(b, a % b) : a;
}