#include <iostream>
#include <cstring>

using namespace std;

const int max_N = 9;
constexpr int power_2[max_N + 1] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };

void printMatrix(int * matrix, int length, int width);
void generateMatrix(int * matrix, int N, int x, int y, int n, int i, int j); // x -- starting x point
														// y -- starting y point
														// n -- size of matrix (2^n)
void rotateMatrix(int * matrix, int N, int x, int y, int n, int deg); // deg -- amount of 90 degs (0 -- 90, 1 -- 180, 2 -- 270)

int main()
{
	int N, n;
	
	cin >> n;
	N = power_2[n];

	if ((N * N - 1) % 3 != 0)
		cout << "-1\n";

	int * T = new int[N * N];
	memset(T, -1, sizeof(int) * N * N);

	int x, y;
	cin >> x >> y;

	generateMatrix(T, N, 0, 0, n, x - 1, y - 1);

	printMatrix(T, N, N);
	return 0;
}

void generateMatrix(int * matrix, int N, int x, int y, int n, int i, int j)
{
	static int currNum = 1;
	matrix[(x + i)*N + (y + j)] = 0;

	if (n == 1)
	{
		for (int a = 0; a < 2; ++a)
		{
			for (int b = 0; b < 2; ++b)
			{
				if (!(a == i && b == j))
					matrix[(x + a)*N + (y + b)] = currNum;
			}
		}
		++currNum;
		return;
	}															//				    ---------
	if (i < power_2[n] / 2 && j < power_2[n] / 2)				// first quarter	| * |	|	
	{															//					---------
		generateMatrix(matrix, N, x, y, n - 1, i, j);

		generateMatrix(matrix, N, x + power_2[n] / 2, y, n - 1, 0, 0); //gen 2nd quarter
		rotateMatrix(matrix, N, x + power_2[n] / 2, y, n - 1, 0);

		generateMatrix(matrix, N, x, y + power_2[n] / 2, n - 1, 0, 0); //gen 4th quarter
		rotateMatrix(matrix, N, x, y + power_2[n] / 2, n - 1, 2);

		generateMatrix(matrix, N, x + power_2[n] / 2, y + power_2[n] / 2, n - 1, 0, 0); //gen 3rd quarter

		matrix[(x + power_2[n] / 2)*N + (y + power_2[n] / 2 - 1)] = currNum;
		matrix[(x + power_2[n] / 2)*N + (y + power_2[n] / 2)] = currNum;
		matrix[(x + power_2[n] / 2 - 1)*N + (y + power_2[n] / 2)] = currNum; //fourth quarter set

		++currNum;
		return;
	}															//				    ---------
	if (i < power_2[n] / 2 && j < power_2[n])					// fouth quarter	|   | * |
	{															//					---------		
		generateMatrix(matrix, N, x, y + power_2[n] / 2, n - 1, i, j - power_2[n] / 2);

		generateMatrix(matrix, N, x, y, n - 1, 0, 0);			//gen 1st quarter
		rotateMatrix(matrix, N, x, y, n - 1, 1);				//rotate by 180

		generateMatrix(matrix, N, x + power_2[n] / 2, y, n - 1, 0, 0); //gen 2nd quarter
		rotateMatrix(matrix, N, x + power_2[n] / 2, y, n - 1, 0);  //rotate by 90 clockwise

		generateMatrix(matrix, N, x + power_2[n] / 2, y + power_2[n] / 2, n - 1, 0, 0); //gen 3rd quarter

		matrix[(x + power_2[n] / 2 - 1)*N + (y + power_2[n] / 2 - 1)] = currNum; //first quarter set
		matrix[(x + power_2[n] / 2)*N + (y + power_2[n] / 2 - 1)] = currNum;	 //second quarter set
		matrix[(x + power_2[n] / 2)*N + (y + power_2[n] / 2)] = currNum;		 //third quarter set
		++currNum;
		return;
	}
	if (i < power_2[n] && j < power_2[n] / 2)					// second quarter
	{
		generateMatrix(matrix, N, x + power_2[n] / 2, y, n - 1, i - power_2[n] / 2, j);

		generateMatrix(matrix, N, x, y, n - 1, 0, 0);			//gen 1st quarter
		rotateMatrix(matrix, N, x, y, n - 1, 1);				//rotate by 180

		generateMatrix(matrix, N, x + power_2[n] / 2, y + power_2[n] / 2, n - 1, 0, 0); //gen 3rd quarter

		generateMatrix(matrix, N, x, y + power_2[n] / 2, n - 1, 0, 0); //gen 4th quarter
		rotateMatrix(matrix, N, x, y + power_2[n] / 2, n - 1, 2);

		matrix[(x + power_2[n] / 2 - 1)*N + (y + power_2[n] / 2 - 1)] = currNum; //first quarter set
		matrix[(x + power_2[n] / 2)*N + (y + power_2[n] / 2)] = currNum;		 //third quarter set
		matrix[(x + power_2[n] / 2 - 1)*N + (y + power_2[n] / 2)] = currNum;	 //fourth quarter set
		++currNum;
		return;
	}
	generateMatrix(matrix, N, x + power_2[n] / 2, y + power_2[n] / 2, n - 1, i - power_2[n] / 2, j - power_2[n] / 2);

	generateMatrix(matrix, N, x, y, n - 1, 0, 0);			//gen 1st quarter
	rotateMatrix(matrix, N, x, y, n - 1, 1);				//rotate by 180

	generateMatrix(matrix, N, x + power_2[n] / 2, y, n - 1, 0, 0); //gen 2nd quarter
	rotateMatrix(matrix, N, x + power_2[n] / 2, y, n - 1, 0);  //rotate by 90 clockwise

	generateMatrix(matrix, N, x, y + power_2[n] / 2, n - 1, 0, 0); //gen 4th quarter
	rotateMatrix(matrix, N, x, y + power_2[n] / 2, n - 1, 2);

	matrix[(x + power_2[n] / 2 - 1)*N + (y + power_2[n] / 2 - 1)] = currNum; //first quarter set
	matrix[(x + power_2[n] / 2)*N + (y + power_2[n] / 2 - 1)] = currNum;	 //second quarter set
	matrix[(x + power_2[n] / 2 - 1)*N + (y + power_2[n] / 2)] = currNum;	 //fourth quarter set
	++currNum;
	return;
}

void rotateMatrix(int * matrix, int N, int x, int y, int n, int deg)
{
	int * temp = new int[power_2[n] * power_2[n]];
	switch (deg)
	{
	case 0: // 90 clockwise
		for (int i = 0; i < power_2[n]; ++i)
		{
			for (int j = 0; j < power_2[n]; ++j)
			{
				temp[i * power_2[n] + (power_2[n] - j - 1)] = matrix[(x + j)*N + (y + i)];
			}
		}
		break;
	case 1: // 180 deg
		for (int i = 0; i < power_2[n]; ++i)
		{
			for (int j = 0; j < power_2[n]; ++j)
			{
				temp[(power_2[n] - i - 1) * power_2[n] + (power_2[n] - j - 1)] = matrix[(x + i)*N + (y + j)];
			}
		}
		break;
	case 2: // 270 clockwise
		rotateMatrix(matrix, N, x, y, n, 1);
		rotateMatrix(matrix, N, x, y, n, 0);
		delete[] temp;
		return;
	default:
		delete[] temp;
		return;
	}
	for (int i = 0; i < power_2[n]; ++i)
	{
		for (int j = 0; j < power_2[n]; ++j)
		{
			matrix[(x + i)*N + (y + j)] = temp[i * power_2[n] + j];
		}
	}
	delete[] temp;
	return;
}

void printMatrix(int * matrix, int length, int width)
{
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			cout << matrix[i * length + j] << "\t";
		}
		cout << endl;
	}
}