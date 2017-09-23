#include <cstdio>
const int MAX = 1001;

int arr[MAX][MAX] = { 0, };
int value[MAX];

// arr[index1][index2]�� ���� ã�� ���� �Լ��̴�.
// arr[index1][i] �� ���� ũ�鼭(���� �� ������ ������ �����ϸ鼭) 
// value[index2]���� ���� ���� value[i]�� ������(���������� ������Ű��) i�� ã�´�. 
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

	// arr[i][j]�� i���� �����Ͽ� j���� ������ ���� �� ������ ���̸� �����Ѵ�.
	// max�� ���ݱ��� ���Դ� arr[i][j] �� ���� ū ���� �����Ѵ�. 
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