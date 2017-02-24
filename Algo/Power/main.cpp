#include <iostream>
using namespace std;

double Power(double, int);

int main() 
{
	double X;
	int N;
	cin >> X >> N;
	cout << Power(X, N);
	return 0;
}

double Power(double X, int N) 
{
	if (N) // N != 0
	{
		if (N < 0)
			return 1.0 / Power(X, -N);
		if (N % 2 == 0)
		{
			double t = Power(X, N / 2);
			return t * t;
		}
		else
		{
			return X * Power(X, N - 1);
		}
	}
	else return 1;
}