#pragma once

#include "Graph.h"

namespace YangAlgorithms
{
	class MinimumSpanningTree : public Graph
	{
	protected:
		Graph _result;

	public:
		MinimumSpanningTree(std::size_t vertexCount, unsigned short min, unsigned short max)
			: Graph(vertexCount, min, max), _result(0, 0, 0)
		{

		}

		Graph GetResult() const
		{
			return _result;
		}

		virtual void Show() override
		{
			std::cout << " * Current graph * " << std::endl;

			Graph::show_graph();

			if (false == _result.IsCreated())
				std::cout << "Call Prim::DoAlgorithm" << std::endl;
			else
			{
				std::cout << " * Order graph of selected edge * " << std::endl;
				_result.Show();
			}
		}

		bool IsSame(const MinimumSpanningTree* other)
		{
			for (std::size_t t = 0; t < _vertexCount; ++t)
			{
				for (std::size_t u = t + 1; u < _vertexCount; ++u)
				{
					if (INIT_VALUE != _result[t][u])
					{
						if(INIT_VALUE == (other->GetResult())[t][u] 
							&& INIT_VALUE == (other->GetResult()[u][t]))
							return false;
					}
				}
			}

			return true;
		}
	};
}