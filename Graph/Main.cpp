#include "Prim.h"
#include "Kruskal.h"
#include "Dijkstra.h"
#include "Floyd.h"

using namespace YangAlgorithms;

int main()
{
	Prim prim(8, 1, 500);
	prim.DoAlgorithm(1);
	prim.Show();

	Kruskal kruskal = (Graph*)&prim;
	kruskal.DoAlgorithm(0);
	kruskal.Show();

	if (true == kruskal.IsSame((MinimumSpanningTree*)& prim))
		std::cout << "prim and kruskal result is same!" << std::endl;
	else
		std::cout << "prim and kruskal result is different!" << std::endl;

	std::cout << std::endl;

	while (true)
	{
		Dijkstra dijkstra(8, 1, 500);
		dijkstra.SetTotalVertex(true);
		for (std::size_t t = 0; t < dijkstra.GetVertexCount(); ++t)
		{
			dijkstra.DoAlgorithm(t);
		}
		dijkstra.Show();

		Floyd floyd = (Graph)dijkstra;
		floyd.DoAlgorithm(1);
		floyd.Show();

		if (true == dijkstra.IsSame(floyd))
		{
			std::cout << "dijkstra and floyd result is same!" << std::endl;
		}
		else
		{
			std::cout << "dijkstra and floyd result is different!" << std::endl;
		}
	}
	

	return 0;
}