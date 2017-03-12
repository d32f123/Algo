#include <iostream>
#include <climits>
#include <math.h>

using namespace std;

struct Point 
{
	int X;
	int Y;
	double Angle;
	int oldIndex;

	struct Point() {}

	struct Point(int x, int y) 
	{
		this->X = x;
		this->Y = y;
	}
};

void merge(Point *, Point *, int, int);
void mergeRec(Point *, Point *, int, int);

int main()
{
	Point * arr;
	
	int N;
	cin >> N;
	arr = new Point[N];

	int xi, yi;
	int minIndex = 0;
	for (int i = 0; i < N; ++i)
	{
		cin >> xi >> yi;
		arr[i].X = xi;
		arr[i].Y = yi;
		arr[i].oldIndex = i;
		if (arr[i].Y < arr[minIndex].Y || arr[i].Y == arr[minIndex].Y && arr[i].X < arr[minIndex].X)
		{
			minIndex = i;
		}

	}

	Point temp = arr[minIndex];
	arr[minIndex] = arr[0];
	arr[0] = temp;

	for (int i = 1; i < N; ++i)		//finding angles relative to the minPoint
	{
		arr[i].Angle = acos((arr[i].X - arr[0].X) /
			sqrt(pow(arr[i].X - arr[0].X, 2) + pow(arr[i].Y - arr[0].Y, 2)));
	}

	// now sort
	Point * tempArr = new Point[N - 1];
	mergeRec(arr, tempArr, 1, N - 1);

	int index = N / 2;

	cout << arr[0].oldIndex + 1 << " " << arr[index].oldIndex + 1;

	return 0;
}

void mergeRec(Point * A, Point * B, int left, int right) {
	if (right - left < 1)
		return;
	int mid = (right + left) / 2;
	mergeRec(A, B, left, mid);
	mergeRec(A, B, mid + 1, right);
	merge(A, B, left, right);
}

void swap(Point * A, int i, int j)
{
	Point t = A[i];
	A[i] = A[j];
	A[j] = t;
}

void merge(Point *A, Point * B, int left, int right) {


	int mid = (right + left) / 2;
	int i = left, j = mid + 1, k = 0; // left head and right head
	while (i != mid + 1 || j != right + 1)
	{
		if (i == mid + 1)
			B[k++] = A[j++];
		else if (j == right + 1)
			B[k++] = A[i++];
		else if (A[i].Angle > A[j].Angle)
			B[k++] = A[j++];
		else
			B[k++] = A[i++];
	}
	memcpy(A + left, B, sizeof(Point) * k);
}