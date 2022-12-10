using System;
using System.Collections.Generic;
using System.Text;

namespace Колоев_439_5_B_LB6
{
    class MATRIX
    {
        static int counter = 0;

		int id;

		public int Lines { get; private set; }
		public int Columns { get; private set; }

		double[] array;

        //Конструкторы

        public MATRIX(int nL = 0, int nC = 0, double[] array = null)//главный конструктор
        {
			if (nC > 0 && nL > 0 && array != null)
			{
				this.array = new double[nC * nL];
				this.Lines = nL;
				this.Columns = nC;
				for (int i = 0; i < nL *nC; i++)
					this.array[i] = array[i];

			}
			else if (nC > 0 && nL > 0 && array == null)
			{
				this.array = new double[nC * nL];
				this.Lines = nL;
				this.Columns = nC;
			}
			else
			{
				this.Lines = 0;
				this.Columns = 0;
				this.array = null;
			}
			counter++;
			this.id = counter;
			Console.WriteLine("Constructor " + this.id);
		}

		public MATRIX(int nL, int nC, double[,] array)
        {
			if(array != null)
            {
				this.array = new double[nC * nL];
				this.Lines = nL;
				this.Columns = nC;
				nL = array.GetLength(0);
				nC = array.GetLength(1);
				for (int i = 0; i < nL; i++)
				{
					for (int j = 0; j < nC; j++)
					{
						this.array[i * nC + j] = array[i, j];
					}
				}
			}
			else if (nC > 0 && nL > 0 && array == null)
			{
				this.array = new double[nC * nL];
				this.Lines = nL;
				this.Columns = nC;
				for (int i = 0; i < nC * nL; i++)
					this.array[i] = 0;
			}
			else
			{
				this.Lines = 0;
				this.Columns = 0;
				this.array = null;
			}
			counter++;
			this.id = counter;
			Console.WriteLine("Constructor " + this.id);
		}

		public MATRIX(int number, double[] arra) : this(number, number, arra) { }
		public MATRIX(int number, double[,] arra): this(number, number, arra) { }
		

		// copy
		public MATRIX(MATRIX matrix) : this(matrix.Lines, matrix.Columns, matrix.array) { }

		~MATRIX()
		{
			Console.WriteLine("Deleted Matrix " + this.id.ToString());
		}


		//проверки

		public bool isNull() //проверяет пустая ли матрица
		{
			return this.array == null;
		}

		private void exceptionH(string name) //обрабтывает исключения пыстой матрицы
		{
			if (isNull())
				throw new ArgumentException(" : Matrix(" + this.id + ") : method(" + name + ") : Matrix is NULL");
		}

		private void exception(string name) //обрабтывает исключения пыстой матрицы
		{
			throw new ArgumentException(" : Matrix(" + this.id + ") : method("+ name +")");
		}


		//возможность умножения и сложения
		public bool possibilityPlus(MATRIX matrix)
		{
			if ((this.Columns == matrix.Columns) && (this.Lines == matrix.Lines))
				return true;
			else
				return false;
		}

		public bool possibilityMultiplu(MATRIX matrix) //проверяет на возможность умножение матрицы на эту
		{
			if (this.Columns == matrix.Lines)
				return true;
			else
				return false;
		}


		//min max

		public double outputMin()//выводит минимальный элимент матрицы
		{
			exceptionH("outputMin");//провепка на исключение

			double minElem = array[0];
			for (int i = 1; i < this.Lines * this.Columns; i++)
			{

				if (minElem > array[i])
					minElem = array[i];

			}
			return minElem;
		}
		public double outputMax()//выводит максимальный элимент матрицы
		{
			exceptionH("outputMax");//провепка на исключение

			double maxElem = array[0];
			for (int i = 1; i < this.Lines * this.Columns; i++)
			{

				if (maxElem < array[i])
					maxElem = array[i];

			}
			return maxElem;
		}




		public static MATRIX operator +(MATRIX matrix, MATRIX matrix1)
		{
			matrix.exceptionH("operator+");
			matrix1.exceptionH("operator+");

			if (matrix.possibilityPlus(matrix1))
			{
				double[] matrix2 = new double[matrix.Columns * matrix.Lines];
				for (int i = 0; i < matrix.Columns * matrix.Lines; i++)
				{
					matrix2[i] = matrix.array[i] + matrix1.array[i];
				}
				return new MATRIX(matrix.Lines, matrix.Columns, matrix2);
			}
			else
			{
				throw new ArgumentException("Matrix(" + matrix.id.ToString() + ") and Matrix(" + matrix1.id.ToString() + "):uncorrect matrix size");
			}
		}

		public static MATRIX operator -(MATRIX matrix, MATRIX matrix1)
		{
			matrix.exceptionH("operator-");
			matrix1.exceptionH("operator-");

			if (matrix.possibilityPlus(matrix1))
			{
				double[] matrix2 = new double[matrix.Columns * matrix.Lines];
				for (int i = 0; i < matrix.Columns * matrix.Lines; i++)
				{
					matrix2[i] = matrix.array[i] - matrix1.array[i];
				}
				return new MATRIX(matrix.Lines, matrix.Columns, matrix2);
			}
			else
			{
				throw new ArgumentException("Matrix(" + matrix.id.ToString() + ") and Matrix(" + matrix1.id.ToString() + "):uncorrect matrix size");
			}
		}

		public static MATRIX operator *(MATRIX matrix, MATRIX matrix1)
		{
			matrix.exceptionH("operator*");
			matrix1.exceptionH("operator*");

			if (!matrix.possibilityMultiplu(matrix1))
            { 
				throw new ArgumentException("Matrix(" + matrix.id.ToString() + ") and Matrix(" + matrix1.id.ToString() + "):uncorrect matrix size");
			}
			
			double element = 0.0;
			double[] matrix2 = new double[matrix1.Columns * matrix.Lines];

			for (int i = 0; i < matrix.Lines; i++)
			{
				for (int j = 0; j < matrix1.Columns; j++)
				{
					element = 0.0;
					for (int k = 0; k < matrix1.Lines; k++)
					{
						element += matrix.array[i * matrix.Columns + k] * matrix1.array[k * matrix1.Columns + j];
					}
					matrix2[i * matrix1.Columns + j] = element;
				}
			}

			return new MATRIX(matrix.Lines, matrix1.Columns, matrix2);
		}


		public static MATRIX operator *(MATRIX matrix, double scal)
		{
			matrix.exceptionH("operator*");
			double[] matrix2 = new double[matrix.Columns * matrix.Lines];
			for (int i = 0; i < matrix.Columns * matrix.Lines; i++)
			{
				matrix2[i] = matrix.array[i] * scal;
			}
			return new MATRIX(matrix.Lines, matrix.Columns, matrix2);

		}

		public static MATRIX operator *(double scal, MATRIX matrix)
		{
			return (matrix * scal);
		}

		public double this[int i, int j]
		{
			get { return this.array[i * Columns + j]; }
			set { this.array[i * Columns + j] = value; }
		}

		//представления матрицы в построчной форме в виде строки
		public override string ToString()
		{
			StringBuilder matrixString = new StringBuilder();

			for (int i = 0; i < this.Lines; i++)
			{
				for (int j = 0; j < this.Columns; j++)
				{
					matrixString.Append($"{this.array[i * this.Columns + j],20} ");
				}
				matrixString.Append("\n");
			}
			return matrixString.ToString();
		}

	}
}
