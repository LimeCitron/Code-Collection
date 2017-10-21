#include <iostream>
#include <queue>
using namespace std;
const int MAX = 401;
int N;
int arr[MAX][MAX];

void BFS(int n)
{
	queue<int> Que;
	bool visited[MAX] = { false, };
	int temp;
	for (int i = 1; i <= N; i++)
	{
		if (arr[n][i] == 1)
		{
			Que.push(i);
			visited[i] = true;
		}
	}

	while (!Que.empty())
	{
		temp = Que.front(); Que.pop();
		for (int i = 1; i <= N; i++)
		{
			if (arr[temp][i] == 1 && visited[i] == false)
			{
				Que.push(i);
				visited[i] = true;
				arr[n][i] = 1;
			}
		}
	}
}

void Reverse()
{
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (arr[i][j] == 1)
				arr[j][i] = -1;
		}
	}
}

int main()
{
	int a, b, M;
	cin >> N >> M;
	for (int i = 1; i <= M; i++)
	{
		cin >> a >> b;
		arr[a][b] = 1;
	}
	for (int i = 1; i <= N; i++)
		BFS(i);
	Reverse();
	cin >> M;
	for (int i = 1; i <= M; i++)
	{
		cin >> a >> b;
		cout << -arr[a][b] << endl;
	}
	return 0;
}