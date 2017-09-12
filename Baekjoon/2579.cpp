#include <stdio.h>
const int MAX = 301;

int Max(int a, int b) { return (a > b ? a : b); }

int main()
{
	int cost[MAX];  // n��° ����� ����
	int score[MAX][2];    // n ��° ����� ���� �ִ� ����(�� ��ܰ� �񿬼� / �� ��ܰ� ����)
	int input;
	scanf("%d", &input);
	cost[0] = 0;
	for (int i = 1; i <= input; i++)
		scanf("%d", &cost[i]);
	
	score[0][0] = 0;
	score[0][1] = 0;
	score[1][0] = cost[1];
	score[1][1] = cost[1];

	// score[n]�� �񿬼� = score[n-2]�� �񿬼Ӱ� ���� ���� �ִ밪 + cost[n]
	// score[n]�� ���� = score[n-1]�� �񿬼� �� + cost[n]
	for (int i = 2; i <= input; i++)
	{
		score[i][0] = Max(score[i - 2][0], score[i - 2][1]) + cost[i];
		score[i][1] = score[i - 1][0] + cost[i];
	}
	
	printf("%d", Max(score[input][0], score[input][1]));
	return 0;
	
}