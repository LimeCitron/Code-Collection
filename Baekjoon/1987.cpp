#include <iostream>
using namespace std;
const int MAX = 22;

int result = 0;
int dirm[4] = { -1, 0, 1, 0 };
int dirn[4] = { 0, 1, 0, -1 };

char arr[MAX][MAX];
char List[100] = "1";

bool CheckList(char a, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (List[i] == a)
			return true;
	}
	return false;
}

void DFS(int num, int m, int n, int size)
{
	if (num > result)
		result = num;

	List[size] = arr[m][n];
	size++;

	for (int i = 0; i < 4; i++)
	{
		int tm = m + dirm[i];
		int tn = n + dirn[i];
		if (arr[tm][tn] >= 'A' && arr[tm][tn] <= 'Z' && !CheckList(arr[tm][tn], size))
		{
			DFS(num + 1, tm, tn, size);
		}
	}

	size--;

	return;
}

int main()
{

	int inm, inn;
	cin >> inm >> inn;

	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
			arr[i][j] = '1';
	}

	for (int i = 1; i <= inm; i++)
	{
		for (int j = 1; j <= inn; j++)
			cin >> arr[i][j];
	}
	DFS(1, 1, 1, 0);
	cout << result << endl;
	return 0;
}