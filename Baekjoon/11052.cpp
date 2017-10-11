/* 1 : 1+0
   2 : 2+0 vs 1+1
   3 : 3+0 vs 2+1
   4 : 4+0 vs 3+1 vs 2+2
   n : n+0 vs (n-1)+1 vs (n-2)+2 vs ..... vs (n/2)+(n/2)
*/

#include <cstdio>
const int MAX = 10001;

int main()
{
	int num;
	int bung[MAX];
	int casemax[MAX];
	casemax[0] = 0;
	scanf("%d", &num);
	for (int i = 1; i <= num; i++)
		scanf("%d", &bung[i]);
	for (int i = 1; i <= num; i++)
	{
		casemax[i] = bung[i];
		for (int j = 0; j <= i / 2; j++)
		{
			if (casemax[i] < casemax[j] + casemax[i - j])
				casemax[i] = casemax[j] + casemax[i - j];
		}
	}
	printf("%d", casemax[num]);
	return 0;
}