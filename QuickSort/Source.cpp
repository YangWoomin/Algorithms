#include <iostream>
#include <string>

using namespace std;

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void QuickSort(int* arr, int left, int right)
{
	int mid = (left + right) / 2;
	if (right > left)
	{
		int i = left, j = right;
		while (i < j)
		{
			for (; arr[i] <= arr[mid] && i < j; ++i);
			for (; arr[j] >= arr[mid] && i < j; --j);
			if (i < j)
			{
				Swap(arr[i], arr[j]);
			}
			else // i == j
			{
				if (mid < i && arr[mid] < arr[i])
					--i;
				else if (mid > i && arr[mid] > arr[i])
					++i;
				Swap(arr[mid], arr[i]);
				break;
			}
		}

		QuickSort(arr, left, i - 1);
		QuickSort(arr, i + 1, right);
	}
}

int main(int argc, char** argv)
{
	if (2 > argc)
	{
		std::cout << "usage : " << argv[0] << " [number]..." << std::endl;
		return -1;
	}

	int* arr = new int[(long long)argc - 1];

	for (int i = 1; i < argc; ++i)
	{
		arr[i - 1] = std::atoi(argv[i]);
		if (0 >= arr[i - 1])
		{
			std::cout << "usage : cannot sort less than 0" << std::endl;
			delete[] arr;
			return -2;
		}
	}

	QuickSort(arr, 0, argc - 2);

	std::cout << "result : ";
	for (int i = 0; i < argc - 1; ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	delete[] arr;

	return 0;
}