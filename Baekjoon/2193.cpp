#include <stdio.h>
const int MAX = 91;

int main()
{
	unsigned long long store[MAX][2];	// ���ǿ� �´� n�ڸ� ������ ���� (0���� ������ ��� / 1�� ������ ���)
	int input;
	scanf("%d", &input);
	store[1][0] = 0;
	store[1][1] = 1;
	store[2][0] = 1;
	store[2][1] = 0;

	// n�ڸ� 0���� ������ ���� ���� = n-1�ڸ� ��ü ��(0�� 1�� ������ ��)�� ����
	// n�ڸ� 1�� ������ ���� ���� = n-1�ڸ� 0���� ������ ���� ����
	for (int i = 3; i <= input; i++)
	{
		store[i][0] = store[i - 1][0] + store[i - 1][1];
		store[i][1] = store[i - 1][0];
	}
	printf("%lld", store[input][0] + store[input][1]);
	return 0;
}