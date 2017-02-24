#include <iostream>

using namespace std;



struct NODE {	// ��������� "����" ��� ��������� ������

	int elem;	// ������
	NODE *left;		// ����� ���������
	NODE *right;	// ������ ���������
	NODE(int el) { left = right = NULL; elem = el; }
};

bool search(NODE * node, int);
void print(NODE* cur);

NODE *root;	// ���������� ������ ������

void push(int el) { // ������� ������ �������� � ������

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
	// ��� ������� ����� ��������
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

void print(NODE* cur) {	// ������, ������������ �����
	if (cur->left) {
		print(cur->left);
	}
	cout << cur->elem << endl;
	if (cur->right) {
		print(cur->right);
	}
}

int main() {
	// ��� �������:
	// ����� ������ print(node) ��� node - ��������� �� ������ ������
	// ��������� ������� � ������ push(element) ����. - ������� ���������� � ������ �����.
	// ������ ������������ ��� �������� �� ��������, ��� ������� ������ ��������������
	// �������� ���� �������� ����. push(5); push(20); push(50) � �.�. � �������� �� ������ ����������

	// ���� ������ ��������� ��������� � ����
	int N;	// ���-�� ���������
	cin >> N;
	for (int i = 0; i < N; i++) {	// ���� ��������� � ������
		int a;
		cin >> a;
		push(a);
	}
	cin >> N;	// ������� �������
	if (search(root, N))
		cout << "Element \"" << N << "\" is found.";
	else
		cout << "Element \"" << N << "\" is not found."; // ����� � �������
	return 0;
}