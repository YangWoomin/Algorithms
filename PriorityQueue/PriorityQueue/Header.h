#pragma once

#include <cstddef>

namespace YangAlgorithms
{
	class PriorityQueue
	{
	public:
		typedef void* QueueItem;
		
	private:
		typedef int (*fnCompare)(QueueItem& /*existing item*/, QueueItem& /*new item*/);

		std::size_t _queueSize;
		std::size_t _last;
		QueueItem* _queue;
		fnCompare _comparer;

	public:
		PriorityQueue(std::size_t queueSize, fnCompare comparer)
			: _queueSize(queueSize), _last(0), _queue(nullptr), _comparer(comparer)
		{
			if(0 < queueSize)
				_queue = new QueueItem[queueSize + 1];
		}

		~PriorityQueue()
		{
			if (nullptr != _queue)
			{
				delete[] _queue;
				_queue = nullptr;
			}
			_queueSize = 0;
			_comparer = nullptr;
		}

		bool Push(QueueItem item)
		{
			if (_last >= _queueSize)
			{
				return false;
			}

			std::size_t index = ++_last;
			std::size_t parentIndex = _last / 2;
			while (0 < parentIndex && 0 < _comparer(_queue[parentIndex], item))
			{
				_queue[index] = _queue[parentIndex];
				index = parentIndex;
				parentIndex /= 2;
			}

			_queue[index] = item;
			return true;
		}

		QueueItem Pop()
		{
			if (1 > _last)
			{
				return nullptr;
			}

			QueueItem lastItem = _queue[_last--];
			if (0 == _last)
			{
				return lastItem;
			}

			QueueItem ret = _queue[1];
			std::size_t index = 2;
			if (_last >= index + 1 && 0 < _comparer(_queue[index], _queue[index + 1]))
				index++;
			while (_last >= index && 0 < _comparer(lastItem, _queue[index]))
			{
				_queue[index / 2] = _queue[index];
				index *= 2;
				if (_last >= index + 1 && 0 < _comparer(_queue[index], _queue[index + 1]))
					index++;
			}

			_queue[index / 2] = lastItem;
			return ret;
		}

		bool IsEmpty()
		{
			return 0 == _last;
		}
	};
}