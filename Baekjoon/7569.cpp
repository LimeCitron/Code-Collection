#include <iostream>
#include <queue>
using namespace std;
const int MAX = 102;
int Z, M, N;
int arr[MAX][MAX][MAX] = { -1, -1, };
int dirz[6] = { 1, -1, 0, 0, 0, 0 };
int dirm[6] = { 0, 0, -1, 0, 1, 0 };
int dirn[6] = { 0, 0, 0, 1, 0, -1 };

typedef struct point { int z; int m; int n; int time; }Point;

void InitArr()
{
	for (int z = 0; z < MAX; z++)
	{
		for (int n = 0; n < MAX; n++)
		{
			for (int m = 0; m < MAX; m++)
				arr[z][n][m] = -1;
		}
	}
}


int BFS()
{
	queue<Point> Que;
	Point temp;
	Point nexttemp;
	int maxtime = 0;
	// ó���� �;��ִ� �丶�� ��ǥ���� �־��ش�. 
	for (int z = 1; z <= Z; z++)
	{
		for (int n = 1; n <= N; n++)
		{
			for (int m = 1; m <= M; m++)
			{
				if (arr[z][n][m] == 1)
				{
					temp.z = z; temp.m = m; temp.n = n; temp.time = 0;
					Que.push(temp);
				}
				
			}
		}
	}

	// ť�� �̿��ؼ� BFS�� �����ش�.
	while (!Que.empty())
	{
		temp.z = Que.front().z; temp.m = Que.front().m; temp.n = Que.front().n; temp.time = Que.front().time; Que.pop();
		for (int i = 0; i < 6; i++)
		{
			nexttemp.z = temp.z + dirz[i]; nexttemp.m = temp.m + dirm[i]; nexttemp.n = temp.n + dirn[i]; nexttemp.time = temp.time + 1;
			if (arr[nexttemp.z][nexttemp.n][nexttemp.m] == 0)
			{
				if (nexttemp.time > maxtime)
					maxtime = nexttemp.time;
				arr[nexttemp.z][nexttemp.n][nexttemp.m] = 1;
				Que.push(nexttemp);
			}
		}
	}
	
	// ť�� �� ���ȴµ��� ���� ������ �丶�䰡 ������ -1�� ����
	for (int z = 1; z <= Z; z++)
	{
		for (int n = 1; n <= N; n++)
		{
			for (int m = 1; m <= M; m++)
			{
				if (arr[z][n][m] == 0)
					return -1;
			}
		}
	}

	return maxtime;
}

int main()
{
	InitArr();
	cin >> M >> N >> Z;
	for (int z = 1; z <= Z; z++)
	{
		for (int n = 1; n <= N; n++)
		{
			for (int m = 1; m <= M; m++)
				cin >> arr[z][n][m];
		}
	}

	cout << BFS();
	return 0;
}