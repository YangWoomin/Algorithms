#pragma once

#include <cstddef>
#include <iostream>
#include <ctime>
#include <stdio.h>

#include <vector>

namespace YangAlgorithms
{
	class Graph
	{
	protected:
		struct Edge
		{
			std::size_t from;
			std::size_t to;
			int value;
			Edge(std::size_t from, std::size_t to, int value)
				: from(from), to(to), value(value)
			{

			}
		};

		std::size_t _vertexCount;
		std::size_t _edgeCount;
		std::vector<std::vector<int>> _weights;

#define INFINITY_VALUE -1
#define INIT_VALUE 0

		virtual void show_graph()
		{
			std::cout << "[Graph] vertex count : " << _vertexCount << ", edge count : " << _edgeCount << std::endl;
			if (0 < _weights.size())
			{
				for (std::size_t t = 0; t < _vertexCount; ++t)
				{
					if (0 != t)
						for (std::size_t u = 0; u < _vertexCount * 6 - 1; ++u)
							std::cout << "-";
					std::cout << std::endl;

					for (std::size_t u = 0; u < _vertexCount; ++u)
					{
						printf("%4d ", _weights[t][u]);
						if (_vertexCount - 1 != u)
							std::cout << "|";
					}
					std::cout << std::endl;
				}
			}
			std::cout << std::endl;
		}

	private:
		void clear()
		{
			_weights.clear();
			_vertexCount = 0;
			_edgeCount = 0;
		}

		void create(std::size_t vertexCount, unsigned short min, unsigned short max, bool random)
		{
			if (2 > vertexCount)
				return;
			if (0 < _weights.size())
				clear();
			_vertexCount = vertexCount;
			_edgeCount = 0;
			_weights.resize(_vertexCount);
			srand((unsigned int)time(NULL));
			unsigned short num = 0;
			for (std::size_t t = 0; t < _vertexCount; ++t)
				_weights[t].resize(_vertexCount);

			for (std::size_t t = 0; t < _vertexCount; ++t)
			{
				if (true == random)
				{
					_weights[t][t] = INIT_VALUE;
					for (std::size_t u = t + 1; u < _vertexCount; ++u)
					{
						num = (double)rand() / (RAND_MAX + 1) * (max - min) + min;
						if (0 != num % 2)
						{
							while (true)
							{
								bool same = false;
								for (std::size_t i = 0; i <= t; ++i)
								{
									for (std::size_t j = i + 1; j < u; ++j)
									{
										if (_weights[i][j] == num || 0 == num % 2)
										{
											same = true;
											break;
										}
									}
									if (true == same)
										break;
								}
								if (false == same)
									break;
								num = (double)rand() / (RAND_MAX + 1) * (max - min) + min;
							}
							_weights[t][u] = num;
							_edgeCount++;
						}
						else
							_weights[t][u] = INFINITY_VALUE;
					}
				}
				else
				{
					for (std::size_t i = 0; i < _vertexCount; ++i)
						_weights[t][i] = INIT_VALUE;
				}
			}
			for (std::size_t t = 1; t < _vertexCount && random; ++t)
				for (std::size_t u = 0; u < t; ++u)
					_weights[t][u] = _weights[u][t];
		}

		void copy(const Graph& other)
		{
			if (true == other.IsCreated())
			{
				create(other.GetVertexCount(), 0, 0, false);
				_edgeCount = other.GetEdgeCount();
				for (std::size_t t = 0; t < _vertexCount; ++t)
					for (std::size_t u = 0; u < _vertexCount; ++u)
						_weights[t][u] = other[t][u];
			}
			else
				clear();
		}

	public:
		Graph(std::size_t vertexCount, unsigned short min, unsigned short max)
			: _vertexCount(vertexCount), _edgeCount(0)
		{
			create(vertexCount, min, max, true);
		}

		virtual ~Graph()
		{
			clear();
		}

		Graph(const Graph& other)
			: _vertexCount(0), _edgeCount(0)
		{
			copy(other);
		}

		Graph& operator=(const Graph& other)
		{
			copy(other);
			return *this;
		}

		std::size_t GetVertexCount() const
		{
			return _vertexCount;
		}

		std::vector<int>& operator[](const std::size_t index)
		{
			if (_vertexCount <= index)
			{
				std::cout << "Array index overrun" << std::endl;
				exit(1);
			}
			
			if (0 == _weights.size())
			{
				std::cout << "Array not allocated" << std::endl;
				exit(1);
			}

			return _weights[index];
		}

		std::vector<int> operator[](const std::size_t index) const
		{
			if (_vertexCount <= index)
			{
				std::cout << "Array index overrun" << std::endl;
				exit(1);
			}

			if (0 == _weights.size())
			{
				std::cout << "Array not allocated" << std::endl;
				exit(1);
			}

			return _weights[index];
		}

		bool IsCreated() const
		{
			return 0 < _weights.size();
		}

		std::size_t GetEdgeCount() const
		{
			return _edgeCount;
		}

		void Reset(int value = 0)
		{
			if (true == IsCreated())
			{
				for (std::size_t t = 0; t < _vertexCount; ++t)
					for (std::size_t u = 0; u < _vertexCount; ++u)
						_weights[t][u] = value;
			}
			_edgeCount = 0;
		}

		virtual void Create(std::size_t vertexCount, unsigned short min, unsigned short max)
		{
			create(vertexCount, min, max, true);
		}

		virtual void DoAlgorithm(std::size_t vertexNum)
		{

		}

		virtual void Show()
		{
			show_graph();
		}
	};
}