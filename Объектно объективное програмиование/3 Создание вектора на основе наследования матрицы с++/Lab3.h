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
		int numberLines;
		int id;

		bool possibilityPlus(const Matrix& matrix) const;//проверяет возможность сложение матриц
		bool possibilityMultiplu(const Matrix& matrix) const;//проверяет на возможность умножение матрицы на эту
		static int counter;

		void goingOutLines(int i) const;

		class Row
		{
		public:
			Row(int numCl, int col, double* m1) : numberColums(numCl), index(col), line(m1) {}

			double const operator[](int col) const;// Перегружение оператара индексации
			double& operator[](int col);// Перегружение оператара индексации
		private:
			int numberColums;
			int index;
			double* line;
		};


	protected:
		double* array;
		int numberColums;

		bool ifNull() const;//проверяет пустая ли матрица

	public:
		//	Matrix();// по умолчанию
		Matrix(int nL = 0, int nC = 0, double* array1 = nullptr);//конструктор для прямоугольной матрицы 
		Matrix(int number, double* array1);//конструктор для квадратной матрицы 

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


	class V_ector : public Matrix
	{
	private:


	public:
		V_ector(int nC = 0, double* array1 = nullptr) : Matrix(1, nC, array1) {}
		V_ector(const V_ector& vector);

		double const operator[](int col) const;// Перегружение оператара индексации
		double& operator[](int col);// Перегружение оператара индексации

		void operator+=(const V_ector& vector);//перегрузка оператора для взаимодействи двух объектов
		void operator-=(const V_ector& vector);//перегрузка оператора для взаимодействи двух объектов
		void operator*=(const V_ector& vector);//перегрузка оператора для взаимодействи двух объектов

		friend V_ector operator+(const V_ector& A, const V_ector& B);//Сложение матриц
		friend V_ector operator-(const V_ector& A, const V_ector& B);//Вычитане матриц
		friend V_ector operator*(const V_ector& A, const V_ector& B);//Произведение матриц

		friend V_ector operator*(const V_ector& A, const double B);//умножение на скаляр
		friend V_ector operator*(const double B, const V_ector& A);//умножение на скаляр

		friend std::ostream& operator<< (std::ostream& out, const V_ector& vector);// Выводит на экра
	};
}
