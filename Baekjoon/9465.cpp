#include <stdio.h>
using namespace std;

const int MAX = 100005;
int arr[2][MAX] = { 0, };
int result[2][MAX] = { 0, };

int Max(int a, int b) { return (a > b ? a : b); }

int Dynamic(int n) {
	int re1, re2, max;
	result[0][1] = arr[0][1];	
	result[1][1] = arr[1][1];	
	max = Max(result[0][1], result[1][1]);

	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= 2; j++) {
			re1 = result[j % 2][i - 2] + arr[j / 2][i];
			re2 = result[j % 2][i - 1] + arr[j / 2][i];
			result[j / 2][i] = Max(re1, re2);
			max = Max(max, result[j / 2][i]);
		}
	}
	return max;
}

int main(){
	int T, n;
	scanf("%d", &T);
	for (int k = 0; k < T; k++) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &arr[0][i]);
		for (int i = 1; i <= n; i++) scanf("%d", &arr[1][i]);
		printf("%d\n", Dynamic(n));
	}
	return 0;
}