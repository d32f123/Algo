#include <iostream>

int swap(int *a, int *b) {
	int buff = *a;
	*a = *b;
	*b = buff;
}

int getNewIndex(int *a, int k, int ind, int el) {
	int res;
	for (res = ind; res + 1 < k && a[res + 1] == el; ++res)
		;
	return res;
}

int main() {
	int k, i = 0;
	// input
	std::cin >> k;

	int *a = new int[k];
	int *index = new int[k];

	for (i = 0; i < k; ++i) {
		std::cin >> a[i];
		index[i] = i + 1;
	}

	// sort
	for (i = 0; i < k; ++i)
		for (int j = k - 1; j > 0; --j)
			if (a[j - 1] < a[j]) {
				swap(&a[j], &a[j - 1]);
				swap(&index[j], &index[j - 1]);
			}
	// algorithm
	while (a[0] > 0) {
		--a[0];
		std::cout << index[0] << ' ';
		// if it is last element
		if ((k == 1) || (k > 1) && (a[1] == 0)) {
			continue;
		}

		i = getNewIndex(a, k, 0, a[0] + 1);

		if (i > 0) {
			swap(&a[0], &a[i]);
			swap(&ind[0], &ind[i]);
			continue;
		}

		--a[1];
		std::cout << ind[1] << ' ';
		i = getNewIndex(a, k, 1, a[1] + 1);
		swap(&a[1], &a[i]);
		swap(&ind[1], &ind[i]);
	}

	return 0;
}
