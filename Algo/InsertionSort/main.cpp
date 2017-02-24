#include <iostream>
#include <time.h>
#include <cstring>

using namespace std;

//�������� ������� ���������� ���������
void InsertionSort(int*, int);

int main() {
	int N;
	cin >> N; // ���������� ���������
			  // ���� ���������� ��� �������, ��������� ��������� �����
			  // srand(time(NULL)); // ������������� ����������
			  // rand()%99 + 1: ����������� ��������� ����� �� 1 �� 99.

	int* A = new int[N]; // ��������� ������ � �������� ������ ��� ����
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	InsertionSort(A, N); // ����� ������� ����������

	delete[] A; // ����������� ������ ��-��� �������
}

void InsertionSort(int* A, int N) {
	// �������� ��� �������
	int* B = new int[N];
	int k = 0;
	B[k++] = A[0];
	for (int i = 0; i < N; ++i)
	{
		int j;
		for (j = 0; j < k; ++j)
		{
			if (B[j] > A[i])
				break;
		}
		for (int l = k; l > j; --l)
			B[l] = B[l - 1];
		B[j] = A[i];
	}
	memcpy(A, B, sizeof(int) * N);
	delete[] B;
}