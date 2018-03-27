#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>	// 편리한 배열 카피를 위해서
using namespace std;

int dir[4][2] = { {-1,0}, {0, 1}, {1, 0}, {0, -1} };  // 8-퍼즐의 좌표 이동 값
int dirnum[4] = { -3,1,3,-1 };	// 8-퍼즐의 인덱스 이동 값
stack<int> openstack;			// 스택
stack<int> openstacklen;		// 스택 길이 저장
queue<int> openqueue;			// 큐
queue<int> openqueuelen;		// 큐 길이 저장
vector<int> openvector;			// A* Search의 Open Vector 배열값
vector<int> openvectorlen;		// A* Search의 배열의 진행 과거 길이
vector<int> openvectorheur;		// A* Search의 배열 진행 과거 + Heuristic 함수에 따른 길이
vector<int> closevector;		// 방문한 노드 저장
vector<int> closevectorlen;		// 방문한 노드 길이 저장
int openmax = 0;				// Open 자료구조의 최대 길이
int nowlist[9];					// 현재 작업중인 8-퍼즐 모양
int nowizero = 0;				// 0이 있는 행
int nowjzero = 0;				// 0이 있는 열
int nowzero = 0;				// 0이 있는 8-퍼즐의 인덱스
int findsameindex = 0;			// A* Search에서 Visited와 같은 값을 찾았을 때 그 인덱스의 넘버

int MakeInt(int* arr)			// 8-퍼즐의 배열을 정수화 
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

void DecomposeInt(int input, int* arr)		// 8퍼즐로 만들어진 정수를 다시 Decompose, 0의 위치도 저장.
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

bool IsSame(int num)		// Visit 안에 똑같은 num이 있는지?(이미 방문한건지)
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
	// [위치][에 있는 숫자]의 점수
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
			if (nowizero + dir[i][0] >= 0 && nowizero + dir[i][0] < 3 && nowjzero + dir[i][1] >= 0 && nowjzero + dir[i][1] < 3) // 만약 퍼즐이 이동 범위를 벗어나지 않는다면
			{
				copy(nowlist, nowlist + 9, temparray);
				SwapArray(nowzero, nowzero + dirnum[i], temparray);
				temp = MakeInt(temparray);
				openstack.push(temp);
				openstacklen.push(len + 1);
			}
		}
		if (openstack.size() > openmax)	// Open의 최대 크기
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
			if (nowizero + dir[i][0] >= 0 && nowizero + dir[i][0] < 3 && nowjzero + dir[i][1] >= 0 && nowjzero + dir[i][1] < 3) // 만약 퍼즐이 이동 범위를 벗어나지 않는다면
			{
				copy(nowlist, nowlist + 9, temparray);
				SwapArray(nowzero, nowzero + dirnum[i], temparray);
				temp = MakeInt(temparray);
				openqueue.push(temp);
				openqueuelen.push(len + 1);
			}
		}
		if (openqueue.size() > openmax)	// Open의 최대 크기
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
			temp = openvector[findindex]; SwapVector(findindex, openvector.size() - 1, openvector); openvector.pop_back();		// 가장 작은 값을 찾아서 Vector에서 빼주는 작업
			len = openvectorlen[findindex]; SwapVector(findindex, openvectorlen.size() - 1, openvectorlen); openvectorlen.pop_back();
			heurlen = openvectorheur[findindex]; SwapVector(findindex, openvectorheur.size() - 1, openvectorheur); openvectorheur.pop_back();
			
			tempright = IsSame(temp);			
			if (tempright == false) break;		// 방문한 곳이 아니면 진행한다.
			else if (tempright == true && closevectorlen[findsameindex] > openvectorheur[findsameindex])		// 방문한 곳이어도 기존보다 값이 작으면 진행한다. 
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
			if (nowizero + dir[i][0] >= 0 && nowizero + dir[i][0] < 3 && nowjzero + dir[i][1] >= 0 && nowjzero + dir[i][1] < 3) // 만약 퍼즐이 이동 범위를 벗어나지 않는다면
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
		if (openvector.size() > openmax)	// Open의 최대 크기
			openmax = openvector.size();
	}
	return 0;
}


int main()
{
	int arr[4] = { 410632758, 431652078, 310452678, 12345678 };   // 예제 Input
	int len = A_Star_Graph(arr[3], 2);							  // DFS_Graph(arr[n]), BFS_Graph(arr[n]), A_Star_Graph(arr[n], 1), A_Star_Graph(arr[n], 2) 중 고르세요.

	cout << "Visit : " << closevector.size() << endl;
	cout << "Open : " << openmax << endl;
	cout << "Length : " << len << endl;
	return 0;
}