#include "Vector.h"
#include <iostream>
#include <cstdio>
using namespace std;


namespace xDlars
{
	int Vector::counter = 0;

	Vector::Vector(double a, double b, double c) : x(a), y(b), z(c)
	{
		counter++;
		id = counter;
		cout << "Constructor " << id << endl;
		cout << endl;
	}

	Vector::Vector() : Vector(0.0, 0.0, 0.0) {}

	Vector::Vector(const Vector& A) : Vector(A.x, A.y, A.z) {}//Конструктор копирования

	Vector& Vector::operator= (const Vector& A)//переопределения оператора присваивания
	{
		if (this == &A)
			return *this;
		x = A.x; y = A.y; z = A.z;
		return *this;//возвращаем ссылку на текущий объект
	}

	Vector::~Vector()
	{
		cout << "Destructor " << id << endl;
	}

	void Vector::output() const/// выводит координаты вектора
	{
		cout << "x: " << x << endl;
		cout << "y: " << y << endl;
		cout << "z: " << z << endl;
		cout << endl;
	}

	void Vector::enter(double x1, double y1, double z1)/// Чтобы ввести координаты вектора 
	{
		x = x1;
		y = y1;
		z = z1;
	}

	double Vector::calculatingVectorModule() const/// Вычисляет и выводит модуль вектора
	{
		double vectorModule = (x * x) + (y * y) + (z * z);
		if (vectorModule == 0)
			return 0;
		vectorModule = sqrt(vectorModule);
		return vectorModule;
	}

	void Vector::vectorMultiplicationScalar(double scalar)/// Умножение вектора на скаляр
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
	}

	void Vector::vectorNormalization()/// Нормировку вектора (получение вектора единичной длины)
	{
		double vectorModule = calculatingVectorModule();/// Вычисляет модуль вектора

		x /= vectorModule;
		y /= vectorModule;
		z /= vectorModule;
	}


	double Vector::outputX() const//Выводит (X)
	{
		return x;
	}

	double Vector::outputY() const//Выводит (Y)
	{
		return y;
	}

	double Vector::outputZ() const//Выводит (Z)
	{
		return z;
	}

	void Vector::enterX(double x1)//Вводит (X)
	{
		x = x1;
	}

	void Vector::enterY(double y1)//Вводит (Y)
	{
		y = y1;
	}

	void Vector::enterZ(double z1)//Вводит (Z)
	{
		z = z1;
	}


	/// <summary>
	/// Сложение вектаров, складывает первых два вектора и записывает, это в третий
	/// </summary>
	/// <param name="A"></param>
	/// <param name="B"></param>
	/// <returns></returns>
	Vector additionVectars(const Vector& A, const Vector& B)
	{
		return Vector(
			A.outputX() + B.outputX(),
			A.outputY() + B.outputY(),
			A.outputZ() + B.outputZ());
	}

	/// <summary>
	/// Вычитане вектаров, вычитает 2 вектор из первого и записывает в третий
	/// </summary>
	/// <param name="A"></param>
	/// <param name="B"></param>
	/// <returns></returns>
	Vector subtractionVectars(const Vector& A, const Vector& B)
	{
		return Vector(
			A.outputX() - B.outputX(),
			A.outputY() - B.outputY(),
			A.outputZ() - B.outputZ());
	}


	/// <summary>
	/// Произведение вектаров, произведение первых два вектора и записывает, это в третий
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	Vector vectorMultiplication(const Vector& A, const Vector& B)
	{
		return Vector(
			(A.outputY() * B.outputZ()) - (A.outputZ() * B.outputY()),
			(A.outputZ() * B.outputX()) - (A.outputX() * B.outputZ()),
			(A.outputX() * B.outputY()) - (A.outputY() * B.outputX()));
	}

	/// <summary>
	/// скалярное произведение двух векторов
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	double dotProductTwoVectors(const Vector& A, const Vector& B)
	{
		return (A.outputX() * B.outputX()) + (A.outputY() * B.outputY()) + (A.outputZ() * B.outputZ());
	}

	/// <summary>
	/// косинуса угла между двумя векторами
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	double cosineAngle(const Vector& A, const Vector& B)
	{
		return dotProductTwoVectors(A, B) / (A.calculatingVectorModule() * B.calculatingVectorModule());
	}


	/// <summary>
	/// синус угла между двумя векторами
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	double sineAngle(const Vector& A, const Vector& B)
	{
		Vector C = vectorMultiplication(A, B);
		return C.calculatingVectorModule() / (A.calculatingVectorModule() * B.calculatingVectorModule());
	}


	/// <summary>
	/// величины угла в градусах между векторами в пределах [–180?, 180?].
	/// </summary>
	/// <param name="A"></param>
	/// <param name="B"></param>
	/// <returns></returns>
	double angleValuesDegrees(const Vector& A, const Vector& B)
	{
		return atan2(cosineAngle(A, B), sineAngle(A, B));
	}
}