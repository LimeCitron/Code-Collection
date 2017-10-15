#include <iostream>
#include <queue>
using namespace std;
const int MAX = 102;

int map[MAX][MAX] = { 0, };
int N;
int num_of_island = 1;

int dirm[4] = { -1,0,1,0 };
int dirn[4] = { 0,1,0,-1 };

int result = MAX * 2;

typedef struct point { int m; int n; int time; }Point;


void InitBFS(int m, int n)
{
	Point temp, nexttemp;
	queue<Point> Que;
	temp.m = m; temp.n = n;
	Que.push(temp);
	num_of_island++;
	map[temp.m][temp.n] = num_of_island;
	while (!Que.empty())
	{
		temp = Que.front(); Que.pop();
		for (int i = 0; i <= 3; i++)
		{
			nexttemp.m = temp.m + dirm[i];
			nexttemp.n = temp.n + dirn[i];
			if (nexttemp.m <= 0 || nexttemp.m > N || nexttemp.n <= 0 || nexttemp.n > N)
				continue;
			if (map[nexttemp.m][nexttemp.n] == 1)
			{
				map[nexttemp.m][nexttemp.n] = num_of_island;
				Que.push(nexttemp);
			}
		}
	}
	return;
}

void FindBFS(int m, int n)
{
	Point temp, nexttemp;
	queue<Point> Que;
	int visited[MAX][MAX] = { {0, },  };
	temp.m = m; temp.n = n; temp.time = 0;
	Que.push(temp);
	visited[m][n] = 1;
	int now = map[m][n];
	while (!Que.empty())
	{
		temp = Que.front(); Que.pop();
		if (result < temp.time)
			return;
		for (int i = 0; i <= 3; i++)
		{
			nexttemp.m = temp.m + dirm[i];
			nexttemp.n = temp.n + dirn[i];
			nexttemp.time = temp.time + 1;
			if (nexttemp.m <= 0 || nexttemp.m > N || nexttemp.n <= 0 || nexttemp.n > N)
				continue;
			if (map[nexttemp.m][nexttemp.n] == 0 && visited[nexttemp.m][nexttemp.n] == 0)
			{
				visited[nexttemp.m][nexttemp.n] = 1;
				Que.push(nexttemp);
			}
			if (map[nexttemp.m][nexttemp.n] != 0 && map[nexttemp.m][nexttemp.n] != now && visited[nexttemp.m][nexttemp.n] != 1)
			{
				result = temp.time;
				return;
			}
		}
	}
	return;
}

int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
			cin >> map[i][j];
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (map[i][j] == 1)
				InitBFS(i, j);
		}
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (map[i][j] != 0)
				FindBFS(i, j);
			
		}
	}

	cout << result;

	return 0;
}