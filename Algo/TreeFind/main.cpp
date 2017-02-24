#include <iostream>

using namespace std;



struct NODE {	// —труктура "”зел" дл€ элементов дерева

	int elem;	// данные
	NODE *left;		// левое поддерево
	NODE *right;	// правое поддерево
	NODE(int el) { left = right = NULL; elem = el; }
};

bool search(NODE * node, int);
void print(NODE* cur);

NODE *root;	// глобальный корень дерева

void push(int el) { // вставка нового элемента в дерево

	if (!root) {
		root = new NODE(el);
		return;
	}

	NODE *buf;
	buf = root;

	while (true) {
		if (buf->elem >= el) {
			if (!buf->left) {
				buf->left = new NODE(el);
				return;
			}
			buf = buf->left;
		}
		else {
			if (!buf->right) {
				buf->right = new NODE(el);
				return;
			}
			buf = buf->right;
		}
	}
}

bool search(NODE * node, int key) {
	// Ё“” ‘”Ќ ÷»ё Ќ”∆Ќќ Ќјѕ»—ј“№
	if (!node)
		return false;
	if (node->elem == key)
	{
		return true;
	}
	else if (node->elem >= key && search(node->left, key))
		return true;
	else if (search(node->right, key))
		return true;
	return false;
}

void print(NODE* cur) {	// печать, симметричный обход
	if (cur->left) {
		print(cur->left);
	}
	cout << cur->elem << endl;
	if (cur->right) {
		print(cur->right);
	}
}

int main() {
	// дл€ отладки:
	// вывод дерева print(node) где node - указатель на корень дерева
	// поместить элемент в дерево push(element) прим. - элемент поместитс€ в нужное место.
	// шаблон предназначен дл€ отправки на проверку, дл€ отладки можете самосто€тельно
	// помещать свои элементы напр. push(5); push(20); push(50) и т.д. и работать со своими элементами

	// —амо дерево объ€влено глобально в коде
	int N;	// кол-во элементов
	cin >> N;
	for (int i = 0; i < N; i++) {	// ввод элементов в дерево
		int a;
		cin >> a;
		push(a);
	}
	cin >> N;	// искомый элемент
	if (search(root, N))
		cout << "Element \"" << N << "\" is found.";
	else
		cout << "Element \"" << N << "\" is not found."; // поиск с выводом
	return 0;
}