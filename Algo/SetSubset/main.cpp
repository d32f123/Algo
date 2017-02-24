#include <iostream>
#include <string>

#define MAXSETSIZE 100
#define DIGIT 0
#define COMMA 2
#define DEFIS 3
#define BLANK 4
#define OTHER 5

using namespace std;

//��������� ��������� �� �������
struct SETINARRAY {
	int m[MAXSETSIZE]; // ������, �������� �������� ���������
	int n; // �������������� ����� ��-��� � ���������
};

// ��������� �������
void Union(SETINARRAY &A, SETINARRAY &B, SETINARRAY &Res); // Res = A union B
void Cross(SETINARRAY &A, SETINARRAY &B, SETINARRAY &Res);// Res = A cross B.
void Difference(SETINARRAY &A, SETINARRAY &B, SETINARRAY &Res); // �������� Res = A \ B.
short SymClass(char z); //������������� ��������
int StringToIntArray(string &p, int *r); // ������ ������ � ������ ����� �����
string ArrayToString(int *p, int np); // ��� ������
int binary_search(int * A, int n, int x);

int main() { // ����� ����� � ���������
	SETINARRAY X, Y, Z;
	string s;
	cin >> s;
	X.n = StringToIntArray(s, X.m);
	cin >> s;
	Y.n = StringToIntArray(s, Y.m);

	Union(X, Y, Z);
	cout << ArrayToString(Z.m, Z.n);
	Cross(X, Y, Z);
	cout << "\n" + ArrayToString(Z.m, Z.n);
	Difference(X, Y, Z);
	cout << "\n" + ArrayToString(Z.m, Z.n);
	return 0;
}

void Union(SETINARRAY &A, SETINARRAY &B, SETINARRAY &Res) {
	// �������� ����
	// ������� ��������� ����������� �������� a,b
	// ��������� ���������� � *Res
	// �������������� ��� ��������� �� �������� ����������
	int i = 0, j = 0, k = 0;
	while (i != A.n || j != B.n)
	{
		if (i == A.n)
		{
			Res.m[k++] = B.m[j++];
		}
		else if (j == B.n)
		{
			Res.m[k++] = A.m[i++];
		}
		else if (A.m[i] == B.m[j])
		{
			Res.m[k++] = A.m[i++];
			++j;
		}
		else if (A.m[i] < B.m[j])
		{
			Res.m[k++] = A.m[i++];
		}
		else
		{
			Res.m[k++] = B.m[j++];
		}
	}
	Res.n = k;
}

int binary_search(int * A, int n, int x)
{
	int left = 0, right = n - 1, m;
	if (x > A[right] || x < A[left])
		return -1;
	if (x == A[right])
		return n - 1;
	if (x == A[left])
		return 0;
	while (true)
	{
		if (left == right)
		{
			if (A[left] != x)
				return -1;
			return left;
		}
		m = (left + right) / 2;
		if (x == A[m])
			return m;
		else if (m == left || m == right)
		{
			return -1;
		}
		else if (x > A[m])
			left = m;
		else
			right = m;
	}
}

void Cross(SETINARRAY &A, SETINARRAY &B, SETINARRAY &Res) {
	// �������� ����
	// ������� ��������� ����������� �������� a,b
	// ��������� ���������� � *Res
	int k = 0;
	for (int i = 0; i < A.n; ++i)
	{
		if (binary_search(B.m, B.n, A.m[i]) != -1)
		{
			Res.m[k++] = A.m[i];
		}
	}
	Res.n = k;
}

void Difference(SETINARRAY &A, SETINARRAY &B, SETINARRAY &Res) {
	// �������� ����
	// ������� ��������� �������� �������� a,b
	// ��������� ���������� � *Res
	int k = 0;
	for (int i = 0; i < A.n; ++i)
	{
		if (binary_search(B.m, B.n, A.m[i]) == -1)
		{
			Res.m[k++] = A.m[i];
		}
	}
	Res.n = k;
}

short SymClass(char z) {
	if (z >= '0' && z <= '9') {
		return DIGIT;
	}
	if (z == ',') {
		return COMMA;
	}
	if (z == '-') {
		return DEFIS;
	}
	if (z == ' ') {
		return BLANK;
	}
	return OTHER;
}

int StringToIntArray(string &p, int *r) {
	int k, p1 = -1, p2 = -1;
	char buf[20];
	short sClass;
	int i = 0; // ����� ������� ����������� �����
	int n = 0; // ����� ������� (������� ����� p)
	int LastPunkt = -1; // ��������� ������ �� DEFIS ��� COMMA
						// -1 ������ ��������

	if (!p.size()) {
		return 0;
	}
	for (int j = 0; j < p.size(); j++) {
		sClass = SymClass(p[j]);
		switch (sClass) {
		case DIGIT:
			buf[i++] = p[j];
			break;
		case COMMA:
			buf[i] = '\0';
			if (LastPunkt == -1 || LastPunkt == COMMA) {
				p1 = atoi(buf);
				r[n++] = p1;
			}
			if (LastPunkt == DEFIS) {
				p2 = atoi(buf);
				if (p1 == -1 || p2 == -1) {
					return -1;
				}
				if (p2<p1) {
					return -1;
				}
				for (k = p1; k <= p2; k++) {
					r[n++] = k;
				}
				p1 = p2 = -1;
			}
			i = 0;
			LastPunkt = COMMA;
			break;
		case DEFIS:
			buf[i] = '\0';
			p1 = atoi(buf);
			p2 = -1;
			LastPunkt = DEFIS;
			i = 0;
			break;
		case BLANK:
			break;
		default:
			return -1;
		} // switch
	}
	buf[i] = '\0';
	if (LastPunkt == -1 || LastPunkt == COMMA) {
		p1 = atoi(buf);
		r[n++] = p1;
	}
	if (LastPunkt == DEFIS) {
		p2 = atoi(buf);
		if (p1 == -1 || p2 == -1) {
			return -1;
		}
		for (k = p1; k <= p2; k++) {
			r[n++] = k;
		}
	}
	// ����������
	bool b = true;
	int t;
	while (b) {
		b = false;
		for (i = 0; i<n - 1; i++) {
			if (r[i]>r[i + 1]) {
				t = r[i];
				r[i] = r[i + 1];
				r[i + 1] = t;
				b = true;
			}
		}
	}
	return n;
}

string ArrayToString(int *p, int np) {
	if (!np) {
		return "Empty";
	}
	int i, cnt = 0;
	string s = to_string(p[0]);
	bool DiffOne, SerStart = false, fOne = false;
	for (i = 1; i < np; i++) {
		DiffOne = (p[i] - p[i - 1] == 1);
		if (!SerStart && DiffOne) {
			SerStart = true;
		}
		if (DiffOne) {
			cnt++;
			if (i == np - 1) {
				if (cnt > 1) {
					s += "-";
				}
				else {
					s += ",";
				}
				s += to_string(p[i]);
			}
			else if (((p[i + 1] - p[i]) != 1) && cnt == 1) {
				s += "," + to_string(p[i]);
			}
		}
		else {
			if (cnt <= 1) {
				s += ",";
				s += to_string(p[i]);
			}
			else {
				fOne = false;
				s += "-";
				s += to_string(p[i - 1]);
				s += ",";
				s += to_string(p[i]);
				cnt = 0;
			}
		}
	}
	return s;
}
