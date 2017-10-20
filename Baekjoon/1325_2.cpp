#include <iostream>
#include <queue>
using namespace std;
const int MAX = 10001;
int result[MAX];
int resultnum = 0;
int N, M;
int relat[100001][2];
int relatnum[MAX][2];		// relatnum[i][0-1]는 i번째 컴퓨터가 신뢰받는 목록이 relat[num][1]부터 relat[num2][1]까지라는 의미(counting sort)

void BFS(int n)
{
	int num = 0;
	int temp, next;
	bool visited[MAX] = { false, };
	queue<int> Que;
	Que.push(n);
	visited[n] = true;
	num++;
	while (!Que.empty())
	{
		temp = Que.front(); Que.pop();
		for(int i = relatnum[temp][0]; i <= relatnum[temp][1]; i++)
		{
			next = relat[i][0];
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

// 입력 받은 관계를 신뢰 받는 컴퓨터 번호 순으로 나열
void Sort()
{
	int temp0, temp1;
	for (int i = 1; i <= M; i++)
	{
		for (int j = i + 1; j <= M; j++)
		{
			if (relat[i][1] > relat[j][1])
			{
				temp0 = relat[i][0];
				temp1 = relat[i][1];
				relat[i][0] = relat[j][0];
				relat[i][1] = relat[j][1];
				relat[j][0] = temp0;
				relat[j][1] = temp1;
			}
		}
	}

	int now;
	now = 1;
	for (int i = 1; i <= N; i++)
	{
		if (relat[now][1] != i)
		{
			relatnum[i][0] = 0;
			relatnum[i][1] = 0;
			continue;
		}
		relatnum[i][0] = now;
		while (relat[now][1] == i)
		{
			now++;
			if (now > M)
				break;
		}
		relatnum[i][1] = now - 1;
	}
}

int main()
{
	int slave, master;
	cin >> N >> M;
	for (int i = 1; i <= M; i++)
	{
		cin >> slave >> master;
		relat[i][0] = slave;
		relat[i][1] = master;
	}
	Sort();

	for (int i = 1; i <= N; i++)
		BFS(i);
	for (int i = 1; i <= resultnum; i++)
		cout << result[i] << " ";
	return 0;
}