#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <string>
#include <cmath>

typedef std::vector<int> Row;
typedef std::vector<int*> Col;

int MakeRandomNum(int min, int max)
{
	static bool init = false;
	if (false == init)
	{
		srand((unsigned int)time(NULL));
		init = true;
	}

	return (int)rand() % (max - min + 1) + min;
}

std::size_t Log2(std::size_t n)
{
	return (std::size_t)(log(n) / log(2));
}

int operator*(Row& row, Col&& col)
{
	int ret = 0;
	for (std::size_t i = 0; i < row.size(); ++i)
	{
		ret += (row[i] * (*col[i]));
	}
	return ret;
}

bool operator==(Row& row1, Row& row2)
{
	return std::equal(row1.begin(), row1.end(), row2.begin());
}

class Matrix
{
protected:
	std::vector<Row> rows;
	std::string name;
	std::size_t n = 0;
	std::size_t len = 0;

private:
	void SetSize()
	{
		len = n;
		if (false == std::_Is_pow_2(len))
		{
			len = (std::size_t)std::pow(2, Log2(len) + 1);
		}
		rows.resize(len, Row(len, 0));
	}

	void Set(Matrix&& C11, Matrix&& C12, Matrix&& C21, Matrix&& C22)
	{
		for (std::size_t i = 0; i < len / 2; ++i)
		{
			for (std::size_t j = 0; j < len / 2; ++j)
			{
				rows[i][j] = C11[i][j];
				rows[i][len / 2 + j] = C12[i][j];
				rows[len / 2 + i][j] = C21[i][j];
				rows[len / 2 + i][len / 2 + j] = C22[i][j];
			}
		}
	}

public:
	Matrix(std::size_t n, std::string name = "")
		: name(name), n(n)
	{
		SetSize();
	}

	// create the matrix with elements each of whose value is random
	Matrix(std::size_t n, int min, int max, std::string name = "")
		: name(name), n(n)
	{
		SetSize();

		for (std::size_t i = 0; i < n; ++i)
		{
			for (std::size_t j = 0; j < n; ++j)
			{
				rows[i][j] = MakeRandomNum(min, max);
			}
		}
	}

	void SetName(std::string name)
	{
		this->name = name;
	}

	std::string Name()
	{
		return name;
	}

	// access to a specified row
	Row& operator[](std::size_t num)
	{
		return rows[num];
	}

	// access to a specified column
	Col operator+(std::size_t num)
	{
		Col ret;
		for (std::vector<Row>::iterator it = rows.begin(); it != rows.end(); ++it)
		{
			ret.push_back(&(*it)[num]);
		}
		return ret;
	}

	bool operator==(Matrix& other)
	{
		for (std::size_t i = 0; i < n; ++i)
		{
			if (rows[i] != other[i])
			{
				return false;
			}
		}
		return true;
	}

	bool operator!=(Matrix& other)
	{
		return !operator==(other);
	}

	Matrix operator*(Matrix& other)
	{
		Matrix ret(n);

		for (std::size_t i = 0; i < n; ++i)
		{
			for (std::size_t j = 0; j < n; ++j)
			{
				ret[i][j] = rows[i] * (other + j);
			}
		}

		return ret;
	}

	Matrix operator+(Matrix& other)
	{
		Matrix ret(n);
		for (std::size_t i = 0; i < n; ++i)
		{
			for (std::size_t j = 0; j < n; ++j)
			{
				ret[i][j] = rows[i][j] + other[i][j];
			}
		}
		return ret;
	}

	Matrix operator-(Matrix& other)
	{
		Matrix ret(n);
		for (std::size_t i = 0; i < n; ++i)
		{
			for (std::size_t j = 0; j < n; ++j)
			{
				ret[i][j] = rows[i][j] - other[i][j];
			}
		}
		return ret;
	}

	void Strassen(Matrix& other)
	{
		if (1 < len)
		{
			Matrix A11(len / 2), A12(len / 2), A21(len / 2), A22(len / 2);
			Matrix B11(len / 2), B12(len / 2), B21(len / 2), B22(len / 2);
			for (std::size_t i = 0; i < len / 2; ++i)
			{
				for (std::size_t j = 0; j < len / 2; ++j)
				{
					A11[i][j] = (*this)[i][j];
					A12[i][j] = (*this)[i][len / 2 + j];
					A21[i][j] = (*this)[len / 2 + i][j];
					A22[i][j] = (*this)[len / 2 + i][len / 2 + j];
					B11[i][j] = other[i][j];
					B12[i][j] = other[i][len / 2 + j];
					B21[i][j] = other[len / 2 + i][j];
					B22[i][j] = other[len / 2 + i][len / 2 + j];
				}
			}

			Matrix M1 = A11 + A22, temp = B11 + B22;
			M1.Strassen(temp);
			Matrix M2 = A21 + A22;
			M2.Strassen(B11);
			Matrix M3 = A11; temp = B12 - B22;
			M3.Strassen(temp);
			Matrix M4 = A22; temp = B21 - B11;
			M4.Strassen(temp);
			Matrix M5 = A11 + A12;
			M5.Strassen(B22);
			Matrix M6 = A21 - A11; temp = B11 + B12;
			M6.Strassen(temp);
			Matrix M7 = A12 - A22; temp = B21 + B22;
			M7.Strassen(temp);

			Set(
				M1 + M4 - M5 + M7,
				M3 + M5,
				M2 + M4,
				M1 - M2 + M3 + M6
			);
		}
		else
		{
			rows[0][0] *= other[0][0];
		}
	}

	void Print(std::size_t width)
	{
		std::cout << "-------------------------------------------------------------------------" << std::endl;
		std::cout << "* " << name << std::endl << std::endl;
		for (std::size_t i = 0; i < n; ++i)
		{
			for (std::size_t j = 0; j < n; ++j)
			{
				std::cout << std::setw(width) << rows[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "-------------------------------------------------------------------------" << std::endl;
		std::cout << std::endl;
	}
};

int main()
{
	std::size_t n = MakeRandomNum(5, 7);
	Matrix MatrixA(n, -100, 100, "Matrix A");
	MatrixA.Print(4);
	Matrix MatrixB(n, -100, 100, "Matrix B");
	MatrixB.Print(4);
	Matrix MatrixC = MatrixA * MatrixB;
	MatrixC.SetName("MatrixC");
	MatrixC.Print(8);
	Matrix MatrixD = MatrixA;
	MatrixD.SetName("Matrix D");
	MatrixD.Strassen(MatrixB);
	MatrixD.Print(8);
	if (MatrixC != MatrixD)
	{
		std::cout << "[" + MatrixC.Name() + "] is not equal with [" + MatrixD.Name() + "]" << std::endl;
	}
	else
	{
		std::cout << "[" + MatrixC.Name() + "] is equal with [" + MatrixD.Name() + "]" << std::endl;
	}

	return 0;
}