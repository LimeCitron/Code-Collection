#include <iostream>
using namespace std;
const int MAX = 1001;

int min(int a, int b) { return (a < b ? a : b); }

int main()
{
	int input;
	int path[MAX][3];
	int cost[MAX][3];
	int result;

	scanf("%d", &input);
	for (int i = 1; i <= input; i++)
		scanf("%d %d %d", &cost[i][0], &cost[i][1], &cost[i][2]);
	for (int j = 0; j < 3; j++)
		path[1][j] = cost[1][j];
	for (int i = 1; i < input; i++)
	{
		path[i + 1][0] = min(path[i][1], path[i][2]) + cost[i + 1][0];
		path[i + 1][1] = min(path[i][0], path[i][2]) + cost[i + 1][1];
		path[i + 1][2] = min(path[i][0], path[i][1]) + cost[i + 1][2];
	}
	result = min(min(path[input][0], path[input][1]), path[input][2]);
	printf("%d", result);
	return 0;
}