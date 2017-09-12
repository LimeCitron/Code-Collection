#include <stdio.h>
const int MAX = 91;

int main()
{
	unsigned long long store[MAX][2];	// 조건에 맞는 n자리 숫자의 갯수 (0으로 끝나는 경우 / 1로 끝나는 경우)
	int input;
	scanf("%d", &input);
	store[1][0] = 0;
	store[1][1] = 1;
	store[2][0] = 1;
	store[2][1] = 0;

	// n자리 0으로 끝나는 수의 갯수 = n-1자리 전체 수(0과 1로 끝나는 수)의 갯수
	// n자리 1로 끝나는 수의 갯수 = n-1자리 0으로 끝나는 수의 갯수
	for (int i = 3; i <= input; i++)
	{
		store[i][0] = store[i - 1][0] + store[i - 1][1];
		store[i][1] = store[i - 1][0];
	}
	printf("%lld", store[input][0] + store[input][1]);
	return 0;
}