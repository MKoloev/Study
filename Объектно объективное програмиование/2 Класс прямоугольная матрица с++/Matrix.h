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

		bool ifNull() const;//��������� ������ �� �������
		void goingOutLines(int i) const;

		class Row
		{
		public:
			Row(int numCl, int col, double* m1) : numberColums(numCl), index(col), line(m1) {}

			double const operator[](int col) const;// ������������ ��������� ����������
			double &operator[](int col);// ������������ ��������� ����������
		private:
			int numberColums;
			int index;
			double* line;
		};

	public:
	//	Matrix();// �� ���������
		Matrix(int nL = 0, int nC = 0, double* array1 = nullptr);//����������� ��� ������������� ������� 
		Matrix(int number, double* array1 );//����������� ��� ���������� ������� 
	//	Matrix(int nL, int nC);

		Matrix(double (*comparisonFcn)(int, int, int, int), int nL, int nC);

		~Matrix();

		// copy
		Matrix(const Matrix& matrix);
		Matrix& operator=(const Matrix& x) noexcept;

		// move
		Matrix(Matrix&& x) noexcept;
		Matrix& operator=(Matrix&& x) noexcept;

		int sizeLines() const;// ������� ����������� �����
		int sizeColums() const;// ������� ����������� ��������

		Row const operator[] (int i) const;// ������������ ��������� ����������
		Row operator[] (int i);// ������������ ��������� ����������

		double outputMin();//������� ����������� ������� �������
		double outputMax();//������� ������������ ������� �������

		bool possibilityPlus(const Matrix& matrix) const;//��������� ����������� �������� ������
		bool possibilityMultiplu(const Matrix& matrix) const;//��������� �� ����������� ��������� ������� �� ���

		void operator+=(const Matrix& matrix);//���������� ��������� ��� ������������� ���� ��������
		void operator-=(const Matrix& matrix);//���������� ��������� ��� ������������� ���� ��������
		void operator*=(const Matrix& matrix);//���������� ��������� ��� ������������� ���� ��������

		void exceptionH(string name) const;//����������� ���������� ������ �������

		friend Matrix operator+(const Matrix& A, const Matrix& B);//�������� ������
		friend Matrix operator-(const Matrix& A, const Matrix& B);//�������� ������
		friend Matrix operator*(const Matrix& A, const Matrix& B);//������������ ������

		friend Matrix operator*(const Matrix& A, const double B);//��������� �� ������
		friend Matrix operator*(const double B, const Matrix& A);//��������� �� ������

		friend std::ostream& operator<< (std::ostream& out, const Matrix& matrix);// ������� �� ���� ��� �������
	};
}
