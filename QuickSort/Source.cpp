#include "SortCommon.h"

using namespace std;

class QuickSort : public SortCommon
{
public:
	virtual void Sort() override
	{
		Sort(0, size - 1);
	}

private:
	void Sort(std::size_t left, std::size_t right)
	{
		if (nullptr == arr)
			return;

		std::size_t pivot = (left + right) / 2;
		if (right > left)
		{
			std::size_t i = left, j = right;
			while (i < j)
			{
				for (; arr[i] <= arr[pivot] && i < j; ++i);
				for (; arr[j] >= arr[pivot] && i < j; --j);
				if (i < j)
				{
					Swap(arr[i], arr[j]);
				}
				else // i == j
				{
					if (pivot < i && arr[pivot] < arr[i])
						--i;
					else if (pivot > i && arr[pivot] > arr[i])
						++i;
					Swap(arr[pivot], arr[i]);
					break;
				}
			}

			if (0 < i)
				Sort(left, i - 1);
			Sort(i + 1, right);
		}
	}
};

int main(int argc, char** argv)
{
	if (3 != argc)
	{
		std::cout << " * usage : " << argv[0] << " [test count number] [show process(true/false)] * " << std::endl;
		return -1;
	}

	std::size_t testCountNum = std::atoi(argv[1]);
	bool showProc = false;
	if ("true" == std::string(argv[2]))
		showProc = true;

	QuickSort sort;
	sort.DoTest(testCountNum, showProc);

	return 0;
}