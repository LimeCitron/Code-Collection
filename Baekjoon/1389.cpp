#include <iostream>
using namespace std;
const int MAX = 102;

int SumMin[MAX][MAX];	// i���� j������ �ּ� �Ÿ�

// �÷��̵� �ͼ��� �����ϴ� �Լ�
void FloidWarshall(int n)
{
	// �÷��̵� �ͼ� ����
	for (int k = 1; k <= n; k++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (SumMin[i][j] > SumMin[i][k] + SumMin[k][j])
					SumMin[i][j] = SumMin[i][k] + SumMin[k][j];
			}
		}
	}

	// �� ������ �ɺ� ������ ���� SumMin[i][101]�� ���س��´�.
	for (int i = 1; i <= n; i++)
	{
		int sum = 0;
		for (int j = 1; j <= n; j++)
			sum = SumMin[i][j] + sum;
		SumMin[i][MAX - 1] = sum;
	}

	return;
}

int main()
{
	// SumMin �迭�� �ʱ�ȭ �Ѵ�. �ڱ� �ڽ��� ��δ� 0���� �ʱ�ȭ�Ѵ�. 
	for (int i = 1; i <= MAX; i++)
	{
		for (int j = 1; j <= MAX; j++)
			SumMin[i][j] = 100000;
	}

	for (int i = 1; i <= MAX; i++)
		SumMin[i][i] = 0;

	int n, cor, t1, t2;
	cin >> n >> cor;

	// �Է� ���� ��ε��� ��������(�Ÿ��� 1����) SumMin�� �Է��Ѵ�.
	for (int i = 0; i < cor; i++)
	{
		cin >> t1 >> t2;
		SumMin[t1][t2] = 1;
		SumMin[t2][t1] = 1;
	}
	FloidWarshall(n);

	int result = 1000000;
	int save = 0;
	for (int i = 1; i <= n; i++)
	{
		if (result > SumMin[i][MAX - 1])
		{
			save = i;
			result = SumMin[i][MAX - 1];
		}
	}
	cout << save;
	return 0;
}