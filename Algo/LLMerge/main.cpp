#include <iostream>
#include <limits.h>

using namespace std;

struct NODE {
	int Number;
	NODE *Next;
};

NODE * MakeList(int*, int);
NODE *JoinTwoList(NODE*, NODE*);

int main() {
	int Arr1[] = { 2,3,5,9 };
	int Arr2[] = { 4,6,7,11,16 };
	NODE *Head1, *Head2;
	Head1 = MakeList(Arr1, sizeof(Arr1) / sizeof(int));
	Head2 = MakeList(Arr2, sizeof(Arr2) / sizeof(int));
	NODE *Head = JoinTwoList(Head1, Head2);
	cout << "Head";
	for (NODE* p1 = Head->Next; p1 != NULL; p1 = p1->Next) {
		cout << " -> " << p1->Number;
	}
	return 0;
}


NODE *JoinTwoList(NODE *Head1, NODE *Head2) {
	// ¬ыполнить сли€ние списков с головами Head1 и Head2
	// ‘ункци€ возвращает указатель на голову списка,
	// €вл€ющегос€ результатом сли€ни€
	// ............................
	NODE * Head3 = new NODE, * a = Head1->Next, * b = Head2->Next, * c = Head3;
	Head3->Next = NULL;
	Head3->Number = INT_MAX;
	while (a != NULL || b != NULL)
	{
		int num;
		c->Next = new NODE;
		c = c->Next;
		if (a == NULL)
		{
			num = b->Number;
			b = b->Next;
		}
		else if (b == NULL)
		{
			num = a->Number;
			a = a->Next;
		}
		else if (a->Number > b->Number)
		{
			num = b->Number;
			b = b->Next;
		}
		else
		{
			num = a->Number;
			a = a->Next;
		}
		c->Number = num;
		c->Next = NULL;
	}
	return Head3;
}



NODE * MakeList(int Arr[], int n) {
	// Ёта функци€ создаЄт один список
	// Arr - массив чисел, которые должны быть помещены в список
	// n - их количество
	NODE *Head = new NODE, *x;
	Head->Next = NULL; //явно указываем на NULL
	Head->Number = INT_MAX; // ”словное значение головы
	x = Head;
	// —оздание собственно списка
	for (int i = 0; i < n; i++) {
		x->Next = new NODE;
		x = x->Next;
		x->Number = Arr[i];
		x->Next = NULL;
	}
	return Head;
}