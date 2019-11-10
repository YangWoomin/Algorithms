#pragma once

#include "MinimumSpanningTree.h"

namespace YangAlgorithms
{
	class Prim : public MinimumSpanningTree
	{
	public:
		Prim(std::size_t vertexCount, unsigned short min, unsigned short max);
		virtual ~Prim();
		Prim(const Graph& other);

		virtual void DoAlgorithm(std::size_t vertexNum) override;
		virtual void Show() override;
	};
}