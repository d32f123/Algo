#include <iostream>

using namespace std;

int Combin(int, int);

int main()
{
	int N, K;
	cin >> N >> K;
	cout << Combin(K, N);
	system("pause");
	return 0;
}

int Combin(int K, int N)
{
	if (!K || K == N)
		return 1;
	return Combin(K, N - 1) + Combin(K - 1, N - 1);
}