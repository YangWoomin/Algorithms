#pragma once

#include "ShortestPath.h"

namespace YangAlgorithms
{
	class Dijkstra : public ShortestPath
	{
	private:
		bool _totalVertex;

	public:
		Dijkstra(std::size_t vertexCount, unsigned short min, unsigned short max);
		Dijkstra(const Graph& other);

		void SetTotalVertex(bool value);
		virtual void DoAlgorithm(std::size_t vertexNum) override;
		virtual void Show() override;
	};
}