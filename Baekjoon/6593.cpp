#include <iostream>
#include <queue>
using namespace std;
const int MAX = 32;
char arr[MAX][MAX][MAX];
char visit[MAX][MAX][MAX];   // v = 방문했음, n = 방문 안했음.

typedef struct point { int z; int m; int n; int time; }Point;
int dirz[6] = { 1,-1,0,0,0,0 };
int dirm[6] = { 0,0,-1,0,1,0 };
int dirn[6] = { 0,0,0,1,0,-1 };

int BFS(int z, int m, int n)
{
	queue<Point> Que;
	point temp, nexttemp;
	temp.z = z; temp.m = m; temp.n = n; temp.time = 0;
	Que.push(temp);
	visit[temp.z][temp.m][temp.n] = 'v';
	while (!Que.empty())
	{
		temp = Que.front(); Que.pop();
		for (int i = 0; i < 6; i++)
		{
			nexttemp.z = temp.z + dirz[i]; nexttemp.m = temp.m + dirm[i]; nexttemp.n = temp.n + dirn[i]; nexttemp.time = temp.time + 1;
			if (visit[nexttemp.z][nexttemp.m][nexttemp.n] == 'n' && arr[nexttemp.z][nexttemp.m][nexttemp.n] == '.')
			{
				visit[nexttemp.z][nexttemp.m][nexttemp.n] = 'v';
				Que.push(nexttemp);
			}
			if (arr[nexttemp.z][nexttemp.m][nexttemp.n] == 'E')
			{
				return nexttemp.time;
			}
		}
	}
	return -1;
}

int main()
{
	int z, m, n, result;

	while (true)
	{
		cin >> z >> m >> n;
		if (z == 0 && m == 0 && n == 0)
			break;

		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				for (int k = 0; k < MAX; k++)
				{
					arr[i][j][k] = '#';
					visit[i][j][k] = 'n';
				}
			}
		}

		for (int i = 1; i <= z; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				for (int k = 1; k <= n; k++)
					cin >> arr[i][j][k];
			}
		}

		for (int i = 1; i <= z; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				for (int k = 1; k <= n; k++)
				{
					if (arr[i][j][k] == 'S')
						result = BFS(i, j, k);
				}
			}
		}

		if (result == -1)
			cout << "Trapped!" << endl;
		else
			cout << "Escaped in " << result << " minute(s)." << endl;
	}
	return 0;
}