/*
예를 들어 동전이 2,3,5가 있다고 하면 아래와 같다.
	[2]	[3]	[5]
[1]	 0
[2]	 1
[3]	 0	 1
[4]	 1	 0
[5]	 0	 1	 1
[6]	 1	 1	 0
[7]	 0	 0	 1
[8]	 1	 1	 1

arr[i][j] = arr[i - arr[0][j]][1] + arr[i - arr[0][j]][2] + ... + arr[i - arr[0][j]][j]이다.
예를 들어

arr[8][3] = arr[3][1] + arr[3][2] + arr[3][3]이다. 

와 이거 어떻게 생각해낸거지 신기하다.
*/

/*

#include <cstdio>
const int NUMMAX = 10001;
const int KINDMAX = 101;
int arr[NUMMAX][KINDMAX] = { 0, };
int n, k;

void SortHead()
{
	int temp = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = i + 1; j <= n; j++)
		{
			if (arr[0][i] > arr[0][j])
			{
				temp = arr[0][i];
				arr[0][i] = arr[0][j];
				arr[0][j] = temp;
			}
		}
	}
	for (int i = 1; i <= n; i++)
		arr[arr[0][i]][i] = 1;
	return;
}

int main()
{
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[0][i]);
	SortHead();

	for (int i = 2; i <= k; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i - arr[0][j] <= 0)
				break;

			for (int k = 1; k <= j; k++)
				arr[i][j] = arr[i][j] + arr[i - arr[0][j]][k];
		}
	}

	int result = 0;
	for (int i = 1; i <= n; i++)
		result = result + arr[k][i];
	printf("%d", result);

	return 0;
}