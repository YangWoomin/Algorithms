#include "RedBlackTree.h"

#include <Windows.h>
#include <iostream>

#include <cstdlib>
#include <ctime>

#include <vector>

#define MIN_TEST_NUM	1
#define MAX_TEST_NUM	1000000
#define RANGE_MIN		1
#define RANGE_MAX		5
#define INSERT_NUM		3

using namespace std;
using namespace YangAlgorithms;

int comparer(RedBlackTree::TreeValue value1, RedBlackTree::TreeValue value2)
{
	std::size_t val1 = (std::size_t)value1, val2 = (std::size_t)value2;
	if (val1 > val2)
		return -1;
	else if (val1 < val2)
		return 1;
	else
		return 0;
}

void shower(RedBlackTree::TreeValue value, RedBlackTree::NODE_COLOR color, int deepCount)
{
	/*SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	for (int i = 0; i < deepCount; ++i)
		std::cout << "*";

	if (RedBlackTree::RED == color)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		
	std::cout << (int)value << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);*/
}

int main(int argc, char** argv)
{
	if (2 != argc)
		return -1;

	std::size_t testCount = atoi(argv[1]);

	srand((unsigned int)time(NULL));

	RedBlackTree rbt(comparer, shower);

	std::size_t temp = 0;
	std::vector<std::size_t> nums;
	bool dup = false;
	for (std::size_t i = 0; i < testCount; ++i)
	{
		temp = (std::size_t)rand() % (RANGE_MAX - RANGE_MIN + 1) + RANGE_MIN;
		std::cout << "[" << i << "] ";
		if (INSERT_NUM >= temp) // insert
		{
			temp = (std::size_t)rand() % (MAX_TEST_NUM - MIN_TEST_NUM + 1) + MIN_TEST_NUM;
			dup = false;
			for (std::size_t j = 0; j < nums.size(); ++j)
			{
				if (temp == nums[j])
				{
					dup = true;
					break;
				}
			}

			if (dup)
			{
				std::cout << "Duplicated.. " << temp << std::endl;
				continue;
			}

			if (false == rbt.Insert((RedBlackTree::TreeValue)temp))
			{
				std::cout << "Inserting failed" << std::endl;
				return -2;
			}
			nums.push_back(temp);

			std::cout << "Insert " << temp << ", node count " << nums.size() << std::endl;
		}
		else if(0 < nums.size()) // delete
		{
			temp = (std::size_t)rand() % nums.size();
			if (false == rbt.Delete((RedBlackTree::TreeValue)(nums[temp])))
			{
				std::cout << "Deleting failed" << std::endl;
				return -3;
			}
			auto it = nums.begin();
			std::advance(it, temp);
			temp = nums[temp];
			nums.erase(it);

			std::cout << "Deleting " << temp << ", node count " << nums.size() << std::endl;
		}
		else // skip
		{
			std::cout << "Skip.." << std::endl;
		}

		if (false == rbt.CheckIntegrity())
		{
			std::cout << "Checking integrity failed" << std::endl;
			return -4;
		}
	}

	std::cout << std::endl;
	std::cout << "Testing succeeded" << std::endl;

	return 0;
}