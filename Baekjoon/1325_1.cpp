#include <iostream>
#include <queue>
using namespace std;
const int MAX = 10001;
int result[MAX];
int resultnum = 0;

typedef struct linked {
	struct linked* link;
	int value;
}Linked;

Linked arr[MAX];

Linked* CreateNode(int value)
{
	Linked* temp = new Linked();
	temp->link = NULL;
	temp->value = value;
	return temp;
}

void BFS(int n)
{
	int num = 0;
	int next;
	Linked* temp;
	bool visited[MAX] = { false, };
	queue<int> Que;
	Que.push(n);
	visited[n] = true;
	num++;
	while (!Que.empty())
	{
		temp = &arr[Que.front()]; Que.pop();
		while (temp->link != NULL)
		{
			temp = temp->link;
			next = temp->value;
			if (visited[next] == false)
			{
				Que.push(next);
				visited[next] = true;
				num++;
			}
		}
	}
	
	if (result[0] < num)
	{
		result[0] = num;
		result[1] = n;
		resultnum = 1;
	}
	else if (result[0] == num)
	{
		result[++resultnum] = n;
	}
}

void Sort()
{
	int temp;
	for (int i = 1; i <= resultnum; i++)
	{
		for (int j = i + 1; j <= resultnum; j++)
		{
			if (result[i] > result[j])
			{
				temp = result[i];
				result[i] = result[j];
				result[j] = temp;
			}
		}
	}
}

int main()
{
	int N, M;
	int slave, master;
	Linked* temp;
	cin >> N >> M;
	for (int i = 1; i <= M; i++)
	{
		cin >> slave >> master;
		temp = &arr[master];
		while (temp->link != NULL)
			temp = temp->link;
		temp->link = CreateNode(slave);
	}

	for (int i = 1; i <= N; i++)
		BFS(i);
	Sort();
	for (int i = 1; i <= resultnum; i++)
		cout << result[i] << " ";
	return 0;
}