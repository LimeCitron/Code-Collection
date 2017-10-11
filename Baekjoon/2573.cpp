#include <iostream>
#include <queue>
using namespace std;
const int MAX = 302;

int arr[MAX][MAX] = { 0, };
int issea[MAX][MAX] = { 0, };
int visited[MAX][MAX] = { 0, };
int dirm[4] = { -1, 0, 1, 0 };
int dirn[4] = { 0, 1, 0, -1 };

typedef struct point {
	int m; int n;
}Point;
int mapm, mapn;

queue<Point> Que;

void Initvisited()
{
	for (int i = 0; i <= mapm; i++)
	{
		for (int j = 0; j < mapn; j++)
			visited[i][j] = 0;
	}
	return;
}

int GetNumofBlock()
{
	int n = 0;
	for (int i = 1; i <= mapm; i++)
	{
		for (int j = 1; j <= mapn; j++)
		{
			if (arr[i][j] != 0)
				n++;
			else
				issea[i][j] = 1;
		}
	}
	return n;
}

// BFS�� �������� ����� ����� ã��, �� ����� ��� ���� ��ü ��ϰ� �ȸ����� ���ϰ� ��������!
bool BFS(int sm, int sn, int numblock)
{
	int num = 0;
	int tm, tn;
	Point temp;
	Point newpoint;
	temp.m = sm; temp.n = sn;
	Que.push(temp);
	visited[sm][sn] = 1;
	num++;
	while (!Que.empty())
	{
		temp = Que.front(); Que.pop();
		for (int i = 0; i < 4; i++)
		{
			tm = temp.m + dirm[i];
			tn = temp.n + dirn[i];
			if (arr[tm][tn] != 0 && visited[tm][tn] == 0)
			{
				visited[tm][tn] = 1;
				newpoint.m = tm; newpoint.n = tn;
				num++;
				Que.push(newpoint);
			}
		}
	}

	Initvisited();
	if (num == numblock)
		return true;
	else
		return false;
}


int main()
{
	int numblock;
	bool pan = true;
	int year = 0;
	int tm, tn;
	cin >> mapm >> mapn;
	for (int i = 1; i <= mapm; i++)
	{
		for (int j = 1; j <= mapn; j++)
			cin >> arr[i][j];
	}
	while (1)
	{
		numblock = GetNumofBlock();
		pan = true;
		if (numblock == 0)
		{
			year = 0;
			break;
		}

		// 1���� ������.... �ٴٰ� ������ ��ĥ ��. ������ �پ���.
		year++;
		for (int i = 1; i <= mapm; i++)
		{
			for (int j = 1; j <= mapn; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					tm = i + dirm[k];
					tn = j + dirn[k];
					if (issea[tm][tn] == 1 && arr[i][j] != 0)
						arr[i][j] = arr[i][j] - 1;
				}
			}
		}
		numblock = GetNumofBlock();

		// �ϴ� BFS�� ������ ���� ��Ƴ��� ������ ã�� �װ��� ���������� ����.
		for (int i = 1; i <= mapm; i++)
		{
			for (int j = 1; j <= mapn; j++)
			{
				if (arr[i][j] != 0)
				{
					pan = BFS(i, j, numblock);
					goto BreakTheDoubleLoop;
				}
			}
		}
	BreakTheDoubleLoop:
		if (pan == false)
			break;
	}

	cout << year;
	return 0;
}