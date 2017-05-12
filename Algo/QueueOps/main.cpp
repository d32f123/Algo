#include <iostream>
#include <limits.h>
using namespace std;

const int M = 8; // ����� �������, ���������� ��� �������

				 // ��������� �������
bool PutInQueue(int);
int TakeFromQueue();
void debugging();
void test();
void printqueue();

// �������� ��������� �������
struct QUEUE {
	int Q[M]; // ������, ������������ ��� �������� �������
	int F; // ������ ������� �������� �������
	int L; // ������ ����������
	bool IsEmpty; // ������� ������ �������
};
QUEUE T;

int main() {
	// ������� ���������� ��������� �������
	T.F = 0;
	T.L = -1;
	T.IsEmpty = true;

	// ��������!!!
	// ��� ������� ��������� ����������� ��������� debugging()
	// ������������ ���������� � ������� ��������� test()
	debugging(); // ��� �������� ������� �� ipc ����������������
	//test();      // ��� �������� ������� �� ipc ����������������� 
	return 0;
}

bool PutInQueue(int x) {
	// �������� ��� �������
	// ��������� ������� x � �������
	// ���������� ������ � ������ ������
	if ((T.F - (T.L + 1)) % M == 0 && !T.IsEmpty) // ������ ������ -- ����� T.F ����� ����
	{
		return false;	// ������ �������
	}
	T.Q[++T.L, T.L %= 8] = x;
	T.IsEmpty = false;
	return true;
}

//----------------------------------------------
int TakeFromQueue() {
	// �������� ��� �������
	// ����� ������� �� ������� T
	// ������� ���������� ������ �� ������� �������
	// ���� ������� �����, �� ������������ INT_MAX (defined � limits.h)
	if (T.IsEmpty)
		return INT_MAX;
	if ((T.F + 1 - T.L) % M == 1)
	{
		T.IsEmpty = true;
	}
	return T.Q[T.F + 1 == M ? (T.F = 0) + M - 1 : ++T.F - 1];
}

void debugging() { // ��������� ��� �������
	int k = 0;
	char c;
	do {
		system("cls");
		cout << "1. �������� ������� � �������\n";
		cout << "2. ����� ������� �� �������\n";
		cout << "3. ���������� �������\n";
		cout << "4. �����\n\n";
		cin.get(c);
		switch (c) {
		case '1':
			system("cls");
			cout << "Input int element\n";
			int x;
			cin >> x;
			if (!PutInQueue(x)) {
				cout << "Queue is overflow\n\n";
				system("pause");
			}
			break;
		case '2': // ������ �������
			system("cls");
			k = TakeFromQueue();
			if (k != INT_MAX) cout << "Value = " << k << endl;
			else cout << "Queue is empty\n\n";
			system("pause");
			break;
		case '3': // ����� ������� �� �����
			system("cls");
			printqueue();
			system("pause");
			break;
		case '4':
			return;
			break;
		default:
			continue;
		}
	} while (true);
}
void printqueue() {
	if (T.IsEmpty) {
		cout << "Queue is empty\n";
		system("pause");
		return;
	}
	cout << "Start: ";
	if (T.F<T.L) {
		for (int i = T.F; i != T.L + 1; i++) {
			cout << T.Q[i] << " < ";
		}
	}
	else {
		for (int i = T.F; i != T.L; i++) {
			if (i == M) {
				i = 0;
			}
			cout << T.Q[i] << " < ";
		}
		cout << T.Q[T.L] << " < ";
	}
	cout << "End\n";
}

void test() {
	int x;
	for (int i = 0; i < M + 1; i++) {
		cin >> x;
		if (!PutInQueue(x)) cout << "overflow" << endl;
	}
	printqueue();

	for (int i = 0; i < M / 2; i++) {
		cout << TakeFromQueue() << ", ";
	}
	cout << endl;
	for (int i = 0; i < 1 + M / 2; i++) {
		cin >> x;
		if (!PutInQueue(x)) cout << "overflow" << endl;
	}
	printqueue();
	for (int i = 0; i < M + 1; i++) {
		cout << TakeFromQueue() << ", ";
	}
}