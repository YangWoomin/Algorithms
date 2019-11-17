#include <iostream>
#include <string>

#include <cstdlib>
#include <ctime>

using namespace std;

void Swap(std::size_t& a, std::size_t& b)
{
	std::size_t temp = a;
	a = b;
	b = temp;
}

void QuickSort(std::size_t* arr, std::size_t left, std::size_t right)
{
	std::size_t mid = (left + right) / 2;
	if (right > left)
	{
		std::size_t i = left, j = right;
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

		if(0 < i)
			QuickSort(arr, left, i - 1);
		QuickSort(arr, i + 1, right);
	}
}

bool Verify(std::size_t* arr, std::size_t size)
{
	for (int i = 1; i < size; ++i)
		if (arr[i - 1] > arr[i])
			return false;
	return true;
}

#define MIN_TEST_COUNT	1
#define MAX_TEST_COUNT	USHRT_MAX
#define MIN_TEST_LIST	1
#define MAX_TEST_LIST	15
#define MIN_TEST_NUM	1
#define MAX_TEST_NUM	100

int main(int argc, char** argv)
{
	if (3 != argc)
	{
		std::cout << " * usage : " << argv[0] << " [test count number] [show process(true/false)] * " << std::endl;
		return -1;
	}

	std::size_t testCountNum = std::atoi(argv[1]);
	if (MIN_TEST_COUNT > testCountNum || MAX_TEST_COUNT < testCountNum)
	{
		std::cout << " * usage : test count number range : " << MIN_TEST_COUNT << " ~ " << MAX_TEST_COUNT << " * " << std::endl;
		return -2;
	}

	bool showProc = false;
	if ("true" == std::string(argv[2]))
		showProc = true;

	srand((unsigned int)time(NULL));

	std::size_t testListNum;
	std::size_t* arr = nullptr;
	bool allSuccess = true;
	for (std::size_t i = 0; i < testCountNum; ++i)
	{
		testListNum = ((std::size_t)rand() % (MAX_TEST_LIST - MIN_TEST_LIST + 1)) + MIN_TEST_LIST;

		if (nullptr != arr)
			delete[] arr;
		arr = new std::size_t[testListNum];
		if (nullptr == arr)
		{
			std::cout << " * allocating failed * " << std::endl;
			return -3;
		}

		if (showProc)
		{
			std::cout << "[" << i + 1 << "] test.. test list num : " << testListNum << std::endl;
			std::cout << "    test numbers : ";
		}

		for (std::size_t j = 0; j < testListNum; ++j)
		{
			arr[j] = ((std::size_t)rand() % (MAX_TEST_NUM - MIN_TEST_NUM + 1)) + MIN_TEST_NUM;
			if (showProc)
				std::cout << arr[j] << " ";
		}

		if (showProc)
			std::cout << std::endl;

		QuickSort(arr, 0, testListNum - 1);

		if (showProc)
		{
			std::cout << "    test result : ";
			for (std::size_t j = 0; j < testListNum; ++j)
				std::cout << arr[j] << " ";
			std::cout << std::endl;
		}

		if (false == Verify(arr, testListNum))
		{
			std::cout << " * verifying failed * " << std::endl;
			return -4;
		}
	}

	if (nullptr != arr)
		delete[] arr;

	std::cout << " * all test succeeded * " << std::endl;

	return 0;
}