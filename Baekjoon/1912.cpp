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
	
	// ���⿡�� dp�� i��°���� �����ϸ鼭 ���ӵǴ� �κм����� ���� ū ��.
	// �׷��ϱ� �� ���� for���� i��° ��Ҹ� �κ����տ� �ִ°� ����Ǵ��� �ƴϸ� �ű⼭ �߶�����°� ���� ���� ���ϴ� �����̴�.
	// �̷� ������ ���� �κ� ������ �ĺ��� ���ϰ� �׵� �� temp�� ���� ū ���� ������ �װ��� ���� ū ������ ���� �Ǵ� ���̴�. 
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