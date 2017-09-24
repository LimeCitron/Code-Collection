#include <cstdio>
const int MAX = 100001;

int Max(int a, int b) { return (a > b ? a : b); }

int main()
{
	int value[MAX];
	int dp[MAX] = { 0, };
	int input;
	scanf("%d", &input);
	for (int i = 1; i <= input; i++)
		scanf("%d", &value[i]);
	
	// 여기에서 dp는 i번째까지 진행하면서 연속되는 부분수열의 가장 큰 합.
	// 그러니까 그 다음 for문은 i번째 요소를 부분집합에 넣는게 도움되는지 아니면 거기서 잘라버리는게 도움 될지 정하는 과정이다.
	// 이런 식으로 많은 부분 수열의 후보를 구하고 그들 중 temp에 가장 큰 값을 넣으며 그것이 가장 큰 수열의 합이 되는 것이다. 
	dp[1] = value[1];
	int temp = dp[1];

	for (int i = 1; i <= input; i++)
	{
		dp[i] = Max(dp[i - 1] + value[i], value[i]);
		if (temp < dp[i])
			temp = dp[i];
	}

	printf("%d", temp);
	return 0;
}