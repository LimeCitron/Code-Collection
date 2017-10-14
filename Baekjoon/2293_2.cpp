// 2293_1의 2차원 배열을 1차원으로 압축시킨 버전. 메모리가 훨씬 줄어든다.

#include <cstdio>
const int NUMMAX = 10001;
const int KINDMAX = 101;
int dp[NUMMAX] = { 0, };
int arr[KINDMAX];
int n, k;

int main()
{
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	
	dp[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		for (int j = arr[i]; j <= k; j++)
		{
			dp[j] = dp[j] + dp[j - arr[i]];
		}
	}
	printf("%d", dp[k]);
	return 0;
}