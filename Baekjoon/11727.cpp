#include <cstdio>
const int MAX = 1001;
int arr[MAX] = { 0, 1, 3, 0, 0, };

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 3; i <= n; i++)
		arr[i] = ((arr[i - 2] * 2) + arr[i - 1]) % 10007;
	printf("%d", arr[n]);
	return 0;
}