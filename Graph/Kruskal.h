#pragma once

#include "MinimumSpanningTree.h"

namespace YangAlgorithms
{
	class Kruskal : public MinimumSpanningTree
	{
	private:
		struct SetTree
		{
			SetTree* parent;
			int setNum;

			SetTree()
				: parent(nullptr), setNum(0)
			{

			}
		};

	public:
		Kruskal(std::size_t vertexCount, unsigned short min, unsigned short max);
		virtual ~Kruskal();
		Kruskal(const Graph* other);

		virtual void DoAlgorithm(std::size_t vertexNum) override;
		virtual void Show() override;
	};
}