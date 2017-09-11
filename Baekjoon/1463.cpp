#include <iostream>
using namespace std;
const int MAX = 1000000;

int space[MAX];

int Min(int a, int b) { return (a < b ? a : b); }

int main()
{
	int input;
	for (int i = 1; i <= MAX; i++) space[i] = MAX;
	scanf("%d", &input);
	space[1] = 0;
	for (int i = 1; i < input; i++)
	{
		space[i + 1] = Min(space[i + 1], space[i] + 1);
		if (i * 2 > input) continue;
		space[i * 2] = Min(space[i * 2], space[i] + 1);
		if (i * 3 > input) continue;
		space[i * 3] = Min(space[i * 3], space[i] + 1);
	}
	printf("%d", space[input]);
}