#include <iostream>
#include <math.h>

using namespace std;

void printArray(int * A, int l);

int main()
{
	int N;
	cin >> N;
	for (int z = 0; z < N; ++z)
	{
		int n, k; // n -- number of fighters, k -- number of teams
		cin >> n >> k;
		int * A = new int[k];
		int m = n / k; // how many fighters per team(floor)
		for (int i = 0; i < n % k; ++i)
			A[i] = m + 1;
		for (int i = n % k; i < k; ++i)
			A[i] = m;
		long long sum = 0;
		for (int i = 0; i < k - 1; ++i)
		{
			for (int j = i + 1; j < k; ++j)
				sum += A[i] * A[j];
		}
		cout << sum << endl;
	}
	return 0;
}

void printArray(int * A, int l)
{
	for (int i = 0; i < l; ++i)
		cout << A[i] << " << ";
	cout << endl;
}