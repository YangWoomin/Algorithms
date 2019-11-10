#include "Dijkstra.h"
#include "PriorityQueue/Header.h"

using namespace YangAlgorithms;

Dijkstra::Dijkstra(std::size_t vertexCount, unsigned short min, unsigned short max)
	: ShortestPath(vertexCount, min, max), _totalVertex(false)
{

}

Dijkstra::Dijkstra(const Graph& other)
	: ShortestPath(0, 0, 0), _totalVertex(false)
{
	*(Graph*)this = other;
}

void Dijkstra::SetTotalVertex(bool value)
{
	_totalVertex = value;

	if (true == _totalVertex)
	{
		_result.clear();
		_result.resize(_vertexCount);
	}
}

void Dijkstra::DoAlgorithm(std::size_t vertexNum)
{
	if (true == IsCreated() && vertexNum < _vertexCount)
	{
		if (false == _totalVertex)
		{
			_result.clear();
			_result.resize(_vertexCount);
		}

		_result[vertexNum].clear();
		_result[vertexNum].resize(_vertexCount);


#define CHECKED 1
#define TO_BE_CHECKED 0

		std::vector<Edge> cost;
		std::vector<std::size_t> check(_vertexCount, TO_BE_CHECKED);
		std::size_t checkCount = 1;

		for (std::size_t i = 0; i < _vertexCount; ++i)
		{
			Edge edge(vertexNum, i, _weights[vertexNum][i]);
			cost.push_back(edge);
		}

		check[vertexNum] = CHECKED;

		int weight;
		std::size_t target = 0;
		while (checkCount < _vertexCount)
		{
			weight = INFINITY_VALUE;
			for (std::size_t i = 0; i < _vertexCount; ++i)
			{
				if (0 < cost[i].value && TO_BE_CHECKED == check[i])
				{
					if (INFINITY_VALUE == weight || cost[i].value < weight)
					{
						weight = cost[i].value;
						target = i;
					}
				}
			}

			if (INFINITY_VALUE == weight)
				break;

			check[target] = CHECKED;
			checkCount++;
			std::vector<Cost>& targetVec = _result[vertexNum][target];
			std::vector<Cost>& fromVec = _result[vertexNum][cost[target].from];
			targetVec.insert(targetVec.begin(), fromVec.begin(), fromVec.end());
			targetVec.push_back(Cost(target, _weights[cost[target].from][target]));

			for (std::size_t i = 0; i < _vertexCount; ++i)
			{
				if (0 < _weights[target][i])
				{
					if (INFINITY_VALUE == cost[i].value || _weights[target][i] + cost[target].value < cost[i].value)
					{
						cost[i].from = target;
						cost[i].value = cost[target].value + _weights[target][i];
					}
				}
			}
		}

#undef CHECKED
#undef TO_BE_CHECKED
	}
}

void Dijkstra::Show()
{
	std::string name = " Dijkstra Algorithm ";
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

	ShortestPath::Show();

	std::cout << std::endl;
}
