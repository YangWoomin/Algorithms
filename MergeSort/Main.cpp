#include "SortCommon.h"

class MergeSort : public SortCommon
{
public:
	virtual void Sort() override
	{
		if (nullptr != temp)
			delete[] temp;
		temp = new std::size_t[size];
		if (nullptr == temp)
			return;

		Sort(0, size - 1);

		delete[] temp;
		temp = nullptr;
	}

private:
	std::size_t* temp;
	void Sort(const std::size_t left, const std::size_t right)
	{
		if (right > left)
		{
			const std::size_t mid = (right + left) / 2;

			Sort(left, mid);
			Sort(mid + 1, right);

			std::size_t leftIdx = left, rightIdx = mid + 1, tempIdx = left;
			while (leftIdx <= mid && rightIdx <= right)
			{
				if (arr[leftIdx] < arr[rightIdx])
					temp[tempIdx++] = arr[leftIdx++];
				else
					temp[tempIdx++] = arr[rightIdx++];
			}

			while (leftIdx <= mid)
				temp[tempIdx++] = arr[leftIdx++];

			while (rightIdx <= right)
				temp[tempIdx++] = arr[rightIdx++];

			const std::size_t sortSize = (right - left + 1) * sizeof(std::size_t);
			memcpy_s(&arr[left], sortSize, &temp[left], sortSize);
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

	MergeSort sort;
	sort.DoTest(testCountNum, showProc);

	return 0;
}