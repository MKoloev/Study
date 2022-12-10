#pragma once
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

namespace xDlars
{
	class Matrix
	{
	private:
		double* array;
		int numberColums;
		int numberLines;
		int id;
		static int counter;

		bool ifNull() const;//проверяет пустая ли матрица
		void goingOutLines(int i) const;

		class Row
		{
		public:
			Row(int numCl, int col, double* m1) : numberColums(numCl), index(col), line(m1) {}

			double const operator[](int col) const;// Перегружение оператара индексации
			double &operator[](int col);// Перегружение оператара индексации
		private:
			int numberColums;
			int index;
			double* line;
		};

	public:
	//	Matrix();// по умолчанию
		Matrix(int nL = 0, int nC = 0, double* array1 = nullptr);//конструктор для прямоугольной матрицы 
		Matrix(int number, double* array1 );//конструктор для квадратной матрицы 
	//	Matrix(int nL, int nC);

		Matrix(double (*comparisonFcn)(int, int, int, int), int nL, int nC);

		~Matrix();

		// copy
		Matrix(const Matrix& matrix);
		Matrix& operator=(const Matrix& x) noexcept;

		// move
		Matrix(Matrix&& x) noexcept;
		Matrix& operator=(Matrix&& x) noexcept;

		int sizeLines() const;// выводит колличество строк
		int sizeColums() const;// выводит колличество столбцов

		Row const operator[] (int i) const;// Перегружение оператара индексации
		Row operator[] (int i);// Перегружение оператара индексации

		double outputMin();//выводит минимальный элимент матрицы
		double outputMax();//выводит максимальный элимент матрицы

		bool possibilityPlus(const Matrix& matrix) const;//проверяет возможность сложение матриц
		bool possibilityMultiplu(const Matrix& matrix) const;//проверяет на возможность умножение матрицы на эту

		void operator+=(const Matrix& matrix);//перегрузка оператора для взаимодействи двух объектов
		void operator-=(const Matrix& matrix);//перегрузка оператора для взаимодействи двух объектов
		void operator*=(const Matrix& matrix);//перегрузка оператора для взаимодействи двух объектов

		void exceptionH(string name) const;//обрабтывает исключения пыстой матрицы

		friend Matrix operator+(const Matrix& A, const Matrix& B);//Сложение матриц
		friend Matrix operator-(const Matrix& A, const Matrix& B);//Вычитане матриц
		friend Matrix operator*(const Matrix& A, const Matrix& B);//Произведение матриц

		friend Matrix operator*(const Matrix& A, const double B);//умножение на скаляр
		friend Matrix operator*(const double B, const Matrix& A);//умножение на скаляр

		friend std::ostream& operator<< (std::ostream& out, const Matrix& matrix);// Выводит на экра всю матрицу
	};
}
