#include <iostream>
#include <queue>
using namespace std;
const int MAX = 102;

int arr[MAX][MAX] = { 0, };
int result[1000] = { 0, };
queue<int> Xque;
queue<int> Yque;

int dirx[4] = { 0, 1, 0, -1 };
int diry[4] = { 1, 0, -1, 0 };

void BFS(int x, int y)
{
	int tempx, tempy;	

	arr[y][x] = 1;
	result[0]++;
	result[result[0]]++;
	Xque.push(x);
	Yque.push(y);

	while (!Xque.empty())
	{
		tempx = Xque.front(); Xque.pop();
		tempy = Yque.front(); Yque.pop();
		for (int i = 0; i < 4; i++)
		{
			if (arr[tempy + diry[i]][tempx + dirx[i]] == 2)
			{
				Xque.push(tempx + dirx[i]);
				Yque.push(tempy + diry[i]);
				arr[tempy + diry[i]][tempx + dirx[i]] = 1;
				result[result[0]]++;
			}
		}	
	}
	return;
}

void Sort()
{
	int size = result[0];
	int temp;
	for (int i = 1; i <= size; i++)
	{
		for (int j = i + 1; j <= size; j++)
		{
			if (result[i] > result[j])
			{
				temp = result[i];
				result[i] = result[j];
				result[j] = temp;
			}
		}
	}
	return;
}

int main()
{
	// ������ �ް� �� ���� ��ŭ 2�� ĥ�ϱ�
	int ysize, xsize, rec;
	cin >> ysize >> xsize >> rec;
	for (int i = 1; i <= ysize; i++)
	{
		for (int j = 1; j <= xsize; j++)
			arr[i][j] = 2;
	}

	// ���簢�� �κе��� 1�� ĥ�ϱ�
	int x1, y1, x2, y2;
	for (int i = 0; i < rec; i++)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		
		for (int j = y1 + 1; j <= y2; j++)
		{
			for (int k = x1 + 1; k <= x2; k++)
				arr[j][k] = 1;
		}
	}

	//ó������ 2�� ���� ã�� BFS ������
	for (int i = 1; i <= ysize; i++)
	{
		for (int j = 1; j <= xsize; j++)
		{
			if (arr[i][j] == 2)
				BFS(j, i);
		}
	}

	// �������� ���� �� ���
	Sort();
	cout << result[0] << endl;
	for (int i = 1; i <= result[0]; i++)
		cout << result[i] << " ";

	return 0;
}