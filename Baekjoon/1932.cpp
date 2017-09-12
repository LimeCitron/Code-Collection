#include <stdio.h>
const int MAX = 502;
int arr[MAX][MAX] = { 0, };

// 배열 중 가장 큰 값 반환
int GetMax(int a[], int size)
{
	int result = 0;
	for (int i = 1; i <= size; i++)
	{
		if (a[i] > result)
			result = a[i];
	}
	return result;
}

int Max(int a, int b) { return (a > b ? a : b); }

int main()
{
	int input;
	scanf("%d", &input);
	for (int i = 1; i <= input; i++)
	{
		for (int j = 1; j <= i; j++)
			scanf("%d", &arr[i][j]);
	}

	for (int i = 1; i <= input; i++)
	{
		for (int j = 1; j <= i; j++)
			arr[i][j] = Max(arr[i - 1][j - 1], arr[i - 1][j]) + arr[i][j];
	}

	printf("%d", GetMax(arr[input],input));
	return 0;
}