#include <iostream>
#include <queue>
using namespace std;
const int MAX = 102;
int arrx[MAX];
int arry[MAX];
int visited[MAX] = { 0, };
int N;

int abs(int a) { return a < 0 ? -a : a; }
void Initvisited(){ for (int i = 0; i < MAX; i++)	visited[i] = 0; }

bool BFS()
{
	queue<int> Que;
	visited[MAX - 1] = 1;
	Que.push(MAX - 1);

	int nowx;
	int nowy;
	while (!Que.empty())
	{
		nowx = arrx[Que.front()]; nowy = arry[Que.front()]; Que.pop();
		if (abs(arrx[0] - nowx) + abs(arry[0] - nowy) <= 1000)
			return true;

		for (int i = 1; i <= N; i++)
		{
			if (visited[i] == 0 && abs(arrx[i] - nowx) + abs(arry[i] - nowy) <= 1000)
			{
				visited[i] = 1;
				Que.push(i);
			}
		}
	}
	return false;
}

int main()
{
	int times;
	cin >> times;
	for (int k = 1; k <= times; k++)
	{
		cin >> N;
		cin >> arrx[MAX - 1] >> arry[MAX - 1];
		for (int i = 1; i <= N; i++)
			cin >> arrx[i] >> arry[i];
		cin >> arrx[0] >> arry[0];

		if(BFS() == true)
			cout << "happy" << endl;
		else
			cout << "sad" << endl;
		Initvisited();
	}
	return 0;
}