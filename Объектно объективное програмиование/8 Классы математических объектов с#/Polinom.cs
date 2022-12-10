using System;
using System.Collections.Generic;
using System.Text;

namespace Колоев_439_5_B_LB8
{
	class Polinom
	{
		double[] polinom = null;
		int X = 0;

		public Polinom(int x = 0, double[] polinom = null)
		{
			if (x < 0)
				x = 0;
			if (x > 0)
				X = x + 1;
			this.polinom = new double[X];

			if (polinom != null)
                for (int i = 0; i < X; i++)
					this.polinom[i] = polinom[i];
			else
				for (int i = 0; i < X; i++)
					this.polinom[i] = 0;
		}

		public Polinom(Polinom polinom) : this(polinom.X, polinom.polinom) { }


		//сокрашение полинома
		public void redication()
        {
			for (int i = X - 1; i > 0; i--)
				if (this.polinom[i] == 0)
					X--;
        }


		public static Polinom operator +(Polinom A, Polinom B)//Сложение
		{
			int c;
			if (A.X > B.X)
				c = A.X - 1;
			else
				c = B.X - 1;
			Polinom C = new Polinom(c);
			for (int i = 0; i < c + 1; i++)
            {
				if (A.X > i)
					C.polinom[i] += A.polinom[i];
				if (B.X > i)
					C.polinom[i] += B.polinom[i];
			}
			C.redication();
			return C;
		}

		public static Polinom operator -(Polinom A, Polinom B)//Сложение
		{
			int c;
			if (A.X > B.X)
				c = A.X - 1;
			else
				c = B.X - 1;
			Polinom C = new Polinom(c);
			for (int i = 0; i < c + 1; i++)
			{
				if (A.X > i)
					C.polinom[i] -= A.polinom[i];
				if (B.X > i)
					C.polinom[i] -= B.polinom[i];
			}
			C.redication();
			return C;
		}


		public static Polinom operator *(Polinom A, Polinom B)//Сложение
		{
			int c = A.X + B.X - 1;
			Polinom C = new Polinom(c);

			for (int i = 0; i < A.X; i++)
			{
				for (int j = 0; j < B.X; j++)
				{
					C.polinom[i + j] += A.polinom[i] * B.polinom[j];
				}
			}
			C.redication();
			return C;
		}

		public static Polinom operator *(Polinom A, double B)//Сложение
		{
			int c = A.X - 1;
			Polinom C = new Polinom(c);

			for (int i = 0; i < A.X; i++)
			{
				C.polinom[i] = A.polinom[i] * B;
			}
			C.redication();
			return C;
		}


		public static Polinom operator /(Polinom A, Polinom B)//Сложение
		{
			if(A.X < B.X)
				throw new ArgumentException(" Fraction : error");
			int c = A.X - B.X;
			Polinom C = new Polinom(c);
			double[] pol = new double[A.X];
			int i = A.X - 1;

			for (int j = 0; j < A.X; j++)
				pol[j] = A.polinom[j];
            for (; i >= B.X - 1 ; i--, c--)
            {
				while (pol[i] == 0)
					i--;
				if (i < B.X - 1)
					break;
				C.polinom[c] = pol[i];
                for (int j = i, k = B.X - 1; k >= 0; j--, k--)
                {
					pol[j] -= B.polinom[k] * C.polinom[c];
				}
			}
			
			C.redication();
			return C;
		}


		public override string ToString()
		{
			StringBuilder matrixString = new StringBuilder();

			matrixString.Append($"({this.polinom[0]}) ");
			for (int i = 1; i < this.X; i++)
				matrixString.Append($"+ ({this.polinom[i]})(N^{i}) ");
			return matrixString.ToString();
		}

	}
}
