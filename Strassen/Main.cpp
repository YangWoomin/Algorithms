#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <string>
#include <cmath>

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

class Matrix
{
private:
	int** _values = nullptr;
	std::size_t _size = 0;
	std::size_t _n = 0;
	bool _useStrassen = false;

	void SetSizeToPowOf2()
	{
		_size = _n;
		if (false == std::_Is_pow_2(_size))
		{
			_size = (std::size_t)std::pow(2, Log2(_size) + 1);
		}
	}

	void Reset()
	{
		if (nullptr != _values)
		{
			for (std::size_t i = 0; i < _size; ++i)
			{
				if (nullptr != _values[i])
				{
					delete[] _values[i];
				}
			}

			delete[] _values;
		}
		_size = 0;
		_n = 0;
		_useStrassen = false;
	}

	void Copy(const Matrix& other)
	{
		_size = other._size;
		_n = other._n;
		_useStrassen = other._useStrassen;

		_values = new int* [_size];
		for (std::size_t i = 0; i < _size; ++i)
		{
			_values[i] = new int[_size];
			for (std::size_t j = 0; j < _size; ++j)
			{
				_values[i][j] = other[i][j];
			}
		}
	}

public:
	// create a matrix with elements each of whose value is random
	Matrix(std::size_t n, int min, int max)
		: _n(n)
	{
		SetSizeToPowOf2();

		_values = new int*[_size];
		for (std::size_t i = 0; i < _size; ++i)
		{
			_values[i] = new int[_size];
			for (std::size_t j = 0; j < _size; ++j)
			{
				_values[i][j] = MakeRandomNum(min, max);
			}
		}
	}

	Matrix(std::size_t n)
		: _n(n)
	{
		SetSizeToPowOf2();

		_values = new int*[_size];
		for (std::size_t i = 0; i < _size; ++i)
		{
			_values[i] = new int[_size];
			for (std::size_t j = 0; j < _size; ++j)
			{
				_values[i][j] = 0;
			}
		}
	}

	Matrix(const Matrix& other)
	{
		Copy(other);
	}

	Matrix& operator=(const Matrix& other)
	{
		Reset();
		Copy(other);
	}

	Matrix(const Matrix&& other) noexcept
	{
		Copy(other);
	}

	Matrix& operator=(const Matrix&& other) noexcept
	{
		Reset();
		Copy(other);
	}

	virtual ~Matrix()
	{
		Reset();
	}

	int* operator[](std::size_t idx) const
	{
		return _values[idx];
	}

	bool operator==(const Matrix& other) const
	{
		for (std::size_t i = 0; i < _size; ++i)
		{
			for (std::size_t j = 0; j < _size; ++j)
			{
				if (_values[i][j] != other[i][j])
				{
					return false;
				}
			}
		}

		return true;
	}

	Matrix& operator*=(const Matrix& other)
	{
		if (false == _useStrassen)
		{
			Matrix temp(*this);
			for (std::size_t i = 0; i < _size; ++i)
			{
				for (std::size_t j = 0; j < _size; ++j)
				{
					int sum = 0;
					for (std::size_t k = 0; k < _size; ++k)
					{
						sum += (temp[i][k] * other[k][j]);
					}
					(*this)[i][j] = sum;
				}
			}
		}
		else
		{
			Strassen(other, 0, 0, 0, 0);
		}
		return *this;
	}

	Matrix operator*(const Matrix& other) const
	{
		Matrix res(*this);
		res *= other;
		return res;
	}

public:
	void SetUseStrassen(bool value)
	{
		_useStrassen = value;
	}

	void Print(std::size_t width) const
	{
		std::cout << "-------------------------------------------------------------------------" << std::endl;
		for (std::size_t i = 0; i < _n; ++i)
		{
			for (std::size_t j = 0; j < _n; ++j)
			{
				std::cout << std::setw(width) << _values[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "-------------------------------------------------------------------------" << std::endl;
		std::cout << std::endl;
	}

	// for strassen
private:
	typedef int (*Calculate)(int, int);
	static int Add(int value1, int value2)
	{
		return value1 + value2;
	}
	static int Sub(int value1, int value2)
	{
		return value1 - value2;
	}
	static int Set(int value1, int value2)
	{
		return value2;
	}

	Matrix(const Matrix& other, std::size_t row1, std::size_t col1, std::size_t row2, std::size_t col2, std::size_t size, Calculate cal)
	{
		_n = _size = size;
		_useStrassen = other._useStrassen; // it must be true

		_values = new int*[_size];
		for (std::size_t i = 0; i < _size; ++i)
		{
			_values[i] = new int[_size];
			for (std::size_t j = 0; j < _size; ++j)
			{
				_values[i][j] = cal(other[row1 + i][col1 + j], other[row2 + i][col2 + j]);
			}
		}
	}

	Matrix(const Matrix& other, std::size_t row, std::size_t col, std::size_t size)
	{
		_n = _size = size;
		_useStrassen = other._useStrassen;

		_values = new int*[_size];
		for (std::size_t i = 0; i < _size; ++i)
		{
			_values[i] = new int[_size];
			for (std::size_t j = 0; j < _size; ++j)
			{
				_values[i][j] = other[row + i][col + j];
			}
		}
	}

	void Calc(const Matrix& other, std::size_t row, std::size_t rowCount, std::size_t col, std::size_t colCount, Calculate cal)
	{
		for (std::size_t i = 0; i < rowCount; ++i)
		{
			for (std::size_t j = 0; j < colCount; ++j)
			{
				_values[row + i][col + j] = cal(_values[row + i][col + j], other[i][j]);
			}
		}
	}

	void Strassen(const Matrix& other, std::size_t thisRow, std::size_t thisCol, std::size_t otherRow, std::size_t otherCol)
	{
		// reference : https://ko.wikipedia.org/wiki/%EC%8A%88%ED%8A%B8%EB%9D%BC%EC%84%BC_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98

		if (1 < _size)
		{
			std::size_t half = _size / 2;

			Matrix M1(*this, thisRow, thisCol, thisRow + half, thisCol + half, half, Add); // M1 = A11 + A22
			M1.Strassen(Matrix(other, otherRow, otherCol, otherRow + half, otherCol + half, half, Add), 0, 0, 0, 0); // M1 *= (B11 + B22)

			Matrix M2(*this, thisRow + half, thisCol, thisRow + half, thisCol + half, half, Add); // M2 = A21 + A22
			M2.Strassen(other, 0, 0, otherRow, otherCol); // M2 *= B11

			Matrix M3(*this, thisRow, thisCol, half); // M3 = A11
			M3.Strassen(Matrix(other, otherRow, otherCol + half, otherRow + half, otherCol + half, half, Sub), 0, 0, 0, 0); // M3 *= (B12 - B22)

			Matrix M4(*this, thisRow + half, thisCol + half, half); // M4 = A22
			M4.Strassen(Matrix(other, otherRow + half, otherCol, otherRow, otherCol, half, Sub), 0, 0, 0, 0); // M4 *= (B21 - B11)

			Matrix M5(*this, thisRow, thisCol, thisRow, thisCol + half, half, Add); // M5 = A11 + A12
			M5.Strassen(other, 0, 0, otherRow + half, otherCol + half); // M5 *= B22

			Matrix M6(*this, thisRow + half, thisCol, thisRow, thisCol, half, Sub); // M6 = A21 - A11
			M6.Strassen(Matrix(other, otherRow, otherCol, otherRow, otherCol + half, half, Add), 0, 0, 0, 0); // M6 *= (B11 + B12)

			Matrix M7(*this, thisRow, thisCol + half, thisRow + half, thisCol + half, half, Sub); // M7 = A12 - A22
			M7.Strassen(Matrix(other, otherRow + half, otherCol, otherRow + half, otherCol + half, half, Add), 0, 0, 0, 0); // M7 *= (B21 + B22)

			// for C11
			Calc(M1, 0, half, 0, half, Set); // C11 = M1
			Calc(M4, 0, half, 0, half, Add); // C11 += M4
			Calc(M5, 0, half, 0, half, Sub); // C11 -= M5
			Calc(M7, 0, half, 0, half, Add); // C11 += M7

			// for C12
			Calc(M3, 0, half, half, half, Set); // C12 = M3
			Calc(M5, 0, half, half, half, Add); // C12 += M5

			// for C21
			Calc(M2, half, half, 0, half, Set); // C21 = M2
			Calc(M4, half, half, 0, half, Add); // C21 += M4

			// for C22
			Calc(M1, half, half, half, half, Set); // C22 = M1
			Calc(M2, half, half, half, half, Sub); // C22 -= M2
			Calc(M3, half, half, half, half, Add); // C22 += M3
			Calc(M6, half, half, half, half, Add); // C22 += m6
		}
		else
		{
			_values[thisRow][thisCol] *= other[otherRow][otherCol];
		}
	}

	void Strassen(const Matrix&& other, std::size_t row1, std::size_t col1, std::size_t row2, std::size_t col2)
	{
		Strassen(other, row1, col1, row2, col2);
	}
};

int main()
{
	for (std::size_t i = 0; i < 100000; ++i)
	{
		Matrix A(4, -10, 10);
		Matrix B(4, -10, 10);

		A.Print(5);
		B.Print(5);

		A.SetUseStrassen(true);
		Matrix C = A * B;

		A.SetUseStrassen(false);
		Matrix D = A * B;

		C.Print(5);
		D.Print(5);

		if (C == D)
		{
			std::cout << "Strassen succeeded." << std::endl;
		}
		else
		{
			std::cout << "Strassen failed." << std::endl;
			break;
		}
	}

	return 0;
}
