#pragma once

#include "Graph.h"
#include <vector>

namespace YangAlgorithms
{
	class ShortestPath : public Graph
	{
	protected:
		struct Cost
		{
			std::size_t _nodeNum;
			int _cost;
			
			Cost(std::size_t nodeNum, int cost)
				: _nodeNum(nodeNum), _cost(cost)
			{

			}
		};
		typedef std::vector<std::vector<std::vector<Cost>>> ShortestPathResult;
		ShortestPathResult _result;

	private:
		

	public:
		ShortestPath(std::size_t vertexCount, unsigned short min, unsigned short max)
			: Graph(vertexCount, min, max)
		{

		}

		ShortestPathResult GetResult() const
		{
			return _result;
		}

		virtual void Show() override
		{
			std::cout << " * Current graph * " << std::endl;

			Graph::show_graph();

			std::cout << " * Cost result * " << std::endl;
			int totalCost = 0;
			for (std::size_t i = 0; i < _result.size(); ++i)
			{
				std::cout << " * " << i << " node's shortest path * " << std::endl;
				for (std::size_t j = 0; j < _result[i].size(); ++j)
				{
					if (i == j)
						continue;
					totalCost = 0;
					std::cout << " to " << j << " node path : ";
					for (std::size_t k = 0; k < _result[i][j].size(); ++k)
					{
						std::cout << _result[i][j][k]._nodeNum << "(" << _result[i][j][k]._cost << ")";
						totalCost += _result[i][j][k]._cost;
						if (k < _result[i][j].size() - 1)
							std::cout << " -> ";
					}
					std::cout << " total weight : " << totalCost << std::endl;
				}
			}
		}

		bool IsSame(const ShortestPath& other)
		{
			int sum1 = 0, sum2 = 0;
			for (std::size_t i = 0; i < _vertexCount; ++i)
			{
				for (std::size_t j = 0; j < _vertexCount; ++j)
				{
					if (i == j)
						continue;
					sum1 = sum2 = 0;
					for (std::size_t k = 0; k < _result[i][j].size(); ++k)
					{
						sum1 += _result[i][j][k]._cost;
					}
					for (std::size_t k = 0; k < other.GetResult()[i][j].size(); ++k)
					{
						sum2 += other.GetResult()[i][j][k]._cost;
					}
					if (sum1 != sum2)
					{
						return false;
					}
				}
			}

			return true;
		}
	};
}