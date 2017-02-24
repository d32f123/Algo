#include <iostream>
#include <string>
#define MAXSTACKSIZE 100

using namespace std;

bool IsStringRight(string&); // �������� ������� ��������

struct STACK { // ��������� ����
	char A[MAXSTACKSIZE]; // ��������� ���������
	int v; // ������ ������� �����
};

STACK S;

int main() {
	// �������� ��������� = ������� ����� = 0
	S.v = 0;

	string str;
	cin >> str; // ���� ������   
	if (IsStringRight(str)) {
		cout << "String is right";
	}
	else {
		cout << "String is wrong";
	}
	return 0;
}

void push(char x)
{
	S.A[S.v++] = x;
}

char pop()
{
	return S.A[--S.v];
}

bool IsStringRight(string& str) {
	// �������� ��� �������
	// ���������� ������ � ������, ���� ������ "����������"
	// ���������� ����, ���� ������ "�� ����������"
	int i = 0;
	while (str[i])
	{
		switch (str[i])
		{
		case '(':
			push('(');
			break;
		case '[':
			push('[');
			break;
		case '{':
			push('{');
			break;
		case ')':
			if (pop() != '(')
				return false;
			break;
		case ']':
			if (pop() != '[')
				return false;
			break;
		case '}':
			if (pop() != '{')
				return false;
			break;
		}
		++i;
	}
	return true;
}