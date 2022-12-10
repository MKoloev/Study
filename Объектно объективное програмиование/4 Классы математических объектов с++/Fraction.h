#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace xDlars
{
	class Fraction
	{
	//private:
	private:
		int NOD();//���������� ����� ���������
		void decomposition();//���������� � ���������� �����
		void reDecompositon();//���������� �������� � ������������ �����

	public:
		Fraction(int a = 0, int b = 1, int c = 0);

		//copy
		Fraction(const Fraction& fraction);
		Fraction& operator=(const Fraction& fraction);

		int A;
		int B;
		int C;

		void redication();//���������� �����

		Fraction& operator+=(const Fraction& drob);
		Fraction& operator-=(const Fraction& drob);
		Fraction& operator*=(const Fraction& drob);
		Fraction& operator/=(const Fraction& drob);

		friend Fraction operator+(const Fraction& A, const Fraction& B);//��������
		friend Fraction operator-(const Fraction& A, const Fraction& B);//��������
		friend Fraction operator*(const Fraction& A, const Fraction& B);//������������
		friend Fraction operator/(const Fraction& A, const Fraction& B);//������������

		void output();
	};
}

