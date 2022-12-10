using System;
using System.Collections.Generic;
using System.Text;

namespace Колоев_439_5_B_LB8
{
    struct Fraction
    {
        private int A;
        private int B;

        public Fraction(int a = 0, int b = 1)
        {
            this.A = a;
            this.B = b;
        }

        //copy
        public Fraction(Fraction fraction) : this(fraction.A, fraction.B) { }



        //сокрашение дроби

        private int NOD()//наибольший обший множитель
        {
            int a = Math.Abs(this.A); int b = Math.Abs(this.B);
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

        public void redication()//сокрашение дроби
        {
            if (this.B == 0)
                throw new ArgumentException(" Fraction : error");

            if (this.A != 0 && this.B != 0)
            {
                int c = NOD();
                this.A /= c;
                this.B /= c;
            }
        }

        //правильная дробь
        public int decomposition()//приведение в правильную дробь
        {
            int C = 0;
            if (Math.Abs(this.A) > Math.Abs(this.B))
            {
                C = Math.Abs(this.A / this.B);
                this.A = this.A % this.B;
            }
            return C;
        }


        //перегрузка операторов

        public static Fraction operator +(Fraction A, Fraction B)//Сложение
        {
            Fraction d = new Fraction();

            if (A.B != B.B)
            {
                d.B = A.B * B.B;
                d.A = A.A * B.B + B.A * A.B;
            }
            else
            {
                d.A = A.A + B.A;
                d.B = A.B;
            }

            d.redication();
            return d;
        }
		public static Fraction operator -(Fraction A, Fraction B)//Вычитане
        {
            Fraction d = new Fraction();

            if (A.B != B.B)
            {
                d.B = A.B * B.B;
                d.A = A.A * B.B - B.A * A.B;
            }
            else
            {
                d.A = A.A - B.A;
                d.B = A.B;
            }

            d.redication();
            return d;
        }
        public static Fraction operator *(Fraction A, Fraction B)//Произведение
        {
            Fraction d = new Fraction();

            if(A.A == 0 || B.A == 0)
            {
                d.A = 0; d.B = 0;
                return d;
            }

            d.A = A.A * B.A;
            d.B = A.B * B.B;

            d.redication();
            return d;
        }
        public static Fraction operator /(Fraction A, Fraction B)//Произведение
        {
            Fraction d = new Fraction();

            if (A.A == 0 || B.A == 0)
            {
                d.A = 0; d.B = 0;
                return d;
            }

            d.A = A.A * B.B;
            d.B = A.B * B.A;

            d.redication();
            return d;
        }


        public static implicit operator Fraction(int x)
        {
            return new Fraction(x);
        }
        public static implicit operator int(Fraction counter)
        {
            if (counter.A == 0 || counter.B == 0)
                return 0;
            return counter.A/counter.B;
        }
        public static implicit operator double(Fraction counter)
        {
            if (counter.A == 0 || counter.B == 0)
                return 0;
            return (double)counter.A / (double)counter.B;
        }


        public override string ToString()
        {
            StringBuilder matrixString = new StringBuilder();
            matrixString.Append(" " + A + "/" + B + " ");
            return matrixString.ToString();
        }
    }
}
