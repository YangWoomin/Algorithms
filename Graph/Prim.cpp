#include "Prim.h"
#include "PriorityQueue/Header.h"

using namespace YangAlgorithms;

Prim::Prim(std::size_t vertexCount, unsigned short min, unsigned short max)
	: MinimumSpanningTree(vertexCount, min, max)
{

}

Prim::~Prim()
{
	
}

Prim::Prim(const Graph& other)
	: MinimumSpanningTree(0, 0, 0)
{
	*(Graph*)this = other;
}

void Prim::DoAlgorithm(std::size_t vertexNum)
{
	if (true == IsCreated() && vertexNum < _vertexCount)
	{
		_result = *this;
		_result.Reset();

#define CHECKED 1
#define TO_BE_CHECKED 0
		
		std::size_t* check = new std::size_t[_vertexCount];
		memset(check, TO_BE_CHECKED, sizeof(std::size_t) * _vertexCount);
		check[vertexNum] = CHECKED;

		PriorityQueue queue(_edgeCount, [] (PriorityQueue::QueueItem& item1, PriorityQueue::QueueItem& item2) -> int
			{
				return ((Edge*)item1)->value - ((Edge*)item2)->value;
			}
		);

		for (std::size_t t = 0; t < _vertexCount; ++t)
			if (t != vertexNum && INFINITY_VALUE != _weights[vertexNum][t])
				queue.Push(new Edge(vertexNum, t, _weights[vertexNum][t]));

		std::size_t order = 1;
		Edge* edge = nullptr;
		while (nullptr != (edge = (Edge*)queue.Pop()))
		{
			if (TO_BE_CHECKED == check[edge->to])
			{
				check[edge->to] = CHECKED;
				_result[edge->from][edge->to] = order++;
				for (std::size_t t = 0; t < _vertexCount; ++t)
					if (t != edge->to && INFINITY_VALUE != _weights[edge->to][t])
						if (TO_BE_CHECKED == check[t])
							queue.Push(new Edge(edge->to, t, _weights[edge->to][t]));
			}
			delete edge;
		}

		delete[] check;

#undef CHECKED
#undef TO_BE_CHECKED
	}
}

void Prim::Show()
{
	std::string name = " Prim Algorithm ";
	for (std::size_t t = 0; t < _vertexCount * 2; ++t)
		std::cout << "=";
	for (std::size_t t = 0; _vertexCount > name.size() && t < (_vertexCount - name.size()) / 2; ++t)
		std::cout << " ";
	std::cout << name;
	for (std::size_t t = 0; _vertexCount > name.size() && t < (_vertexCount - name.size()) / 2; ++t)
		std::cout << " ";
	for (std::size_t t = 0; t < _vertexCount * 2; ++t)
		std::cout << "=";
	std::cout << std::endl;

	MinimumSpanningTree::Show();
}
