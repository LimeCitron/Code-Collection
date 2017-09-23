#include <cstdio>
const int MAX = 101;

int main()
{
	int arr[MAX][10] = { 0, };
	int input;
	scanf("%d", &input);
	arr[1][0] = 0;
	for (int i = 1; i < 10; i++)
		arr[1][i] = 1;

	for (int i = 2; i <= input; i++)
	{
		arr[i][0] = arr[i - 1][1] % 1000000000;
		for (int j = 1; j <= 8; j++)
			arr[i][j] = (arr[i - 1][j - 1] + arr[i - 1][j + 1]) % 1000000000;
		arr[i][9] = arr[i - 1][8] % 1000000000;
	}

	int result = 0;
	for (int i = 0; i < 10; i++)
		result = (result + arr[input][i]) % 1000000000;
	printf("%d", result);
	return 0;
}