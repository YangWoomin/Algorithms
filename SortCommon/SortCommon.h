#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MIN_TEST_COUNT	1
#define MAX_TEST_COUNT	USHRT_MAX
#define MIN_TEST_LIST	1
#define MAX_TEST_LIST	15
#define MIN_TEST_NUM	1
#define MAX_TEST_NUM	100

class SortCommon
{
protected:
	std::size_t* arr;
	std::size_t size;

	SortCommon() : arr(nullptr), size(0)
	{
		static bool init = false;
		if (false == init)
		{
			srand((unsigned int)time(NULL));
			init = true;
		}
	}

	void Swap(std::size_t& a, std::size_t& b)
	{
		std::size_t temp = a;
		a = b;
		b = temp;
	}

private:
	bool Verify()
	{
		if (nullptr == arr)
			return false;
		for (int i = 1; i < size; ++i)
			if (arr[i - 1] > arr[i])
				return false;
		return true;
	}

public:
	bool DoTest(std::size_t testCountNum, bool showProc)
	{
		if (MIN_TEST_COUNT > testCountNum || MAX_TEST_COUNT < testCountNum)
		{
			std::cout << " * usage : test count number range : " << MIN_TEST_COUNT << " ~ " << MAX_TEST_COUNT << " * " << std::endl;
			return false;
		}

		for (std::size_t i = 0; i < testCountNum; ++i)
		{
			size = ((std::size_t)rand() % (MAX_TEST_LIST - MIN_TEST_LIST + 1)) + MIN_TEST_LIST;
			
			if (nullptr != arr)
				delete[] arr;

			arr = new std::size_t[size];
			if (nullptr == arr)
			{
				std::cout << " * allocating failed * " << std::endl;
				return false;
			}

			if (showProc)
			{
				std::cout << "[" << i + 1 << "] test.. test list num : " << size << std::endl;
				std::cout << "    test numbers : ";
			}

			for (std::size_t j = 0; j < size; ++j)
			{
				arr[j] = ((std::size_t)rand() % (MAX_TEST_NUM - MIN_TEST_NUM + 1)) + MIN_TEST_NUM;
				if (showProc)
					std::cout << arr[j] << " ";
			}

			if (showProc)
				std::cout << std::endl;

			Sort();

			if (showProc)
			{
				std::cout << "    test result : ";
				for (std::size_t j = 0; j < size; ++j)
					std::cout << arr[j] << " ";
				std::cout << std::endl;
			}

			if (false == Verify())
			{
				std::cout << " * verifying failed * " << std::endl;
				return false;
			}
		}

		if (nullptr != arr)
		{
			delete[] arr;
			arr = nullptr;
		}

		std::cout << " * all test succeeded * " << std::endl;
		return true;
	}

	virtual ~SortCommon()
	{
		if (nullptr != arr)
		{
			delete[] arr;
			arr = nullptr;
		}
	}

	virtual void Sort() = 0;
};