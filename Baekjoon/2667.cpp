#include <iostream>
#include <queue>
using namespace std;
const int MAX = 27;
char arr[MAX][MAX];		// ���� �Ƕ���
int result[1000] = { 0, };		// result[0]�� ������ ����, result[i]�� �� ������ �� ����

typedef struct point {
	int m; 
	int n;
}Point;

int dirm[4] = { -1, 0, 1, 0 };	// �� ���� �Ʒ� ��
int dirn[4] = { 0, 1, 0, -1 };

queue<Point> que;

void BFS(int m, int n)
{
	Point temp;
	result[0]++;		// ���ο� ������ �߰������� ������ ���� ����
	result[result[0]] = 0;		// �� ���ο� ������ ��ȣ�� �ű�� ��� ���� �ִ��� ����.
	temp.m = m; 
	temp.n = n;
	que.push(temp);

	while (que.empty() != true)
	{
		temp = que.front();
		que.pop();
		result[result[0]]++;
		arr[temp.m][temp.n] = '0';
		//���� ��ġ�� �������� 4���� ã��.
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
				
	// arr[i][j]�� 1�� ���̸� ���ο� ������ �����̴ϱ� �װ��� �������� BFS ������.
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