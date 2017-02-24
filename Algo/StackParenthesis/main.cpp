#include <iostream>
#include <string>
#define MAXSTACKSIZE 100

using namespace std;

bool IsStringRight(string&); // прототип функции проверки

struct STACK { // структура СТЕК
	char A[MAXSTACKSIZE]; // контейнер элементов
	int v; // индекс вершины стека
};

STACK S;

int main() {
	// Наальное состояние = Вершина стека = 0
	S.v = 0;

	string str;
	cin >> str; // ввод строки   
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
	// НАПИШИТЕ ЭТУ ФУНКЦИЮ
	// ВОЗВРАЩАЕТ ИСТИНУ В СЛУЧАЕ, ЕСЛИ СТРОКА "ПРАВИЛЬНАЯ"
	// ВОЗВРАЩАЕТ ЛОЖЬ, ЕСЛИ СТРОКА "НЕ ПРАВИЛЬНАЯ"
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