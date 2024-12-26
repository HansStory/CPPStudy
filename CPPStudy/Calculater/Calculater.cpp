#include <iostream>

using namespace std;

void SetInputValue(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << "번째 수를 입력하세요. : ";
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

	// 입력값 세팅
	SetInputValue(arr, size);

	// 합계
	int&& sumValue = Sum(arr, size);
	cout << "합계는 : " << sumValue << " 입니다!" << endl;

	// 평균
	cout << "평균은 : " << Average(sumValue, size) << " 입니다!";

	return 0;
}