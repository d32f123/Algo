#include <iostream>
#include <time.h>
#include <cstring>

using namespace std;

// ��������� �������
void merge(int*, int, int);
void mergeRec(int*, int, int);
int N;
int * B;

int main() {
	cin >> N; // ���������� ������� ���������
			  // ���� ���������� ��� �������, ��������� ��������� �����
			   //srand(time(NULL)); // ������������� ����������
			  // rand()%99 + 1: ����������� ��������� ����� �� 1 �� 99.

	int* A = new int[N];
	B = new int[N];
	for (int i = 0; i < N; i++) {
		cin >> A[i]; // ���������� �������
		//A[i] = rand() % 99 + 1;
	}
	mergeRec(A, 0, N - 1); // ����� ����������

	for (int i = 0; i < N; i++) {
		cout << A[i] << " "; // ������
	}
	delete[] A, B; // ���������� ������
	return 0;
}

void mergeRec(int* A, int left, int right) {
	// ����������� ����� ����������, ����� ����� �������
	// ���������� �����������
	if (right - left < 1)
		return;
	int mid = (right + left) / 2;
	mergeRec(A, left, mid);
	mergeRec(A, mid + 1, right);
	merge(A, left, right);
}

void swap(int * A, int i, int j)
{
	int t = A[i];
	A[i] = A[j];
	A[j] = t;
}

void merge(int *A, int left, int right) {
	// ��������� ��� ������� A[left .. mid] � A[mid+1 .. right];
	// ���������� �����������
	
	int mid = (right + left) / 2;
	int i = left, j = mid + 1, k = 0; // left head and right head
	while (i != mid + 1 || j != right + 1)
	{
		if (i == mid + 1)
			B[k++] = A[j++];
		else if (j == right + 1)
			B[k++] = A[i++];
		else if (A[i] > A[j])
			B[k++] = A[j++];
		else
			B[k++] = A[i++];
	}
	memcpy(A + left, B, sizeof(int) * k);
}