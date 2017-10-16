#include <iostream>
#include <queue>
using namespace std;
const int MAX = 101;
int N;
int result = 0;
int arr[MAX] = { 0, };
int finish[MAX] = { 0, }; // 1�̸� ����Ŭ �̷�� ���, 0�̸� ���� ������, -1�̸� ��ź, -2�̸� �Լ� ������ ���� ��.

void FindCycle(int n)
{
	queue<int> Que;	// ����Ŭ �ĺ��� ������� ����ִ� ť
	finish[n] = -2;
	Que.push(n);
	int now = arr[n];

	// ������ ���� ����Ŭ �ĺ����� ť�� �ִ´�.
	while (finish[now] == 0)
	{
		finish[now] = -2;
		Que.push(now);
		now = arr[now];
	}

	// while������ ����Ŭ�� �߰��ϸ�
	if (finish[now] == -2)
	{
		// ť �߿��� ����Ŭ ���� ���� �κ��� ��������.
		while (Que.front() != now)
		{
			finish[Que.front()] = -1;
			Que.pop();
		}
		// ����Ŭ�� �κ��� finish�� 1�� �����.
		while (!Que.empty())
		{
			finish[Que.front()] = 1;
			Que.pop();
			result++;
		}
	}
	// ����Ŭ�� ������ ť�� ���� ���� ��ź(-1)�̴�.
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