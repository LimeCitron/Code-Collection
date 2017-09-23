#include <cstdio>
const int MAX = 1001;

int arr[MAX][MAX] = { 0, };
int value[MAX];

// arr[index1][index2]의 값을 찾기 위한 함수이다.
// arr[index1][i] 중 가장 크면서(가장 긴 길이의 수열을 포함하면서) 
// value[index2]보다 작은 값인 value[i]를 가지는(증가수열을 만족시키는) i를 찾는다. 
int FindMax(int index1, int index2)
{
	int temp = 0;
	for (int i = index1; i < index2; i++)
	{
		if ((arr[index1][i] > arr[index1][temp]) && (value[index2] > value[i]))
			temp = i;
	}
	return arr[index1][temp];
}

int main()
{
	int input;
	scanf("%d", &input);
	for (int i = 1; i <= input; i++)
		scanf("%d", &value[i]);
	int max = 1;

	// arr[i][j]는 i부터 시작하여 j에서 끝나는 가장 긴 수열의 길이를 저장한다.
	// max는 지금까지 나왔던 arr[i][j] 중 가장 큰 값을 저장한다. 
	for (int i = 1; i <= input; i++)
	{
		arr[i][i] = 1;
		for (int j = i + 1; j <= input; j++)
		{
			arr[i][j] = FindMax(i, j) + 1;
			if (arr[i][j] > max)
				max = arr[i][j];
		}
	}
	printf("%d", max);
	return 0;
}