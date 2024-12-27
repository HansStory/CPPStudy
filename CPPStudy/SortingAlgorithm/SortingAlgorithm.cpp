#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


using namespace std;

// 팀 정렬에서 사용할 최소 런 크기
const int RUN = 32;

class SortAlgorithm
{
public :
	SortAlgorithm()
	{
		InitAlgorithm();
	}

	~SortAlgorithm()
	{
		delete[] pBuffer;
		pBuffer = nullptr;
	}

	void InitAlgorithm()
	{
		cout << "배열의 수를 입력하세요 : ";
		cin >> size;

		if (pBuffer != nullptr)
		{
			delete[] pBuffer;
			pBuffer = nullptr;
		}

		pBuffer = new int[size] {0};

		for (int i = 0; i < size; i++)
		{
			cout << i + 1 << "번째 값을 입력하세요! : ";
			cin >> pBuffer[i];
		}
	}

#pragma region 버블 정렬 알고리즘 (Bubble Sort Algorithm)
	void BubbleSort(int arr[], int size)
	{
		int i, j, temp;
		for (i = 0; i < size - 1; ++i)
		{
			for (j = 0; j < (size - i) - 1; ++j)
			{
				if (arr[j] > arr[j + 1])
				{
					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
	}

	void BubbleSort()
	{
		BubbleSort(pBuffer, this->size);
	}
#pragma endregion

#pragma region 선택 정렬 알고리즘 (Selection Sort Algorithm)
	void SelectionSort(int arr[], int size)
	{
		for (int i = 0; i < size - 1; ++i)
		{
			// 최소값의 인덱스를 찾는다
			int minIndex = i;
			for (int j = i + 1; j < size; ++j)
			{
				if (arr[j] < arr[minIndex])
				{
					minIndex = j;
				}
			}
			// 최소값과 현재 위치의 값을 직접 교환
			if (minIndex != i)
			{
				int temp = arr[i];
				arr[i] = arr[minIndex];
				arr[minIndex] = temp;
			}
		}
	}

	void SelectionSort()
	{
		SelectionSort(pBuffer, this->size);
	}
#pragma endregion

#pragma region 삽입 정렬 알고리즘 (Insertion Sort Algorithm)
	template <typename T>
	void insertionSort(std::vector<T>& vec, const int& left, const int& right) 
	{
		for (int i = left; i < right; ++i) 
		{
			for (int j = i + 1; j > left && vec[j] < vec[j - 1]; --j)
			{
				std::swap(vec[j], vec[j - 1]);
			}
		}
	}

	void InsertionSort(int arr[], int n) 
	{
		for (int i = 1; i < n; ++i) 
		{
			int key = arr[i];
			int j = i - 1;

			// 현재 값(key)이 정렬된 부분 배열 내에서 적절한 위치를 찾도록 이동
			while (j >= 0 && arr[j] > key) 
			{
				arr[j + 1] = arr[j];
				--j;
			}

			// 적절한 위치에 현재 값을 삽입
			arr[j + 1] = key;
		}
	}

	void InsertionSort()
	{
		InsertionSort(this->pBuffer, this->size);
	}
#pragma endregion

#pragma region 병합 정렬 알고리즘 (Merge Sort Algorithm)

	void Merge(int arr[], int left, int mid, int right) 
	{
		int leftArrSize = mid - left + 1;  // 왼쪽 배열 크기
		int rightArrSize = right - mid;    // 오른쪽 배열 크기

		// 임시 배열 메모리 동적할당
		int* leftArr = new int[leftArrSize];
		int* RightArr = new int[rightArrSize];

		// 원본 배열 데이터를 임시 배열에 복사
		for (int i = 0; i < leftArrSize; ++i)
		{
			leftArr[i] = arr[left + i];
		}
		for (int j = 0; j < rightArrSize; ++j)
		{
			RightArr[j] = arr[mid + 1 + j];
		}

		// 병합 작업
		int i = 0, j = 0, k = left;
		while (i < leftArrSize && j < rightArrSize)
		{
			if (leftArr[i] <= RightArr[j])
			{
				arr[k] = leftArr[i];
				++i;
			}
			else
			{
				arr[k] = RightArr[j];
				++j;
			}
			++k;
		}

		// 남은 데이터를 병합
		while (i < leftArrSize)
		{
			arr[k] = leftArr[i];
			++i;
			++k;
		}
		while (j < rightArrSize)
		{
			arr[k] = RightArr[j];
			++j;
			++k;
		}

		// 동적 메모리 해제
		delete[] leftArr;
		delete[] RightArr;
	}

	void MergeSort(int arr[], int left, int right)
	{
		// 재귀호출 종료 조건
		if (left < right)
		{
			int mid = left + (right - left) / 2; // 중간 인덱스 계산

			// 좌우 분할
			MergeSort(arr, left, mid);
			MergeSort(arr, mid + 1, right);

			// 병합
			Merge(arr, left, mid, right);
		}
	}

	void MergeSort()
	{
		MergeSort(this->pBuffer, 0, this->size);
	}

#pragma endregion 

#pragma region 힙 정렬 알고리즘 (Heap Sort Algorithm)
	void Heapify(int arr[], int size, int i)
	{
		int largest = i;       // 루트를 가장 큰 값으로 가정
		int left = 2 * i + 1;  // 왼쪽 자식 노드
		int right = 2 * i + 2; // 오른쪽 자식 노드

		// 왼쪽 자식이 루트보다 크면 largest 갱신
		if (left < size && arr[left] > arr[largest])
		{
			largest = left;
		}

		// 오른쪽 자식이 largest보다 크면 largest 갱신
		if (right < size && arr[right] > arr[largest])
		{
			largest = right;
		}

		// largest가 루트가 아니면 교환하고 재귀 호출
		if (largest != i)
		{
			swap(arr[i], arr[largest]);
			Heapify(arr, size, largest);
		}
	}

	// 힙 정렬 함수
	void HeapSort(int arr[], int size) 
	{
		// 배열을 힙 구조로 변환
		int&& largest = (size / 2) - 1;		//가운데 값을 largest로 가정
		for (int i = largest; i >= 0; --i)
		{
			Heapify(arr, size, i);
		}

		// 하나씩 요소를 힙에서 추출
		for (int i = size - 1; i > 0; --i)
		{
			swap(arr[0], arr[i]);	// 현재 루트를 끝으로 보냄
			Heapify(arr, i, 0);		// 힙 구조 재정렬
		}
	}

	void HeapSort()
	{
		HeapSort(this->pBuffer, this->size);
	}

#pragma endregion

#pragma region 퀵 정렬 알고리즘 (Quick Sort Algorithm)
	// 배열을 분할하는 함수
	int Partition(int arr[], int low, int high) 
	{
		int pivot = arr[high];			// 피벗으로 마지막 요소 선택
		int i = low - 1;				// 작은 요소의 인덱스

		for (int j = low; j < high; ++j) 
		{
			if (arr[j] < pivot)			// 현재 요소가 피벗보다 작으면
			{
				++i;					// 작은 요소의 인덱스 증가
				swap(arr[i], arr[j]);	// 현재 요소와 교환
			}
		}

		// 피벗을 적절한 위치로 이동
		swap(arr[i + 1], arr[high]);
		return i + 1; // 피벗의 최종 위치 반환
	}

	// 퀵 정렬 함수
	void QuickSort(int arr[], int low, int high) 
	{
		if (low < high) 
		{
			// 배열을 분할하고 피벗의 위치를 얻음
			int pivot = Partition(arr, low, high);

			// 피벗을 기준으로 좌우 배열 재귀 호출
			Partition(arr, low, pivot - 1);
			Partition(arr, pivot + 1, high);
		}
	}

	void QuickSort() 
	{
		QuickSort(this->pBuffer, 0, this->size - 1);
	}
#pragma endregion

#pragma region 트리 정렬 (Tree Sort Algorithm)
	struct Node 
	{
		int key;
		Node* left;
		Node* right;

		Node(int value) : key(value), left(nullptr), right(nullptr) {}
	};

	// 새로운 노드를 삽입하는 함수
	Node* Insert(Node* root, int key)
	{
		if (root == nullptr)
		{
			return new Node(key);	// 새로운 노드 생성
		}

		if (key < root->key)
		{
			root->left = Insert(root->left, key);	// 왼쪽 서브트리에 삽입
		}
		else
		{
			root->right = Insert(root->right, key); // 오른쪽 서브트리에 삽입
		}

		return root;
	}

	// 중위 순회로 트리 출력 (정렬된 순서로 출력)
	void InorderTraversal(Node* root, int arr[], int& index)
	{
		if (root != nullptr)
		{
			InorderTraversal(root->left, arr, index);	// 왼쪽 서브트리 순회
			arr[index++] = root->key;					// 현재 노드의 값 저장
			InorderTraversal(root->right, arr, index);	// 오른쪽 서브트리 순회
		}
	}

	// 트리 메모리 해제
	void DeleteTree(Node* root)
	{
		if (root != nullptr)
		{
			DeleteTree(root->left);
			DeleteTree(root->right);
			delete root;
		}
	}

	// 트리 정렬 함수
	void TreeSort(int arr[], int n)
	{
		Node* root = nullptr;

		// 배열의 모든 값을 이진 탐색 트리에 삽입
		for (int i = 0; i < n; ++i) {
			root = Insert(root, arr[i]);
		}

		// 트리를 중위 순회하여 배열에 저장
		int index = 0;
		InorderTraversal(root, arr, index);

		// 메모리 해제
		DeleteTree(root);
	}

	void TreeSort()
	{
		TreeSort(this->pBuffer, this->size);
	}
#pragma endregion

#pragma region 팀 소트 (Tim Sort Algorithm)
	// 삽입 정렬 함수
	void InsertionSort(int arr[], int left, int right, bool ascending)
	{
		for (int i = left + 1; i <= right; ++i)
		{
			int temp = arr[i];
			int j = i - 1;
			// ascending에 의해 오름차순 내림차순 정렬 여부 결정
			while (j >= left && (ascending ? arr[j] > temp : arr[j] < temp))
			{
				arr[j + 1] = arr[j];
				--j;
			}
			arr[j + 1] = temp;
		}
	}

	// 두 배열을 병합하는 함수
	void Merge(int arr[], int left, int mid, int right, bool ascending)
	{
		int leftArrSize = mid - left + 1;
		int rightArrSize = right - mid;

		// 임시 배열 메모리 동적할당
		int* leftArr = new int[leftArrSize];
		int* rightArr = new int[rightArrSize];

		// 데이터를 임시 배열로 복사
		for (int i = 0; i < leftArrSize; ++i)
		{
			leftArr[i] = arr[left + i];
		}
		for (int i = 0; i < rightArrSize; ++i)
		{
			rightArr[i] = arr[mid + 1 + i];
		}

		int i = 0, j = 0, k = left;

		// 병합 작업
		while (i < leftArrSize && j < rightArrSize)
		{
			// ascending에 의해 오름차순 내림차순 정렬 여부 결정
			if (ascending ? leftArr[i] <= rightArr[j] : leftArr[i] >= rightArr[j])
			{
				arr[k++] = leftArr[i++];
			}
			else {
				arr[k++] = rightArr[j++];
			}
		}

		// 남은 데이터 처리
		while (i < leftArrSize)
		{
			arr[k++] = leftArr[i++];
		}
		while (j < rightArrSize)
		{
			arr[k++] = rightArr[j++];
		}
	}

	// 팀 정렬 함수
	void TimSort(int arr[], int n, bool ascending = true)
	{
		// RUN 크기마다 삽입 정렬 수행
		for (int i = 0; i < n; i += RUN)
		{
			InsertionSort(arr, i, min(i + RUN - 1, n - 1), ascending);
		}

		// 병합 작업
		for (int size = RUN; size < n; size *= 2)
		{
			for (int left = 0; left < n; left += 2 * size)
			{
				int mid = left + size - 1;
				int right = std::min(left + 2 * size - 1, n - 1);

				if (mid < right)
				{
					Merge(arr, left, mid, right, ascending);
				}
			}
		}
	}

	void TimSort(bool ascending = true)
	{
		TimSort(this->pBuffer, this->size, ascending);
	}
#pragma endregion

	void InputSortOption()
	{
		cout << "1 입력 : 입력한 배열을 오름차순으로 정렬" << endl;
		cout << "2 입력 : 입력한 배열을 내림차순으로 정렬" << endl;

		int inputValue = 0;
		cout << "입력해 주시기 바랍니다. : ";
		cin >> inputValue;

		PrintSortResult(inputValue);
	}

	void PrintSortResult(int sortOption)
	{
		cout << "정렬하기전 배열 : ";
		PrintArray(this->pBuffer, this->size);

		switch (sortOption)
		{
		case 1:
		default:
			this->TimSort(true);
			break;
		case 2:
			this->TimSort(false);
			break;
		}

		cout << "정렬 후 배열 : ";
		PrintArray(this->pBuffer, this->size);
	}

	void InputRestart()
	{
		string inputRestart;
		cout << "다시 시도해보시겠습니까? (Y/N) : ";
		cin >> inputRestart;

		if (inputRestart == "Y" || "y")
		{
			cout << "알고리즘을 초기화 합니다." << endl;
			InitAlgorithm();
			InputSortOption();
			InputRestart();
		}
		else
		{
			cout << "프로그램을 종료하겠습니다.";
		}
	}

	void PrintArray(int arr[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			cout << arr[i] << ", ";
		}

		cout << endl;
	}

	void PrintArray()
	{
		PrintArray(this->pBuffer, this->size);
	}

private :
	int size;
	int* pBuffer = nullptr;
};



int main()
{
	SortAlgorithm sortAlgorithm;

	sortAlgorithm.InputSortOption();
	sortAlgorithm.InputRestart();

	return 0;
}

