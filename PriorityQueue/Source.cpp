#include "Header.h"

using namespace YangAlgorithms;

#include <iostream>

using namespace std;

int comparer(PriorityQueue::QueueItem& itemInQueue, PriorityQueue::QueueItem& newItem)
{
	return (int)itemInQueue - (int)newItem;
}

int main()
{
	PriorityQueue pq(100, comparer);

	pq.Push((PriorityQueue::QueueItem)1);
	pq.Push((PriorityQueue::QueueItem)11);
	pq.Push((PriorityQueue::QueueItem)15);
	pq.Push((PriorityQueue::QueueItem)31);
	pq.Push((PriorityQueue::QueueItem)7);
	pq.Push((PriorityQueue::QueueItem)3);
	pq.Push((PriorityQueue::QueueItem)22);

	for (PriorityQueue::QueueItem item = pq.Pop(); nullptr != item; item = pq.Pop())
	{
		std::cout << (int)item << " ";
	}

	std::cout << std::endl;

	return 0;
}