#include <iostream>
#include <time.h>
#include <cstring>

using namespace std;

//прототип функции сортировки вставками
void InsertionSort(int*, int);

int main() {
	int N;
	cin >> N; // количество элементов
			  // если пригодитс€ дл€ отладки, генератор случайных чисел
			  // srand(time(NULL)); // инициализатор генератора
			  // rand()%99 + 1: сгенерирует случайное число от 1 до 99.

	int* A = new int[N]; // объ€вл€ем массив и выдел€ем пам€ть дл€ него
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	InsertionSort(A, N); // вызов функции сортировки

	delete[] A; // освобождаем пам€ть из-под массива
}

void InsertionSort(int* A, int N) {
	// Ќјѕ»Ў»“≈ Ё“” ‘”Ќ ÷»ё
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