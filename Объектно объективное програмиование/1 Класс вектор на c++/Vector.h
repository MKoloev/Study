#pragma once
#include <iostream>
#include <cstdio>
using namespace std;

namespace xDlars
{
	class Vector
	{

	private:
		int id;
		double x;
		double y;
		double z;
		static int counter;

	public:

		Vector();//инициализирует нулями
		Vector(double a, double b, double c);//инициализирует заданным набором компонентов.
		Vector(const Vector& A);//Конструктор копирования
		Vector& operator= (const Vector& A);//переопределения оператора присваивания
		~Vector();

		/// <summary>
		/// выводит координаты вектора
		/// </summary>
		void output() const;

		/// <summary>
		/// Чтобы ввести координаты вектора
		/// </summary>
		void enter(double x1, double y1, double z1);

		/// <summary>
		/// Вычисляет и выводит модуль вектора
		/// </summary>
		/// <returns></returns>
		double calculatingVectorModule() const;

		/// <summary>
		/// Умножение вектора на скаляр
		/// </summary>
		void vectorMultiplicationScalar(double scalar);

		/// <summary>
		/// Нормировку вектора (получение вектора единичной длины)
		/// </summary>
		void vectorNormalization();


		/// <summary>
		/// Выводит (X)
		/// </summary>
		/// <returns></returns>
		double outputX() const;

		/// <summary>
		/// Выводит (Y)
		/// </summary>
		/// <returns></returns>
		double outputY() const;

		/// <summary>
		/// Выводит (Z)
		/// </summary>
		/// <returns></returns>
		double outputZ() const;


		/// <summary>
		/// Вводит (X)
		/// </summary>
		/// <returns></returns>
		void enterX(double);

		/// <summary>
		/// Вводит (Y)
		/// </summary>
		/// <returns></returns>
		void enterY(double);

		/// <summary>
		/// Вводит (Z)
		/// </summary>
		/// <returns></returns>
		void enterZ(double);


	};


	Vector additionVectars(const Vector& A, const Vector& B);//Сложение вектаров
	Vector subtractionVectars(const Vector& A, const Vector& B);//Вычитане вектаров
	Vector vectorMultiplication(const Vector& A, const Vector& B);//Произведение  вектаров


	double dotProductTwoVectors(const Vector& A, const Vector& B);//скалярное произведение двух векторов
	double cosineAngle(const Vector& A, const Vector& B);//косинуса угла между двумя векторами
	double sineAngle(const Vector& A, const Vector& B);//синус угла между двумя векторами
	double angleValuesDegrees(const Vector& A, const Vector& B);//величины угла в градусах между векторами в пределах [–180?, 180?].


}



