#include <cstdio>
const int MAX = 10001;

int Max(int a, int b) { return (a > b ? a : b); }
int FindMax(int arr[][2], int size)
{
	int result = 0;
	int temp;
	for (int i = 1; i <= size; i++)
	{
		temp = Max(arr[i][0], arr[i][1]);
		if (temp > result) result = temp;
	}
	return result;
}

int main()
{
	int arr[MAX][2] = { {0, 0}, };	// [n][0]은 비연속일 때, [n][1]은 연속일 때
	int size[MAX] = { 0, };
	int input;
	scanf("%d", &input);
	for (int i = 1; i <= input; i++)
		scanf("%d", &size[i]);
	arr[1][0] = size[1];
	arr[2][0] = size[2];
	arr[2][1] = size[1] + size[2];

	for (int i = 3; i <= input; i++)
	{
		arr[i][0] = FindMax(arr,i-2) + size[i];
		arr[i][1] = arr[i - 1][0] + size[i];
	}

	printf("%d", FindMax(arr, input));
	return 0;
}