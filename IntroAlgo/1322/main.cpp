#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>


using namespace std;

const int LEXSIZE = 54;
char lex[LEXSIZE] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";
char lexIndex[256];    // used for sorting
int lexCounter[256];  // counts how many specific chars are there
int matrixCounter[256];	   // tells us which occurence of the character it currently is

void merge(char *, char *, int, int);
void mergeRec(char *, char *, int, int);

int main()
{
	memset(lexCounter, 0, sizeof(int) * 256);
	memset(matrixCounter, (int) -1, sizeof(int) * 256);
	for (int i = 0; i < LEXSIZE; ++i)
	{
		lexIndex[lex[i]] = i;
	}

	int k;
	string base;
	cin >> k;
	cin >> base;
	int N = base.size();

	char ** resultMatrix = new (char *[N]);
	for (int i = 0; i < N; ++i)
		resultMatrix[i] = new char[2];

	char * sortedBase = new char[N];
	char * temp = new char[N];
	strcpy(sortedBase, base.c_str());

	mergeRec(sortedBase, temp, 0, N - 1);
	
	for (int i = 0; i < N; ++i) // forming initial matrix based on the rules
	{
		resultMatrix[i][0] = sortedBase[i];
		resultMatrix[i][1] = base[i];
	}

	for (int i = 0; i < N; ++i)
	{
		++lexCounter[sortedBase[i]];
	}

	int * next = new int[N];
	memset(next, INT_MAX, sizeof(int) * N);
	for (int i = 0; i < N; ++i) // now try to deduce any obvious nexts
	{
		if (lexCounter[resultMatrix[i][0]] == 1)
		{
			for (int j = 0; j < N; ++j)
			{
				if (resultMatrix[j][1] == resultMatrix[i][0] && i != j)
					next[i] = j;
			}
		}
	}

	for (int i = 0; i < N; ++i) // now deduce the rest
	{
		if (next[i] == 0)
			continue;
		int l;
		for (l = matrixCounter[resultMatrix[i][0]] + 1; l < N; ++l)
		{
			if (resultMatrix[l][1] == resultMatrix[i][0])
			{
				matrixCounter[resultMatrix[i][0]] = l;
				break;
			}
		}
		next[i] = l;
	}

	--k;
	for (int i = 0; i < N; ++i)
	{
		cout << base[k = next[k]];
	}

	return 0;
}

void mergeRec(char * A, char * B, int left, int right) {
	if (right - left < 1)
		return;
	int mid = (right + left) / 2;
	mergeRec(A, B, left, mid);
	mergeRec(A, B, mid + 1, right);
	merge(A, B, left, right);
}

void swap(char * A, int i, int j)
{
	char t = A[i];
	A[i] = A[j];
	A[j] = t;
}

void merge(char *A, char * B, int left, int right) {


	int mid = (right + left) / 2;
	int i = left, j = mid + 1, k = 0; // left head and right head
	while (i != mid + 1 || j != right + 1)
	{
		if (i == mid + 1)
			B[k++] = A[j++];
		else if (j == right + 1)
			B[k++] = A[i++];
		else if (lexIndex[A[i]] > lexIndex[A[j]])
			B[k++] = A[j++];
		else
			B[k++] = A[i++];
	}
	memcpy(A + left, B, sizeof(char) * k);
}