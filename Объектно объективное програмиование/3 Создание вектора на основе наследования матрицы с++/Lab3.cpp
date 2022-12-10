#include <iostream>
#include <iomanip>
#include "Lab3.h"
#include <string>

namespace xDlars
{
	int Matrix::counter = 0;

	//------------------------------------------------------------------------------------------------------------------

	Matrix::Matrix(int nL, int nC, double* array1)//конструктор для прямоугольной матрицы
	{
		if (nC > 0 && nL > 0 && array1 != nullptr)
		{
			array = new double[nC * nL];
			numberColums = nC;
			numberLines = nL;
			std::copy(array1, array1 + nC * nL, array);
		}
		else if (nC > 0 && nL > 0 && array1 == nullptr)
		{
			array = new double[nC * nL];
			numberColums = nC;
			numberLines = nL;
			for (int i = 0; i < nC * nL; i++)
				array[i] = 0;
		}
		else
		{
			numberColums = 0;
			numberLines = 0;
			array = nullptr;
		}
		counter++;
		id = counter;
		cout << "Constructor " << id << endl << endl;
	}

	Matrix::Matrix(int number, double* array1) : Matrix(number, number, array1) {}//конструктор для квадратной матрицы

	Matrix::Matrix(double (*comparisonFcn)(int, int, int, int), int nL, int nC) : Matrix(nL, nC)
	{
		if (nC > 0 && nL > 0 && comparisonFcn != nullptr)
		{
			for (int i = 0; i < nL; i++)
			{
				for (int j = 0; j < nC; j++)
				{
					array[i * nC + j] = comparisonFcn(nL, nC, i, j);
				}
			}
		}

	}

	Matrix::~Matrix()
	{
		if (array != nullptr)
		{
			delete[] array;
			array = nullptr;
		}
		cout << "Destructor " << id << endl;
	}

	//------------------------------------------------------------------------------------------------------------------
	// copy

	Matrix::Matrix(const Matrix& matrix) : Matrix(matrix.numberLines, matrix.numberColums, matrix.array) {} //коструктор копирования

	Matrix& Matrix::operator=(const Matrix& x)noexcept
	{
		if (this == &x)
			return *this;

		int sz = x.numberColums * x.numberLines;

		if (numberColums * numberLines != sz)
		{
			if (array != nullptr)
				delete[] array;

			array = sz > 0 ? new double[sz] : nullptr;
		}

		numberColums = x.numberColums;
		numberLines = x.numberLines;

		if (sz > 0)
			std::copy(x.array, x.array + sz, array);
		return *this;
	}

	//------------------------------------------------------------------------------------------------------------------
	// move

	Matrix::Matrix(Matrix&& x) noexcept : Matrix(0, 0, nullptr)
	{
		*this = std::move(x);
	}

	Matrix& Matrix::operator=(Matrix&& x) noexcept
	{
		// Проверка на самоприсваивание
		if (&x == this)
			return *this;

		// Удаляем всё, что к этому моменту может хранить указатель
		if (array != nullptr)
		{
			delete[] array;
			array = nullptr;
		}
		numberColums = x.numberColums;
		numberLines = x.numberLines;

		// Передаем право собственности на x.array в array
		if (x.array != nullptr)
		{
			array = std::move(x.array);
			x.array = nullptr;
			x.numberColums = 0;
			x.numberLines = 0;
		}

		return *this;
	}

	//------------------------------------------------------------------------------------------------------------------

	int Matrix::sizeColums() const
	{
		return numberColums;
	}

	int Matrix::sizeLines() const
	{
		return numberLines;
	}

	//------------------------------------------------------------------------------------------------------------------

	double Matrix::outputMax()
	{
		exceptionH("outputMax");//провепка на исключение

		double maxElim = array[0];
		for (int i = 1; i < numberColums * numberLines; i++)
		{
			if (maxElim < array[i])
				maxElim = array[i];
		}
		return maxElim;
	}

	double Matrix::outputMin()
	{
		exceptionH("outputMin ");//провепка на исключение

		double minElim = array[0];
		for (int i = 1; i < numberColums * numberLines; i++)
		{
			if (minElim > array[i])
				minElim = array[i];
		}
		return minElim;
	}

	//------------------------------------------------------------------------------------------------------------------

	Matrix::Row Matrix::operator[](int i)
	{
		goingOutLines(i);
		return Row(numberColums, i, array + numberColums * i);
	}

	Matrix::Row const Matrix::operator[](int i) const
	{
		goingOutLines(i);
		return Row(numberColums, i, array + numberColums * i);
	}

	// обработка исключения выход за границы
	void Matrix::goingOutLines(int i) const
	{
		if (i >= numberLines)
			cout << "operator[] : Matrix(" + std::to_string(id) + ") : Matrix is NULL";
	}

	double& Matrix::Row::operator[](int col)
	{
		if (col <= numberColums && col >= 0)
			return line[col];
		else
		{
			cout << "going abroad" << endl;
			return line[col];
		}
	}

	double const Matrix::Row::operator[](int col) const
	{
		if (col <= numberColums && col >= 0)
			return line[col];
		else
		{
			cout << "going abroad" << endl;
			return 0;
		}
	}

	//------------------------------------------------------------------------------------------------------------------

	bool Matrix::possibilityPlus(const Matrix& matrix) const
	{
		exceptionH("possibilityPlus");//провепка на исключение

		if ((numberColums == matrix.sizeColums()) && (numberLines == matrix.sizeLines()))
			return true;
		else
		{
			cout << "additionand negation of matrices is not possible" << endl;
			return false;
		}
	}

	bool Matrix::possibilityMultiplu(const Matrix& matrix) const
	{
		exceptionH("possibilityMultiplu");//провепка на исключение

		if (numberColums == matrix.sizeLines())
			return true;
		else
		{
			cout << "matrix multiplication is not possible" << endl;
			return false;
		}
	}

	bool Matrix::ifNull() const
	{
		if (array == nullptr)
		{
			cout << "Matrix empty" << endl;
			return true;
		}
		else
			return false;
	}

	//------------------------------------------------------------------------------------------------------------------

	void Matrix::operator+=(const Matrix& matrix)
	{
		exceptionH("operator+=");
		if (possibilityPlus(matrix))
		{
			for (int i = 0; i < numberLines * numberColums; i++)
			{
				array[i] += matrix.array[i];
			}
		}
	}

	void Matrix::operator-=(const Matrix& matrix)
	{
		exceptionH("operator-=");
		if (possibilityPlus(matrix))
		{
			for (int i = 0; i < numberLines * numberColums; i++)
			{
				array[i] -= matrix.array[i];
			}
		}
	}

	void Matrix::operator*=(const Matrix& matrix)
	{
		exceptionH("operator*=");
		if (possibilityMultiplu(matrix))
		{
			double element = 0.0;
			double* newArray = new double[numberLines * matrix.sizeColums()];
			for (int i = 0; i < numberLines; i++)
			{
				for (int j = 0; j < matrix.sizeColums(); j++)
				{
					element = 0.0;
					for (int t = 0; t < numberColums; t++)
					{
						element += array[i * numberColums + t] * matrix[t][j];
					}
					newArray[i * matrix.sizeColums() + j] = element;
				}
			}
			numberColums = matrix.sizeColums();
			if (array != nullptr)
				array = nullptr;
			array = newArray;
			newArray = nullptr;
		}
	}

	// обрабтывает исключения пыстой матрицы
	void Matrix::exceptionH(string name) const
	{
		if (ifNull())
			throw  name + " : Matrix(" + std::to_string(id) + ") : Matrix is NULL";
	}

	//------------------------------------------------------------------------------------------------------------------

	Matrix operator+(const Matrix& A, const Matrix& B)
	{
		//return std::move(Matrix(A) += B); не работает
		Matrix C(A);
		cout << C << endl;
		C += B;
		return C;
	}

	Matrix operator-(const Matrix& A, const Matrix& B)
	{
		//return std::move(Matrix(A) -= B);  и  return Matrix(A) -= B; не работают
		Matrix C(A);
		cout << C << endl;
		C -= B;
		return C;
	}

	Matrix operator*(const Matrix& A, const Matrix& B)
	{
		Matrix C(A);
		cout << C << endl;
		C *= B;
		return C;
	}

	Matrix operator*(const Matrix& A, const double B)
	{
		Matrix C(A);
		cout << C << endl;
		for (int i = 0; i < C.sizeColums() * C.sizeLines(); i++)
		{
			C.array[i] *= B;
		}
		return C;
	}

	Matrix operator*(const double B, const Matrix& A)
	{
		Matrix C;
		C = A * B;
		return C;
	}

	//------------------------------------------------------------------------------------------------------------------

	std::ostream& operator<< (std::ostream& out, const Matrix& matrix)
	{
		matrix.exceptionH("operator<<");
		for (int i = 0; i < matrix.numberLines; i++)
		{
			for (int j = 0; j < matrix.numberColums; j++)
			{
				cout << std::setw(15) << matrix.array[matrix.numberColums * i + j];
			}
			cout << endl;
		}
		return out;
	}



//---------------------------------------------------------------------------
//Vector


	V_ector::V_ector(const V_ector& vector) :V_ector(vector.numberColums, vector.array) {}

	//------------------------------------------------------------------------------------------------------------------
	double& V_ector::operator[](int col)
	{
		if (col <= numberColums && col >= 0)
			return array[col];
		else
		{
			cout << "going abroad" << endl;
			return array[col];
		}
	}

	double const V_ector::operator[](int col) const
	{
		if (col <= numberColums && col >= 0)
			return array[col];
		else
		{
			cout << "going abroad" << endl;
			return 0;
		}
	}


	//------------------------------------------------------------------------------------------------------------------

	void V_ector::operator+=(const V_ector& vector)
	{
		exceptionH("operator+=");
		if (vector.numberColums == numberColums)
		{
			for (int i = 0; i < numberColums; i++)
			{
				array[i] += vector.array[i];
			}
		}
		else
			cout << "additionand negation of matrices is not possible" << endl;
	}

	void V_ector::operator-=(const V_ector& vector)
	{
		exceptionH("operator-=");
		if (vector.numberColums == numberColums)
		{
			for (int i = 0; i < numberColums; i++)
			{
				array[i] -= vector.array[i];
			}
		}
		else
			cout << "additionand negation of matrices is not possible" << endl;
	}

	void V_ector::operator*=(const V_ector& vector)
	{
		exceptionH("operator*=");
		if (vector.numberColums == numberColums)
		{
			for (int i = 0; i < numberColums; i++)
			{
				array[i] *= vector.array[i];
			}
		}
		else
			cout << "matrix multiplication is not possible" << endl;
	}

	//------------------------------------------------------------------------------------------------------------------

	V_ector operator+(const V_ector& A, const V_ector& B)
	{
		//return std::move(Matrix(A) += B); не работает
		V_ector C(A);
		cout << C << endl;
		C += B;
		return C;
	}

	V_ector operator-(const V_ector& A, const V_ector& B)
	{
		//return std::move(Matrix(A) -= B);  и  return Matrix(A) -= B; не работают
		V_ector C(A);
		cout << C << endl;
		C -= B;
		return C;
	}

	V_ector operator*(const V_ector& A, const V_ector& B)
	{
		V_ector C(A);
		cout << C << endl;
		C *= B;
		return C;
	}

	V_ector operator*(const V_ector& A, const double B)
	{
		V_ector C(A);
		for (int i = 0; i < C.numberColums; i++)
		{
			C.array[i] *= B;
		}
		return C;
	}

	V_ector operator*(const double B, const V_ector& A)
	{
		V_ector C(A);
		for (int i = 0; i < C.numberColums; i++)
		{
			C.array[i] *= B;
		}
		return C;
	}



	std::ostream& operator<< (std::ostream& out, const V_ector& vector)
	{
		vector.exceptionH("operator<<");
		for (int j = 0; j < vector.numberColums; j++)
		{
			cout << std::setw(15) << vector.array[j];
		}
		cout << endl;
	
		return out;
	}

}
