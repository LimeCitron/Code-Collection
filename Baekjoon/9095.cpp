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
	
	// num[n]�� ���� = num[n-3] ����鿡 +3 ���̱� AND num[n-2] ����鿡 +2 ���̱� AND num[n-1] ����鿡 +1 ���̱��̴�.
	for (int i = 4; i < MAX; i++)
		num[i] = num[i - 3] + num[i - 2] + num[i - 1];

	scanf("%d", &input);
	for (int i = 0; i < input; i++)
		scanf("%d", &testcase[i]);
	for (int i = 0; i < input; i++)
		printf("%d\n", num[testcase[i]]);
	return 0;
}