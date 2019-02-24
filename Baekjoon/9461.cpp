#include <iostream>
using namespace std;

int main() {
	long long int arr[101] = { 0, 1, 1, 1, 2, };
	int input, T;
	cin >> T;
	for (int i = 5; i <= 100; i++) arr[i] = arr[i - 1] + arr[i - 5];
	for (int k = 0; k < T; k++) {
		cin >> input;
		cout << arr[input] << endl;
	}
	return 0;
}