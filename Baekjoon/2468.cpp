#include <iostream>
#include <queue>
using namespace std;
const int MAX = 102;
int arr[MAX][MAX];
int visited[MAX][MAX];	// 0 안방문, 1 방문
int N;
int dirm[4] = { -1,0,1,0 };
int dirn[4] = { 0,1,0,-1 };

void BFS(int m, int n, int zamgim)
{
	queue<int> Que;
	int tempm, tempn, nextm, nextn;
	visited[m][n] = 1;
	Que.push(m * 1000 + n);
	while (!Que.empty())
	{
		tempm = Que.front() / 1000; tempn = Que.front() % 1000; Que.pop();
		for (int i = 0; i <= 3; i++)
		{
			nextm = tempm + dirm[i]; nextn = tempn + dirn[i];
			if (arr[nextm][nextn] > zamgim && visited[nextm][nextn] == 0)
			{
				visited[nextm][nextn] = 1;
				Que.push(nextm * 1000 + nextn);
			}
		}
	}
}

void Init()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			visited[i][j] = 0;
	}
}

int main()
{
	int result = 0;
	int checknum;
	int zamgim = 0;
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
			visited[i][j] = 1;
	}
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			cin >> arr[i][j];
	}

	while (zamgim <= 100)
	{
		checknum = 0;
		Init();
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (arr[i][j] > zamgim && visited[i][j] == 0)
				{
					BFS(i,j,zamgim);
					checknum++;
				}
			}
		}
		if (result < checknum)
			result = checknum;
		zamgim++;
	}
	cout << result;
	return 0;
}
