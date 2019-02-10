#include <iostream>
#include <queue>

using namespace std;

int arr[52][52];
int check[52][52];
int dirVerti[4] = { -1, 0, 1, 0 }; // 위, 오른쪽, 아래, 왼쪽
int dirHoriz[4] = { 0, 1, 0, -1 };
int N, L, R;

void checkArrayClear()
{
	for (int i = 0; i <= N + 1; i++) {
		for (int j = 0; j <= N + 1; j++) {
			if (i == 0 || j == 0 || i == N + 1 || j == N + 1)
				check[i][j] = -1;
			else
				check[i][j] = 0;
		}
	}
}

int GetAbsolute(int n) {
	if (n >= 0) return n;
	else return -n;
}

int Fun()
{
	int count = 0;
	int alloCount;

	do {	// 더 이상 이동할 수 없는 상태일때 까지 반복한다.
		queue<int> alloQueuei;
		queue<int> alloQueuej;
		int newi, newj, subtract;
		int alloresult[2500];
		checkArrayClear();
		alloCount = 1;

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (check[i][j] != 0) continue;

				alloQueuei.push(i); 
				alloQueuej.push(j);
				int sum = 0;
				int allonation = 1;
				check[i][j] = alloCount;
				while (!alloQueuei.empty())		// 큐가 다 떨어질때까지 탐색(BFS), 조건에 맞을 경우 큐에 넣는다.
				{
					int currenti = alloQueuei.front(); alloQueuei.pop();
					int currentj = alloQueuej.front(); alloQueuej.pop();
					sum = sum + arr[currenti][currentj];				

					for (int k = 0; k <= 3; k++) {
						newi = currenti + dirVerti[k];
						newj = currentj + dirHoriz[k];
						subtract = GetAbsolute(arr[currenti][currentj] - arr[newi][newj]);

						if (subtract >= L && subtract <= R && check[newi][newj] == 0) {
							check[newi][newj] = alloCount;
							alloQueuei.push(newi);
							alloQueuej.push(newj);
							allonation = allonation + 1;
						}
					}
				}

				alloresult[alloCount] = sum / allonation;    // 연합들의 최종 기대값을 계산한다.
				if (allonation > 1)
					alloCount++;
				else if (allonation == 1)
					check[i][j] = 0;
			}
		}

		for (int i = 1; i <= N; i++) {			// 연합들의 결과를 바꾸어준다. 
			for (int j = 1; j <= N; j++) {
				if (check[i][j] != 0)
					arr[i][j] = alloresult[check[i][j]];
			}
		}

		if (alloCount > 1)
			count++;
	} while (alloCount > 1);
	
	return count;
}

int main()
{
	cin >> N >> L >> R;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			cin >> arr[i][j];
	}
	cout << Fun() << endl;
	return 0;
}