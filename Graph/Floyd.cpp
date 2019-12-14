#include "Floyd.h"

using namespace YangAlgorithms;

void Floyd::setCost(Graph& path, std::size_t first, std::size_t last, std::size_t from, std::size_t to)
{
	if (INFINITY_VALUE != path[from][to])
	{
		setCost(path, first, last, from, path[from][to]);
		setCost(path, first, last, path[from][to], to);
	}
	else // nothing between from and to
	{
		if(INFINITY_VALUE != _weights[from][to])
			_result[first][last].push_back(Cost(to, _weights[from][to]));
	}
}

Floyd::Floyd(std::size_t vertexCount, unsigned short min, unsigned short max)
	: ShortestPath(vertexCount, min, max)
{

}

Floyd::Floyd(const Graph& other)
	: ShortestPath(0, 0, 0)
{
	*(Graph*)this = other;
}

void Floyd::DoAlgorithm(std::size_t vertexNum)
{
	if (true == IsCreated())
	{
		Graph totalCost = *this;
		Graph path = *this;
		path.Reset(INFINITY_VALUE);

		for (std::size_t i = 0; i < _vertexCount; ++i)
		{
			for (std::size_t j = 0; j < _vertexCount; ++j)
			{
				for (std::size_t k = 0; k < _vertexCount; ++k)
				{
					if (INFINITY_VALUE != totalCost[j][i] && INFINITY_VALUE != totalCost[i][k])
					{
						if (INFINITY_VALUE == totalCost[j][k] || totalCost[j][i] + totalCost[i][k] < totalCost[j][k])
						{
							totalCost[j][k] = totalCost[j][i] + totalCost[i][k];
							path[j][k] = i;
						}
					}
				}
			}
		}

		_result.clear();
		_result.resize(_vertexCount);
		for (std::size_t t = 0; t < _vertexCount; ++t)
		{
			_result[t].resize(_vertexCount);

			for (std::size_t k = 0; k < _vertexCount; ++k)
			{
				setCost(path, t, k, t, k);
			}
		}
	}
}

void Floyd::Show()
{
	std::string name = " Floyd Algorithm ";
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
