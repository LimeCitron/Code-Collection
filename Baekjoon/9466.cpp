#include <iostream>
#include <queue>
using namespace std;
const int MAX = 100001;

int arr[MAX] = { 0, };
// finish가 0이면 아직 모르는거, 1이면 이미 짜여진거, -1이면 이미 파탄난거, -2는 사이클 찾는 과정중의 참조를 말함. -2는 함수가 실행된 후 -1이나 1로 바뀐다.
int finish[MAX] = { 0, };
int N;

void InitFinish()
{
	for (int i = 1; i < MAX; i++)
		finish[i] = 0;
}

// 사이클을 찾는 과정입니다. 
void MakeTeam(int n)
{
	if (arr[n] == n)
	{
		finish[n] = 1;
		return;
	}

	// 이 큐는 들어온 순서를 위해 사용된다. 만약 밑의 while문에서 finish[arr[now]]가 -2라면 
	// 그 arr[now]의 정보가 있는 큐 원소부터 사이클이라는 소리다. 그러한 순서를 보장하기 위해 큐를 사용하였다.
	queue<int> list;
	finish[n] = -2;
	list.push(n);
	int now = n;

	// 매핑을 따라서 연결이 가능한 곳을 계속 따라간다. 그 끝에 1이나 -1을 만나 파탄을 만나던지 -2를 만나 사이클을 이루던지.
	while (finish[arr[now]] == 0)
	{
		finish[arr[now]] = -2;
		list.push(arr[now]);
		now = arr[now];
	}

	// while 마지막 끝에서 -2를 만나서 사이클을 이루는 경우 
	if (finish[arr[now]] == -2)
	{
		// 사이클 아닌 부분은 파탄.
		while (list.front() != arr[now])
		{
			finish[list.front()] = -1;
			list.pop();
		}
		// 사이클인 부분은 1로 바꾸어준다.
		while (!list.empty())
		{
			finish[list.front()] = 1;
			list.pop();
		}
	}

	// while 마지막 끝에서 1이나 -1을 만나 파탄을 이루는 경우
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