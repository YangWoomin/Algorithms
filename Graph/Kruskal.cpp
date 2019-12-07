#include "Kruskal.h"
#include "PriorityQueue/Header.h"

using namespace YangAlgorithms;

Kruskal::Kruskal(std::size_t vertexCount, unsigned short min, unsigned short max)
	: MinimumSpanningTree(vertexCount, min, max)
{

}

Kruskal::~Kruskal()
{

}

Kruskal::Kruskal(const Graph* other)
	: MinimumSpanningTree(0, 0, 0)
{
	*(Graph*)this = *other;
}

void Kruskal::DoAlgorithm(std::size_t vertexNum)
{
	if (true == IsCreated())
	{
		PriorityQueue queue(_edgeCount, [](PriorityQueue::QueueItem& item1, PriorityQueue::QueueItem& item2) -> int
			{
				return ((Edge*)item1)->value - ((Edge*)item2)->value;
			}
		);

		SetTree* setTrees = new SetTree[_vertexCount];
		for (std::size_t t = 0; t < _vertexCount; ++t)
		{
			setTrees[t].parent = nullptr;
			setTrees[t].setNum = t;

			for (std::size_t u = t + 1; u < _vertexCount; ++u)
			{
				if (INFINITY_VALUE != _weights[t][u])
					queue.Push(new Edge(t, u, _weights[t][u]));
			}
		}

		std::size_t order = 0;
		Edge* edge = nullptr;
		_result = *this;
		_result.Reset();
		while (nullptr != (edge = (Edge*)queue.Pop()) && order < _vertexCount)
		{
			SetTree* from = &setTrees[edge->from];
			while (nullptr != from->parent)
				from = from->parent;
			SetTree* to = &setTrees[edge->to];
			while (nullptr != to->parent)
				to = to->parent;
			if (from->setNum != to->setNum)
			{
				_result[edge->from][edge->to] = ++order;
				to->parent = from;
			}
			delete edge;
		}

		while (nullptr != (edge = (Edge*)queue.Pop()))
			delete edge;

		delete[] setTrees;
	}
}

void Kruskal::Show()
{
	std::string name = " Kruskal Algorithm ";
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
