#include <cstdio>

int main()
{
	int input;
	int arr[1001];
	arr[1] = 1;
	arr[2] = 2;
	scanf("%d", &input);
	
	for (int i = 3; i <= input; i++)
		arr[i] = (arr[i - 1] + arr[i - 2]) % 10007;
	
	printf("%d", arr[input]);
	return 0;
}