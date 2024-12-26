#include <iostream>

using namespace std;

void SetInputValue(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << "��° ���� �Է��ϼ���. : ";
		cin >> arr[i];
	}
}

int const Sum(int arr[], int size)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += arr[i];
	}
	
	return sum;
}

double const Average(int sumValue, int size, bool b_showDecimal = true)
{
	double &&avg = (double)sumValue / (double)size;
	return b_showDecimal ? avg : (int)avg;
}

int main()
{
	int size = 5;
	int* arr = new int[size];

	// �Է°� ����
	SetInputValue(arr, size);

	// �հ�
	int&& sumValue = Sum(arr, size);
	cout << "�հ�� : " << sumValue << " �Դϴ�!" << endl;

	// ���
	cout << "����� : " << Average(sumValue, size) << " �Դϴ�!";

	return 0;
}