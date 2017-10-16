#include <iostream>
#include <queue>
using namespace std;
const int MAX = 101;
int N;
int result = 0;
int arr[MAX] = { 0, };
int finish[MAX] = { 0, }; // 1이면 사이클 이루는 요소, 0이면 아직 미판정, -1이면 파탄, -2이면 함수 내에서 판정 중.

void FindCycle(int n)
{
	queue<int> Que;	// 사이클 후보를 순서대로 집어넣는 큐
	finish[n] = -2;
	Que.push(n);
	int now = arr[n];

	// 매핑을 따라서 사이클 후보들을 큐에 넣는다.
	while (finish[now] == 0)
	{
		finish[now] = -2;
		Que.push(now);
		now = arr[now];
	}

	// while문에서 사이클을 발견하면
	if (finish[now] == -2)
	{
		// 큐 중에서 사이클 시작 전의 부분은 떼버린다.
		while (Que.front() != now)
		{
			finish[Que.front()] = -1;
			Que.pop();
		}
		// 사이클인 부분은 finish를 1로 만든다.
		while (!Que.empty())
		{
			finish[Que.front()] = 1;
			Que.pop();
			result++;
		}
	}
	// 사이클이 없으면 큐에 들어간건 전부 파탄(-1)이다.
	else
	{
		while (!Que.empty())
		{
			finish[Que.front()] = -1;
			Que.pop();
		}
	}
	return;
}

int main()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> arr[i];
	for (int i = 1; i <= N; i++)
	{
		if (finish[i] == 0)
			FindCycle(i);
	}
	cout << result << endl;
	for (int i = 1; i <= N; i++)
	{
		if (finish[i] == 1)
			cout << i << endl;
	}
	return 0;
}