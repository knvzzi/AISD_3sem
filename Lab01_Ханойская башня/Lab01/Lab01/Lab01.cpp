#include <iostream>
using namespace std;

void hanoi(int i, int k, int N, int tmp) {
	if (N == 1) {
		cout << " 1. Переместить диск " << N << " со стержня " << i << " на стержень " << k << endl;
		return;
	}
	else {
		hanoi(i, tmp, N - 1, k);
		cout << "2. Переместить диск " << N << " со стержня " << i << " на стержень " << k << endl;
		hanoi(tmp, k, N - 1, i);
	}
}

int main() {

	setlocale(LC_CTYPE, "rus");

	int N, k; // N - 4; k - 3
	cout << "Ввежите количество дисков N -";
	cin >> N;
	cout << "Ввежите количество стержней k -";
	cin >> k;

	if (N < 1 || k < 3) {
		cout << "Некорректные данные";
		return 1;
	}

	hanoi(1, k, N, 2);
	return 0;
}
