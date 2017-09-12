#include <stdio.h>
const int MAX = 11;

int main()
{
	int num[MAX];
	int input;
	int testcase[1000];

	
	num[1] = 1;
	num[2] = 2;
	num[3] = 4;
	
	// num[n]의 개수 = num[n-3] 방법들에 +3 붙이기 AND num[n-2] 방법들에 +2 붙이기 AND num[n-1] 방법들에 +1 붙이기이다.
	for (int i = 4; i < MAX; i++)
		num[i] = num[i - 3] + num[i - 2] + num[i - 1];

	scanf("%d", &input);
	for (int i = 0; i < input; i++)
		scanf("%d", &testcase[i]);
	for (int i = 0; i < input; i++)
		printf("%d\n", num[testcase[i]]);
	return 0;
}