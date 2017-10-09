#include <iostream>
using namespace std;
const int MAX = 14;

int visited[MAX * 4][MAX * 4] = { 0, };

int dirm[4] = { 0, 0, 1, -1 };
int dirn[4] = { 1, -1, 0, 0 };
double prarr[4];
int nmax;

double simp = 0;
double comp = 0;

void DFS(int num, int status, int m, int n, double prob)
{
	if (num == nmax)
	{
		if (status == 1)
			comp = comp + prob;
		else
			simp = simp + prob;

		return;
	}

	int tm, tn;
	for (int i = 0; i < 4; i++)
	{
		tm = m + dirm[i];
		tn = n + dirn[i];
		if (visited[tm][tn] == 1)
		{
			comp = comp + prob*prarr[i];
		}
		else
		{
			visited[tm][tn] = 1;
			DFS(num + 1, status, tm, tn, prob*prarr[i]);
			visited[tm][tn] = 0;
		}
	}
	return;
}

int main()
{
	cin >> nmax >> prarr[0] >> prarr[1] >> prarr[2] >> prarr[3];
	for (int i = 0; i < 4; i++)
		prarr[i] = prarr[i] / 100;

	visited[MAX * 2][MAX * 2] = 1;
	DFS(0, 0, MAX * 2, MAX * 2, 1);
	printf("%.10lf", simp);

	return 0;
}