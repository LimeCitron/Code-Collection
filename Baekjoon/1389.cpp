#include <iostream>
using namespace std;
const int MAX = 102;

int SumMin[MAX][MAX];	// i부터 j까지의 최소 거리

// 플로이드 와샬을 적용하는 함수
void FloidWarshall(int n)
{
	// 플로이드 와샬 본문
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

	// 각 정점의 케빈 베이컨 값을 SumMin[i][101]에 구해놓는다.
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
	// SumMin 배열을 초기화 한다. 자기 자신의 경로는 0으로 초기화한다. 
	for (int i = 1; i <= MAX; i++)
	{
		for (int j = 1; j <= MAX; j++)
			SumMin[i][j] = 100000;
	}

	for (int i = 1; i <= MAX; i++)
		SumMin[i][i] = 0;

	int n, cor, t1, t2;
	cin >> n >> cor;

	// 입력 받은 경로들이 존재함을(거리가 1임을) SumMin에 입력한다.
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