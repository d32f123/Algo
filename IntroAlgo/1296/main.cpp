#include <iostream>

using namespace std;

const size_t MAX_N = 60000;

int max_potential(int * max_P, int * P, int N);

int main()
{
	int N;
	int P[MAX_N];
	int max_P[MAX_N];


	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> P[i];
		max_P[i] = -1;
	}
	
	for (int i = 0; i < N; ++i)
		max_potential(max_P, P, i);
	
	int max = 0;
	for (int i = 0; i < N; ++i)
		if (max_P[i] > max)
			max = max_P[i];
	cout << max;
	return 0;
}

int max_potential(int * max_P, int * P, int N)
{
	if (N == 0)
	{
		max_P[0] = P[0];
		return P[0];
	}
	if (max_P[N] != -1)
		return max_P[N];
	return max_P[N] = max_potential(max_P, P, N - 1) + P[N] > P[N] ? max_potential(max_P, P, N - 1) + P[N] : P[N];
}