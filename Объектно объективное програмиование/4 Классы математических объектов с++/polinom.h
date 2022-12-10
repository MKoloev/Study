#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace xDlars
{
	class polinom
	{
	private:
		double *polin;
		int X = 0;

		void multiplu(double* pol, int x1);
		void socr();
	public:
		polinom(int x = 0, double* pol = nullptr);

		polinom(const polinom& pol);
		polinom& operator=(const polinom& pol);

		polinom(polinom&& pol);
		polinom& operator=(polinom&& pol);

		polinom& operator+=(const polinom& pol);
		polinom& operator-=(const polinom& pol);
		polinom& operator*=(const polinom& pol);
		polinom& operator*=(double p);
		polinom& operator/=(const polinom& pol);

		friend polinom operator*(const polinom& pol, double p);
		friend polinom operator*(const polinom& pol, const polinom& pol1);
		void outPut();
	};
}
