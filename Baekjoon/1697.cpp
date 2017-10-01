#include <cstdio>
#include <queue>
using namespace std;

int start, fin;
int result = 100000;
int arr[100001] = { 0, };
queue<int> q;

int BFS()
{
	int temp;
	q.push(start);
	arr[start] = 1;
	while (1)
	{
		temp = q.front();
		q.pop();

		if (temp == fin)
			return arr[temp] - 1;
		if (temp * 2 <= 100000 && arr[temp * 2] == 0)
		{
			arr[temp * 2] = arr[temp] + 1;
			q.push(temp * 2);
		}
		if (temp + 1 <= 100000 && arr[temp + 1] == 0)
		{
			arr[temp + 1] = arr[temp] + 1;
			q.push(temp + 1);
		}
		if (temp - 1 >= 0 && arr[temp - 1] == 0)
		{
			arr[temp - 1] = arr[temp] + 1;
			q.push(temp - 1);
		}
	}
}

int main()
{
	scanf("%d %d", &start, &fin);
	if (start < fin)
		result = BFS();
	else
		result = start - fin;

	printf("%d", result);
	return 0;
}