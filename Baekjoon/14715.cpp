#include <iostream>
using namespace std;

// 파라미터 a를 나눌 수 있는 가장 작은 소수로 나누었을 때의 나눈 수와 몫을 반환하는 함수
// arr[0]은 나눈 수, arr[1]은 몫을 반환한다.
void DividePrime(int a, int* arr)
{
	arr[0] = -1;
	arr[1] = -1;
	int stddiv = 2;
	while (1)
	{
		if (a < stddiv)
			break;
		if (a % stddiv == 0)
		{
			arr[0] = stddiv;
			arr[1] = a / stddiv;
			break;
		}
		stddiv++;
	}
	return;
}

// a가 2의 몇승보다 같거나 작은지 반환
int PowerOfTwo(int a)
{
	int temp = 1;
	int time = 0;
	while (a > temp)
	{
		time++;
		temp *= 2;
	}
	return time;
}

int main()
{
	int value;
	int primenum = 0;
	int temp[2];
	cin >> value;
	while (1)
	{
		DividePrime(value, temp);
		primenum++;
		if (temp[1] == 1)
			break;
		value = value / temp[0];
	}
	cout << PowerOfTwo(primenum);
	return 0;
}