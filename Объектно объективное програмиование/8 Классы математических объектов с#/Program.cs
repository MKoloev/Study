using System;

namespace Колоев_439_5_B_LB8
{
    class Program
    {
        static void Main(string[] args)
        {
            /* Fraction X = new Fraction(3, 2);
             Fraction Y = new Fraction(7, 3);
             Console.WriteLine(X.ToString());
             Console.WriteLine(Y.ToString());
             double Z = 50;
             Z = Y;
             Console.WriteLine(Y.ToString());
             Console.WriteLine(Z);*/

            double[] m1 = { 34, 6.4, 3, -5.7, 1 };
            int x1 = 4;
            Polinom A = new Polinom(x1, m1);
            Console.WriteLine(A.ToString());

            double[] m2 = { 1, 1, 4.5, -7, 5 };
            int x2 = 1;
            Polinom B = new Polinom(x2, m2);
            Console.WriteLine(B.ToString());

            Polinom C = A / B;
            Console.WriteLine(C.ToString());

        }
    }
}
