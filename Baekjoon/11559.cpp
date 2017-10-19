#include <iostream>
#include <queue>
using namespace std;
const int MAXHEI = 14;
const int MAXWEI = 8;
char arr[MAXHEI][MAXWEI];	// R은 빨강, G는 초록, B는 파랑, P는 보라, Y는 노랑
int visited[MAXHEI][MAXWEI];	// 0은 미방문, 1은 방문 및 펑, -2는 임시.

int dirm[4] = { -1, 0, 1, 0 };
int dirn[4] = { 0, 1, 0, -1 };
queue<int> Que;				// 높이에는 10을 곱하며, 넓이에는 그냥 더해요.  

void NextStage()
{
	char temp;
	int k;
	for (int i = 1; i < (MAXHEI - 1); i++)
	{
		for (int j = 1; j < (MAXWEI - 1); j++)
		{
			if (visited[i][j] == 1)
				arr[i][j] = '.';
			visited[i][j] = 0;
		}
	}

	for (int i = 12; i >= 1; i--)
	{
		for (int j = 1; j < (MAXWEI - 1); j++)
		{
			if (arr[i][j] == '.')
			{
				for (k = i - 1; k >= 1; k--)
				{
					if (arr[k][j] != '.')
						break;
				}
				if (k >= 1)
				{
					temp = arr[i][j];
					arr[i][j] = arr[k][j];
					arr[k][j] = temp;
				}
			}
		}
	}
}

bool BFS(int i, int j)
{
	char temp = arr[i][j];
	int n = 1;
	int store[100] = { 0, };
	int tempm, tempn, nextm, nextn;
	Que.push(i * 10 + j);
	store[n] = i * 10 + j;
	visited[i][j] = -2;
	while (!Que.empty())
	{
		tempm = Que.front() / 10;  tempn = Que.front() % 10;  Que.pop();
		for (int k = 0; k <= 3; k++)
		{
			nextm = tempm + dirm[k]; nextn = tempn + dirn[k];
			if (arr[nextm][nextn] == temp && visited[nextm][nextn] == 0)
			{
				n++;
				visited[nextm][nextn] = -2;
				Que.push(nextm * 10 + nextn);
				store[n] = nextm * 10 + nextn;
			}
		}
	}

	if (n >= 4)
	{
		for (int k = 1; k <= n; k++)
			visited[store[k] / 10][store[k] % 10] = 1;
		return true;
	}
	else
		return false;
}

bool MakeHoobo()
{
	bool dochain = false;
	for (int i = 1; i < (MAXHEI-1); i++)
	{
		for (int j = 1; j < (MAXWEI-1); j++)
		{
			if (arr[i][j] != '.' && visited[i][j] == 0)
			{
				dochain = dochain | BFS(i, j);
			}
		}
	}
	NextStage();
	return dochain;
}

int main()
{
	int n = 0;
	for (int i = 0; i < MAXHEI; i++)
	{
		for (int j = 0; j < MAXWEI; j++)
			arr[i][j] = '.';
	}
	for (int i = 1; i < (MAXHEI - 1); i++)
	{
		for (int j = 1; j < (MAXWEI - 1); j++)
			cin >> arr[i][j];
	}
	while (MakeHoobo()) n++;
	cout << n;
	return 0;
}