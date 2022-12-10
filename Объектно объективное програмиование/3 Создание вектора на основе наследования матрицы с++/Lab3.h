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

		bool possibilityPlus(const Matrix& matrix) const;//��������� ����������� �������� ������
		bool possibilityMultiplu(const Matrix& matrix) const;//��������� �� ����������� ��������� ������� �� ���
		static int counter;

		void goingOutLines(int i) const;

		class Row
		{
		public:
			Row(int numCl, int col, double* m1) : numberColums(numCl), index(col), line(m1) {}

			double const operator[](int col) const;// ������������ ��������� ����������
			double& operator[](int col);// ������������ ��������� ����������
		private:
			int numberColums;
			int index;
			double* line;
		};


	protected:
		double* array;
		int numberColums;

		bool ifNull() const;//��������� ������ �� �������

	public:
		//	Matrix();// �� ���������
		Matrix(int nL = 0, int nC = 0, double* array1 = nullptr);//����������� ��� ������������� ������� 
		Matrix(int number, double* array1);//����������� ��� ���������� ������� 

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


	class V_ector : public Matrix
	{
	private:


	public:
		V_ector(int nC = 0, double* array1 = nullptr) : Matrix(1, nC, array1) {}
		V_ector(const V_ector& vector);

		double const operator[](int col) const;// ������������ ��������� ����������
		double& operator[](int col);// ������������ ��������� ����������

		void operator+=(const V_ector& vector);//���������� ��������� ��� ������������� ���� ��������
		void operator-=(const V_ector& vector);//���������� ��������� ��� ������������� ���� ��������
		void operator*=(const V_ector& vector);//���������� ��������� ��� ������������� ���� ��������

		friend V_ector operator+(const V_ector& A, const V_ector& B);//�������� ������
		friend V_ector operator-(const V_ector& A, const V_ector& B);//�������� ������
		friend V_ector operator*(const V_ector& A, const V_ector& B);//������������ ������

		friend V_ector operator*(const V_ector& A, const double B);//��������� �� ������
		friend V_ector operator*(const double B, const V_ector& A);//��������� �� ������

		friend std::ostream& operator<< (std::ostream& out, const V_ector& vector);// ������� �� ����
	};
}
