#pragma once

#include "ShortestPath.h"

namespace YangAlgorithms
{
	class Floyd : public ShortestPath
	{
	private:
		void setCost(Graph& path, std::size_t first, std::size_t last, std::size_t from, std::size_t to);

	public:
		Floyd(std::size_t vertexCount, unsigned short min, unsigned short max);
		Floyd(const Graph& other);

		virtual void DoAlgorithm(std::size_t vertexNum) override;
		virtual void Show() override;
	};
}