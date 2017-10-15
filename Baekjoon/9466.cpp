#include <iostream>
#include <queue>
using namespace std;
const int MAX = 100001;

int arr[MAX] = { 0, };
// finish�� 0�̸� ���� �𸣴°�, 1�̸� �̹� ¥������, -1�̸� �̹� ��ź����, -2�� ����Ŭ ã�� �������� ������ ����. -2�� �Լ��� ����� �� -1�̳� 1�� �ٲ��.
int finish[MAX] = { 0, };
int N;

void InitFinish()
{
	for (int i = 1; i < MAX; i++)
		finish[i] = 0;
}

// ����Ŭ�� ã�� �����Դϴ�. 
void MakeTeam(int n)
{
	if (arr[n] == n)
	{
		finish[n] = 1;
		return;
	}

	// �� ť�� ���� ������ ���� ���ȴ�. ���� ���� while������ finish[arr[now]]�� -2��� 
	// �� arr[now]�� ������ �ִ� ť ���Һ��� ����Ŭ�̶�� �Ҹ���. �׷��� ������ �����ϱ� ���� ť�� ����Ͽ���.
	queue<int> list;
	finish[n] = -2;
	list.push(n);
	int now = n;

	// ������ ���� ������ ������ ���� ��� ���󰣴�. �� ���� 1�̳� -1�� ���� ��ź�� �������� -2�� ���� ����Ŭ�� �̷����.
	while (finish[arr[now]] == 0)
	{
		finish[arr[now]] = -2;
		list.push(arr[now]);
		now = arr[now];
	}

	// while ������ ������ -2�� ������ ����Ŭ�� �̷�� ��� 
	if (finish[arr[now]] == -2)
	{
		// ����Ŭ �ƴ� �κ��� ��ź.
		while (list.front() != arr[now])
		{
			finish[list.front()] = -1;
			list.pop();
		}
		// ����Ŭ�� �κ��� 1�� �ٲپ��ش�.
		while (!list.empty())
		{
			finish[list.front()] = 1;
			list.pop();
		}
	}

	// while ������ ������ 1�̳� -1�� ���� ��ź�� �̷�� ���
	else
	{
		while (!list.empty())
		{
			finish[list.front()] = -1;
			list.pop();
		}
	}
	
	return;
}

int main()
{
	int times;
	int result[1000] = { 0, };
	cin >> times;
	for (int i = 1; i <= times; i++)
	{
		cin >> N;
		for (int j = 1; j <= N; j++)
			cin >> arr[j];

		for (int j = 1; j <= N; j++)
		{
			if (finish[j] == 0)
				MakeTeam(j);
		}
		for (int j = 1; j <= N; j++)
		{
			if (finish[j] == -1)
				result[i]++;
		}
		InitFinish();
	}
	for (int i = 1; i <= times; i++)
		cout << result[i] << endl;

	return 0;
}