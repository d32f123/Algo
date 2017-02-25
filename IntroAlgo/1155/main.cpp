#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int vertexNum = 8;

int rmVertex(int * arr, size_t vertex1, size_t vertex2)
{
	if (arr[vertex1] && arr[vertex2])
	{
		int min = (arr[vertex1] < arr[vertex2]) ? arr[vertex1] : arr[vertex2];
		arr[vertex1] -= min;
		arr[vertex2] -= min;
		return min;
	}
	return 0;
}

int main()
{
	int duonArr[vertexNum];
	std::ostringstream sout;

	for (int i = 0; i < vertexNum; ++i)
	{
		cin >> duonArr[i];
	}

	//Основной проход (просто удаляем соседние дуоны) (упрощаем работу)
	// AB BC CD AD EF FG GH HE AE BF CG DH
	int k;

	k = rmVertex(duonArr, 0, 1);
	for (int i = 0; i < k; ++i) //AB
	{
		sout << "AB-\n";
	}

	k = rmVertex(duonArr, 1, 2);
	for (int i = 0; i < k; ++i)
	{
		sout << "BC-\n";
	}

	k = rmVertex(duonArr, 2, 3);
	for (int i = 0; i < k; ++i)
	{
		sout << "CD-\n";
	}

	k = rmVertex(duonArr, 0, 3);
	for (int i = 0; i < k; ++i)
	{
		sout << "AD-\n";
	}

	k = rmVertex(duonArr, 4, 5);
	for (int i = 0; i < k; ++i)
	{
		sout << "EF-\n";
	}

	k = rmVertex(duonArr, 5, 6);
	for (int i = 0; i < k; ++i)
	{
		sout << "FG-\n";
	}

	k = rmVertex(duonArr, 6, 7);
	for (int i = 0; i < k; ++i)
	{
		sout << "GH-\n";
	}

	k = rmVertex(duonArr, 4, 7);
	for (int i = 0; i < k; ++i)
	{
		sout << "EH-\n";
	}

	k = rmVertex(duonArr, 0, 4);
	for (int i = 0; i < k; ++i)
	{
		sout << "AE-\n";
	}

	k = rmVertex(duonArr, 1, 5);
	for (int i = 0; i < k; ++i)
	{
		sout << "BF-\n";
	}

	k = rmVertex(duonArr, 2, 6);
	for (int i = 0; i < k; ++i)
	{
		sout << "CG-\n";
	}

	k = rmVertex(duonArr, 3, 7);
	for (int i = 0; i < k; ++i)
	{
		sout << "DH-\n";
	}

	bool isEmpty = true;

	for (int i = 0; i < vertexNum; ++i)
		if (duonArr[i])
		{
			isEmpty = false;
			break;
		}

	if (isEmpty)
	{
		cout << sout.str();
		return 0;
	}
	// now check for unaligned duons
	// EC: use DH		AG: use DH			BH: use AE		DF: use AE
	// 
	// A 0 B 1 C 2 D 3 E 4 F 5 G 6 H 7
	if (duonArr[0] && duonArr[6])
	{
		k = rmVertex(duonArr, 0, 6);
		for (int i = 0; i < k; ++i)
		{
			sout << "DH+\nAD-\nGH-\n";
		}
	}

	if (duonArr[4] && duonArr[2])
	{
		k = rmVertex(duonArr, 2, 4);
		for (int i = 0; i < k; ++i)
		{
			sout << "DH+\nEH-\nCD-\n";
		}
	}

	if (duonArr[3] && duonArr[5])
	{
		k = rmVertex(duonArr, 3, 5);
		for (int i = 0; i < k; ++i)
		{
			sout << "CG+\nDC-\nFG-\n";
		}
	}

	if (duonArr[1] && duonArr[7])
	{
		k = rmVertex(duonArr, 1, 7);
		for (int i = 0; i < k; ++i)
		{
			sout << "CG+\nGH-\nBC-\n";
		}
	}

	for (int i = 0; i < vertexNum; ++i)
		if (duonArr[i])
		{
			cout << "IMPOSSIBLE\n";
			return 0;
		}

	cout << sout.str();
	return 0;
}