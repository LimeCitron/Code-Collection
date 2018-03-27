#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>	// ���� �迭 ī�Ǹ� ���ؼ�
using namespace std;

int dir[4][2] = { {-1,0}, {0, 1}, {1, 0}, {0, -1} };  // 8-������ ��ǥ �̵� ��
int dirnum[4] = { -3,1,3,-1 };	// 8-������ �ε��� �̵� ��
stack<int> openstack;			// ����
stack<int> openstacklen;		// ���� ���� ����
queue<int> openqueue;			// ť
queue<int> openqueuelen;		// ť ���� ����
vector<int> openvector;			// A* Search�� Open Vector �迭��
vector<int> openvectorlen;		// A* Search�� �迭�� ���� ���� ����
vector<int> openvectorheur;		// A* Search�� �迭 ���� ���� + Heuristic �Լ��� ���� ����
vector<int> closevector;		// �湮�� ��� ����
vector<int> closevectorlen;		// �湮�� ��� ���� ����
int openmax = 0;				// Open �ڷᱸ���� �ִ� ����
int nowlist[9];					// ���� �۾����� 8-���� ���
int nowizero = 0;				// 0�� �ִ� ��
int nowjzero = 0;				// 0�� �ִ� ��
int nowzero = 0;				// 0�� �ִ� 8-������ �ε���
int findsameindex = 0;			// A* Search���� Visited�� ���� ���� ã���� �� �� �ε����� �ѹ�

int MakeInt(int* arr)			// 8-������ �迭�� ����ȭ 
{
	int multip = 1;
	int result = 0;
	for (int i = 0; i < 9; i++)
	{
		result = result + (arr[8 - i] * multip);
		multip = multip * 10;
	}
	return result;
}

void DecomposeInt(int input, int* arr)		// 8����� ������� ������ �ٽ� Decompose, 0�� ��ġ�� ����.
{
	int divi = 100000000;
	int result = input;
	int temp = 0;
	for (int i = 0; i < 9; i++)
	{
		temp = result / divi;
		arr[i] = temp;
		if (temp == 0)
		{
			nowizero = i / 3;
			nowjzero = i % 3;
			nowzero = i;
		}
		result = result - (temp * divi);
		divi = divi / 10;
	}
	return;
}

bool IsSame(int num)		// Visit �ȿ� �Ȱ��� num�� �ִ���?(�̹� �湮�Ѱ���)
{
	int vectorsize = closevector.size();
	for (int i = 0; i < vectorsize; i++)
	{
		if (num == closevector[i])
			return true;
	}
	return false;
}

int FindSmallestValue(vector<int>& vec)
{
	int vectorsize = vec.size();
	int smallvalue = 1000000;
	int result = 0;
	for (int i = 0; i < vectorsize; i++)
	{
		if (vec[i] < smallvalue)
		{
			smallvalue = vec[i];
			result = i;
		}
	}
	return result;
}

void SwapArray(int i, int j, int* arr)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void SwapVector(int i, int j, vector<int>& vec)
{
	int temp = vec[i];
	vec[i] = vec[j];
	vec[j] = temp;
}

int GetHeuristic1(int* arr)
{
	int result = 0;
	for (int i = 0; i < 9; i++)
	{
		if (arr[i] != i + 1)
			result++;
	}
	return result-1;
}

int GetHeuristic2(int* arr)
{
	// [��ġ][�� �ִ� ����]�� ����
	int lookuptable[9][9] = { {0,0,1,2,1,2,3,2,3}, {0,1,0,1,2,1,2,3,2}, {0,2,1,0,3,2,1,4,3},
							 {0,1,2,3,0,1,2,1,2}, {0,2,1,2,1,0,1,2,1}, {0,3,2,1,2,1,0,3,2},
							 {0,2,3,4,1,2,3,0,1}, {0,3,2,3,2,1,2,1,0}, {0,4,3,2,3,2,1,2,1} };
	int result = 0;
	for (int i = 0; i < 9; i++)
	{
		result = result + lookuptable[i][arr[i]];
	}
	return result;
}


int DFS_Graph(int first)	// DFS
{
	openstack.push(first);
	openstacklen.push(0);
	int temp;
	int temparray[9];
	int len;
	while (true)
	{
		if (openstack.empty()) return -1;
		do
		{
			temp = openstack.top(); openstack.pop();
			len = openstacklen.top(); openstacklen.pop();
		} while (IsSame(temp));
		if (temp == 123456780) return len;
		closevector.push_back(temp);
		DecomposeInt(temp, nowlist);
		for (int i = 0; i < 4; i++)
		{
			if (nowizero + dir[i][0] >= 0 && nowizero + dir[i][0] < 3 && nowjzero + dir[i][1] >= 0 && nowjzero + dir[i][1] < 3) // ���� ������ �̵� ������ ����� �ʴ´ٸ�
			{
				copy(nowlist, nowlist + 9, temparray);
				SwapArray(nowzero, nowzero + dirnum[i], temparray);
				temp = MakeInt(temparray);
				openstack.push(temp);
				openstacklen.push(len + 1);
			}
		}
		if (openstack.size() > openmax)	// Open�� �ִ� ũ��
			openmax = openstack.size();
	}
	return 0;
}

int BFS_Graph(int first)	// BFS
{
	openqueue.push(first);
	openqueuelen.push(0);
	int temp;
	int temparray[9];
	int len;
	while (true)
	{
		if (openqueue.empty()) return -1;
		do
		{
			temp = openqueue.front(); openqueue.pop();
			len = openqueuelen.front(); openqueuelen.pop();
		} while (IsSame(temp));
		if (temp == 123456780) return len;
		closevector.push_back(temp);
		DecomposeInt(temp, nowlist);
		for (int i = 0; i < 4; i++)
		{
			if (nowizero + dir[i][0] >= 0 && nowizero + dir[i][0] < 3 && nowjzero + dir[i][1] >= 0 && nowjzero + dir[i][1] < 3) // ���� ������ �̵� ������ ����� �ʴ´ٸ�
			{
				copy(nowlist, nowlist + 9, temparray);
				SwapArray(nowzero, nowzero + dirnum[i], temparray);
				temp = MakeInt(temparray);
				openqueue.push(temp);
				openqueuelen.push(len + 1);
			}
		}
		if (openqueue.size() > openmax)	// Open�� �ִ� ũ��
			openmax = openqueue.size();
	}
	return 0;
}

int A_Star_Graph(int first, int heurmode)		// A* Search
{
	openvector.push_back(first);
	openvectorlen.push_back(0);
	openvectorheur.push_back(0);
	int temp;
	int temparray[9];
	int len;
	int heurlen;
	int findindex;
	bool tempright;
	while (true)
	{
		if (openvector.empty()) return -1;
		do
		{
			findindex = FindSmallestValue(openvectorheur);
			temp = openvector[findindex]; SwapVector(findindex, openvector.size() - 1, openvector); openvector.pop_back();		// ���� ���� ���� ã�Ƽ� Vector���� ���ִ� �۾�
			len = openvectorlen[findindex]; SwapVector(findindex, openvectorlen.size() - 1, openvectorlen); openvectorlen.pop_back();
			heurlen = openvectorheur[findindex]; SwapVector(findindex, openvectorheur.size() - 1, openvectorheur); openvectorheur.pop_back();
			
			tempright = IsSame(temp);			
			if (tempright == false) break;		// �湮�� ���� �ƴϸ� �����Ѵ�.
			else if (tempright == true && closevectorlen[findsameindex] > openvectorheur[findsameindex])		// �湮�� ���̾ �������� ���� ������ �����Ѵ�. 
			{
				closevectorlen[findsameindex] = openvectorheur[findsameindex];
				break;
			}
		} while (true);
		if (temp == 123456780) return len;
		closevector.push_back(temp);
		closevectorlen.push_back(heurlen);
		DecomposeInt(temp, nowlist);
		for (int i = 0; i < 4; i++)
		{
			if (nowizero + dir[i][0] >= 0 && nowizero + dir[i][0] < 3 && nowjzero + dir[i][1] >= 0 && nowjzero + dir[i][1] < 3) // ���� ������ �̵� ������ ����� �ʴ´ٸ�
			{
				copy(nowlist, nowlist + 9, temparray);
				SwapArray(nowzero, nowzero + dirnum[i], temparray);
				temp = MakeInt(temparray);
				openvector.push_back(temp);
				openvectorlen.push_back(len + 1);
				if(heurmode == 1)
					openvectorheur.push_back(len + 1 + GetHeuristic1(temparray));
				else if(heurmode == 2)
					openvectorheur.push_back(len + 1 + GetHeuristic2(temparray));
			}
		}
		if (openvector.size() > openmax)	// Open�� �ִ� ũ��
			openmax = openvector.size();
	}
	return 0;
}


int main()
{
	int arr[4] = { 410632758, 431652078, 310452678, 12345678 };   // ���� Input
	int len = A_Star_Graph(arr[3], 2);							  // DFS_Graph(arr[n]), BFS_Graph(arr[n]), A_Star_Graph(arr[n], 1), A_Star_Graph(arr[n], 2) �� ������.

	cout << "Visit : " << closevector.size() << endl;
	cout << "Open : " << openmax << endl;
	cout << "Length : " << len << endl;
	return 0;
}