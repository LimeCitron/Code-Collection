#include <iostream>
using namespace std;
const int MAX = 101;

int dp[MAX][MAX];
int N;

void FloidWarshall()
{
	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (dp[i][j] > dp[i][k] + dp[k][j])
				{
					dp[i][j] = dp[i][k] + dp[k][j];
				}
			}
		}
	}
}

int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> dp[i][j];
			if (dp[i][j] == 0)
				dp[i][j] = 100000;
		}
	}
	FloidWarshall();

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (dp[i][j] < 100000)
				cout << "1 ";
			else
				cout << "0 ";
		}
		cout << endl;
	}
	return 0;
}