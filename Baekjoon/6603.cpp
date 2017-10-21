#include <iostream>
using namespace std;

int N;
int arr[15];
int hubo[15];
bool visited[15];
void DFS(int n, int prev)
{
	if (n == 6)
	{
		for (int i = 0; i < 6; i++)
			cout << hubo[i] << " ";
		cout << endl;
		return;
	}

	for (int i = n; i < N; i++)
	{
		if (visited[i] == false && prev < arr[i])
		{
			visited[i] = true;
			hubo[n] = arr[i];
			DFS(n + 1, arr[i]);
			visited[i] = false;
		}
	}
}
int main()
{
	while (1)
	{
		cin >> N;
		if (N == 0)
			break;
		for (int i = 0; i < N; i++)
			cin >> arr[i];
		DFS(0,0);
		cout << endl;
	}
	return 0;
}