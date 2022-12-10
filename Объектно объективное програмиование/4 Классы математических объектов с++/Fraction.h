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
		int NOD();//наибольший обший множитель
		void decomposition();//приведение в правильную дробь
		void reDecompositon();//приведение обратнов в неправильную дробь

	public:
		Fraction(int a = 0, int b = 1, int c = 0);

		//copy
		Fraction(const Fraction& fraction);
		Fraction& operator=(const Fraction& fraction);

		int A;
		int B;
		int C;

		void redication();//сокрашение дроби

		Fraction& operator+=(const Fraction& drob);
		Fraction& operator-=(const Fraction& drob);
		Fraction& operator*=(const Fraction& drob);
		Fraction& operator/=(const Fraction& drob);

		friend Fraction operator+(const Fraction& A, const Fraction& B);//Сложение
		friend Fraction operator-(const Fraction& A, const Fraction& B);//Вычитане
		friend Fraction operator*(const Fraction& A, const Fraction& B);//Произведение
		friend Fraction operator/(const Fraction& A, const Fraction& B);//Произведение

		void output();
	};
}

