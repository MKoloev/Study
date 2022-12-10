#include "Fraction.h"


namespace xDlars
{
	Fraction::Fraction(int a, int b, int c)
	{
		if (b == 0)
			throw"error";

		A = a; B = b; C = c;
		
		if (B < 0)
		{
			A *= -1;
			B *= -1;
		}
		redication();
	
	}


	//copy
	Fraction::Fraction(const Fraction& fraction):Fraction(fraction.A, fraction.B, fraction.C){}

	Fraction& Fraction::operator=(const Fraction& fraction)
	{
		if (this == &fraction)
			return *this;

		A = fraction.A;
		B = fraction.B;
		C = fraction.C;

		return *this;
	}

	void Fraction::redication()
	{
		if (B == 0)
			throw "error";

		if (A != 0 && B != 0)
		{
			int c = NOD();
			A /= c;
			B /= c;
		}
		
	}


	int Fraction::NOD()//наибольший обший множитель
	{
		int a = abs(A); int b = abs(B);
		while (a != 0 && b != 0)
		{
			if (a < b)
				b -= a;
			if (a > b)
				a -= b;
			if (a == b)
				return a;
		}
		if (a == 0)
			return b;
		else
			return a;
	}


	void Fraction::decomposition()//приведение в правильную дробь
	{
		if (abs(A) > abs(B))
		{
			C = abs(A / B);
			A = A % B;
		}
	}

	void Fraction::reDecompositon()//приведение обратнов в неправильную дробь
	{
		if (C == 0) return;

		if (A < 0)
			A = (C * B - A) * (-1);
		else
			A = C * B + A;
		C = 0;
	}


	//-------------------------------------------------------
	Fraction& Fraction::operator+=(const Fraction& drob)
	{
		Fraction d(drob);
		int c;

		if (B != d.B)
		{
			c = d.B;
			d.B = B * d.B;
			d.A = B * d.A;
			A = c * A;
			B = c * B;
		}

		C += d.C;
		A += d.A;
		redication();
		return *this;
	}

	Fraction& Fraction::operator-=(const Fraction& drob)
	{
		Fraction d(drob);
		int c;

		if (B != d.B)
		{
			c = d.B;
			d.B = B * d.B;
			d.A = B * d.A;
			A = c * A;
			B = c * B;
		}

		C -= d.C;
		A -= d.A;
		redication();
		return *this;
	}

	Fraction& Fraction::operator*=(const Fraction& drob)
	{
		Fraction d(drob);

		d.reDecompositon();
		reDecompositon();

		A *= d.A;
		B *= d.B;
		redication();
		return *this;
	}

	Fraction& Fraction::operator/=(const Fraction& drob)
	{
		Fraction d(drob);

		d.reDecompositon();
		reDecompositon();

		A *= d.B;
		B *= d.A;
		if (B == 0)
			throw"error";
		if (B < 0)
		{
			A *= -1;
			B *= -1;
		}
		redication();
		return *this;
	}


	//-----------------------------------
	Fraction operator+(const Fraction& A, const Fraction& B)//Сложение
	{
		return (Fraction(A) += B);
	}

	Fraction operator-(const Fraction& A, const Fraction& B)//Вычитане
	{
		return (Fraction(A) -= B);
	}

	Fraction operator*(const Fraction& A, const Fraction& B)//Произведение
	{
		return (Fraction(A) *= B);
	}

	Fraction operator/(const Fraction& A, const Fraction& B)//Произведение
	{
		return (Fraction(A) /= B);
	}


	void Fraction::output()
	{
		cout << "----------------------" << endl;
		if (C > 0)
			cout << C;
		cout << "( " << A << "/" << B << " )"<<" = " << A/B;


	}
}

