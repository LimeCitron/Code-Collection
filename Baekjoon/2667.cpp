#include <iostream>
#include <queue>
using namespace std;
const int MAX = 27;
char arr[MAX][MAX];		// 지도 판때기
int result[1000] = { 0, };		// result[0]은 단지의 개수, result[i]는 각 단지의 집 개수

typedef struct point {
	int m; 
	int n;
}Point;

int dirm[4] = { -1, 0, 1, 0 };	// 위 오른 아래 왼
int dirn[4] = { 0, 1, 0, -1 };

queue<Point> que;

void BFS(int m, int n)
{
	Point temp;
	result[0]++;		// 새로운 단지를 발견했으니 단지의 갯수 증가
	result[result[0]] = 0;		// 그 새로운 단지의 번호를 매기고 몇개의 집이 있는지 센다.
	temp.m = m; 
	temp.n = n;
	que.push(temp);

	while (que.empty() != true)
	{
		temp = que.front();
		que.pop();
		result[result[0]]++;
		arr[temp.m][temp.n] = '0';
		//현재 위치를 기준으로 4방향 찾기.
		for (int i = 0; i < 4; i++)
		{
			if (arr[temp.m + dirm[i]][temp.n + dirn[i]] == '1')
			{
				Point brandnew;
				brandnew.m = temp.m + dirm[i];
				brandnew.n = temp.n + dirn[i];
				que.push(brandnew);
				arr[temp.m + dirm[i]][temp.n + dirn[i]] = '0';
			}
		}
	}
}

void Sort()
{
	for (int i = 1; i <= result[0]; i++)
	{
		for (int j = i + 1; j <= result[0]; j++)
		{
			if (result[i] > result[j])
			{
				int temp = result[i];
				result[i] = result[j];
				result[j] = temp;
			}
		}
	}
}

int main()
{
	int input;
	cin >> input;
	for (int i = 1; i <= input; i++)
	{
		for (int j = 1; j <= input; j++)
		{
			cin >> arr[i][j];
		}
	}
				
	// arr[i][j]가 1인 곳이면 새로운 단지의 시작이니까 그곳을 시작으로 BFS 돌리기.
	for (int i = 1; i <= input; i++)
	{
		for (int j = 1; j <= input; j++)
		{
			if (arr[i][j] == '1')
				BFS(i, j);
		}
	}
	
	Sort();
	for (int i = 0; i <= result[0]; i++)
		cout << result[i] << endl;
	return 0;
}