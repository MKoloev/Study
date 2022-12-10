#include "polinom.h"

namespace xDlars
{
	polinom::polinom(int x, double* pol)
	{
		if (pol == nullptr || x < 0)
			x = 0;
		if(x>0)
		X = x + 1;
		polin = new double[X]();

		if (X > 0) 
		{
			for (int i = 0; i < X; i++)
			{
				polin[i] = pol[i];
			}
		}
		else
			polin = nullptr;
	}

	polinom::polinom(const polinom& pol) :polinom(pol.X, pol.polin ) {}
	polinom& polinom::operator=(const polinom& pol)
	{
		if (this == &pol)
			return *this;
		if (pol.X > 0)
		{
			polin = new double[pol.X];
			for (int i = 0; i < pol.X; i++)
			{
				polin[i] = pol.polin[i];
			}
			X = pol.X;
		}
		else
			polin = nullptr;
		return *this;
	}




	polinom& polinom::operator=(polinom&& pol)
	{
		// Проверка на самоприсваивание
		if (&pol == this) return *this;

		// Удаляем всё, что к этому моменту может хранить указатель
		if (polin != nullptr)
		{
			delete[] polin;
			polin = nullptr;
			X = 0;
		}

		std::swap(polin, pol.polin);
		std::swap(X, pol.X);

		return *this;
	}


	polinom::polinom(polinom&& pol)
	{
		*this = std::move(pol);
	}

	polinom& polinom::operator+=(const polinom& pol)
	{
		int x = 0;
		x = X >= pol.X ? X : pol.X;
		if (x > 0)
		{
			double* pol2 = new double[x];
			for (int i = 0; i < X; i++)
			{
				pol2[i] = polin[i];
			}

			for (int i = 0; i < pol.X; i++)
			{
				pol2[i] += pol.polin[i];
			}
			polin = pol2;
			X = x;
			socr();
		}
		return *this;
	}



	polinom& polinom::operator-=(const polinom& pol)
	{
		int x = 0;
		x = X >= pol.X ? X : pol.X;
		if (x > 0)
		{
			double* pol2 = new double[x];
			for (int i = 0; i < X; i++)
				pol2[i] = polin[i];

			for (int i = 0; i < pol.X; i++)
				pol2[i] -= pol.polin[i];

			polin = pol2;
			X = x;
			socr();
		}

		return *this;
	}

	polinom& polinom::operator*=(const polinom& pol)
	{
		int x = X + pol.X-1;
		if (x > 0)
		{
			double* pol2 = new double[x];
			for (int i = 0; i < x; i++)
				pol2[i] = 0;

			for (int i = 0; i < pol.X; i++)
			{
				for (int j = 0; j < X; j++)
				{
					pol2[i + j] += pol.polin[i] * polin[j];
				}
			}

			polin = pol2;
			X = x;
			socr();
		}

		return *this;
	}


	polinom& polinom::operator*=(double p)
	{
		for (size_t i = 0; i < X; i++)
		{
			polin[i] *= p;
		}
		return *this;
	}


	polinom operator*(const polinom& pol, double p)
	{
		return polinom(pol) *= p;
	}

	void polinom::multiplu(double* pol, int x1)
	{
		int x = X + x1 - 1;
		if (x > 0)
		{
			double* pol2 = new double[x];
			for (int i = 0; i < x; i++)
				pol2[i] = 0;

			for (int i = 0; i < x1; i++)
			{
				for (int j = 0; j < X; j++)
				{
					pol2[i + j] += pol[i] * polin[j];
				}
			}

			polin = pol2;
			X = x;
		}

	}


	polinom& polinom::operator/=(const polinom& pol)
	{
		if (X < pol.X)
			return *this;
		int x = X - (pol.X - 1) ;
		int j = 1;
		double k = 0;
		double* pol2 = new double[x];
		double* pol3;
		polinom C;
		while ((X - j) >= pol.X -1 )
		{
			if (polin[X - j] != 0)
				k = polin[X - j] / pol.polin[pol.X - 1];
			else
			{
				j++;
				continue;
			}



			pol3 = new double[X - j - (pol.X -2)];
			pol3[X - j - (pol.X - 2)-1] = k;
			for (size_t i = 0; i < X - j - (pol.X - 2)-1; i++)
				pol3[i] = 0;
			cout << endl << "---------------------------" << endl;
			for (size_t i = 0; i < X - j - (pol.X - 2); i++)
				cout << pol3[i] << "   ";
			cout << endl;
			C = pol;
			C.multiplu(pol3, X - j - (pol.X -2));
			*this -= C;




			cout << endl << "---------------------------" << endl;
			for (size_t i = 0; i < X; i++)
				cout << polin[i] << "   ";
			cout << endl;
			for (size_t i = 0; i < C.X ; i++)
				cout << C.polin[i] << "   ";
			cout << endl;
			cout <<k<< endl;
			pol2[x - j++] = k;
			for (size_t i = 0; i < x; i++)
				cout << pol2[i] << "   ";
		}
		polinom m(x - 1, pol2);
		cout << endl << "---------------------------" << endl;
		m.outPut();
		socr();
		return m;
	}

	void polinom::socr()
	{
		while (polin[X - 1] == 0)
			X--;
		double* pol2 = new double[X];
		for (size_t i = 0; i < X; i++)
		{
			pol2[i] = polin[i];
		}
		polin = pol2;
	}
	void polinom::outPut()
	{
		cout << endl;
		cout << "("<< polin[0] <<") ";
		for (int i = 1; i < X; i++)
		{
			cout << "+ (" << polin[i] << ")"<< "(x^" << i << ") ";
		}
	}
}