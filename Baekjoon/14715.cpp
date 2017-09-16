#include <iostream>
using namespace std;

// �Ķ���� a�� ���� �� �ִ� ���� ���� �Ҽ��� �������� ���� ���� ���� ���� ��ȯ�ϴ� �Լ�
// arr[0]�� ���� ��, arr[1]�� ���� ��ȯ�Ѵ�.
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

// a�� 2�� ��º��� ���ų� ������ ��ȯ
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