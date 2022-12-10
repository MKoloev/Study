// v3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <utility>
#include <fstream>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include "ShamirHeader.h"

using namespace std;

const int SIZEARRAY = 1000;
const int P = 97429;

/* Возведение в степень по модулю
* Алгоритм позволяет выполнить следующую задачу:
* Необходимо вычислить  a^x mod p, причем a, x, p могут быть большимм
* mod p - остаток от деления на число p.
*/
long long Modular_Exonentiation(long long a, int b, int n);

void OutputInt(int* ar, int size);
void OutputChar(char* ar, int size);
int outputFromFile(char* outputFile, char* sourceText);

 class SKey
 {
 public:
     const int P = 97429;
	 int Ca, Da;
	 int Cb, Db;

     SKey()
     {
         Ca = 500;
         Generate_key(Ca, Da);
         Cb = Ca + 1;
         Generate_key(Cb, Db);
     }

 private:
     //Нахождение НОД
     int GCD(int firstNumber, int secondNumber);

     //Генерация ключей
     void Generate_key(int& C, int& D);

     //Расширенный(Обобщенный) алгоритм Евклида
    // void extended_euclid(unsigned long a, unsigned long b, long* x, long* y, long* d);
     long extended_euclid(unsigned long a, unsigned long b, long& x, long& y);
     //Поиск обратного элемента по модулю
     long inverse(unsigned long a, unsigned long n);
 };
 
 class ShamirEncryption
 {
 public:
     int* aray;

     ShamirEncryption(int* ary, int size)
     {
         initialArraySize = size;
         arrayDivision(ary, size);
     }

     void encryption(int key);
     void terminalOutput();
     int* outPut();

 private:
     int initialArraySize;
     int sizeArray;

     void arrayDivision(int* ary, int size);
     int shift(int sh);
 };



int main()
{
    setlocale(LC_ALL, "Russian");

    char encryptFile[]{ "D:\\учеба\\Информационная безопасность\\Лаб3\\Text.txt" };
    char sourceText[SIZEARRAY];
    int sizeText = outputFromFile(encryptFile, sourceText);
    OutputChar(sourceText, sizeText);

    int* textInNumbers = replace_char(sourceText, sizeText);
    OutputInt(textInNumbers, sizeText);

    ShamirEncryption A(textInNumbers, sizeText);

    SKey key;
    cout << "\n-----------Shamir-----------\n";
    cout << "Start message: " << endl;
    A.terminalOutput();
    A.encryption(key.Ca);
    cout << endl << endl << "Encripting by A: " << endl;
    A.terminalOutput();
    A.encryption(key.Cb);
    cout << endl << endl << "Encripting by B: " << endl;
    A.terminalOutput();
    A.encryption(key.Da);
    cout << endl << endl << "Decripting by A: " << endl;
    A.terminalOutput();
    A.encryption(key.Db);
    cout << endl << endl << "Decripting by B(message from A): " <<  endl;
    A.terminalOutput();
    cout << "\n---------------------------\n\n";

    int* descryptionNumber = A.outPut();
    OutputInt(descryptionNumber, sizeText);

    char* descryptionText = inv_replace_char(descryptionNumber, sizeText);
    OutputChar(descryptionText, sizeText);

    delete[] textInNumbers;
    delete[] descryptionNumber;
    delete[] descryptionText;

}


int outputFromFile(char* outputFile, char* sourceText)
{
    ifstream fail;

    fail.open(outputFile, 'a');
    if (!fail.is_open())
    {
        cout << "No" << endl;
        return NULL;
    }
    else
    {
        char enter;
        int sizeText = 0;
        for (int i = 0; i < SIZEARRAY && !fail.eof(); i++, sizeText++)
        {
            fail >> enter;//выводит число из файла
            sourceText[i] = enter;
        }
        fail.close();
        return sizeText - 1;
    }
}


long long Modular_Exonentiation(long long a, int b, int n)
{
    int res = 1;
    a = a % n;

    while (b > 0)
    {
        // Если не четное
        if (b & 1)
            res = (res * a) % n;

        b = b >> 1; // n = n/2
        a = (a * a) % n;
    }
    return res;
}

void OutputInt(int* ar, int size)
{
    for (int i = 0; i < size; i++)
        cout << ar[i] << "  ";

    cout << endl;
}

void OutputChar(char* ar, int size)
{
    for (int i = 0; i < size; i++)
        cout << ar[i];

    cout << endl;
}

//========================================================
//===========Класс Skey===================================

long SKey::inverse(unsigned long a, unsigned long n)
{
    long d, x, y;
    d = extended_euclid(a, n, x, y);
    if (d != 1) { return 0; }
    else
        return x;
}

long SKey::extended_euclid(unsigned long a, unsigned long b, long& x, long& y)
{
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    long x1, y1;
    long d = extended_euclid(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

void SKey::Generate_key(int& C, int& D)
{
    for (int i; C < 1000; C++)
    {
        if (GCD(C, P - 1) == 1)
        {
            D = inverse(C, P - 1);
            if (D > 0 && (C * D) % (P - 1) == 1 && D < 10000)
                break;
        }
    }
}

int SKey::GCD(int firstNumber, int secondNumber)
{
    return secondNumber != 0 ? GCD(secondNumber, firstNumber % secondNumber) : firstNumber;
}


//========================================================
//===========Класс ShamirEncryption=======================
void ShamirEncryption::arrayDivision(int* ary, int size)
{
    aray = new int[size];
    for (int i = 0; i < size; i++)
        aray[i] = 0;
    int j = 0;
    int shift = 100;
    for (int i = 0; i < size; i++)
    {
        if ((aray[j] * 10 + (ary[i] / 10)) >= P)
            j++;
        aray[j] = aray[j] * 10 + (ary[i] / 10);

        if ((aray[j] * 10 + (ary[i] % 10)) >= P)
            j++;
        aray[j] = aray[j] * 10 + (ary[i] % 10);
    }
    sizeArray = j + 1;
}

void ShamirEncryption::encryption(int key)
{
    for (int i = 0; i < sizeArray; i++)
    {
        aray[i] = Modular_Exonentiation(aray[i], key, P);
    }
}

void ShamirEncryption::terminalOutput()
{
    for (int i = 0; i < sizeArray; i++)
    {
        cout << aray[i] << "  ";
    }
}

int* ShamirEncryption::outPut()
{
    int* ary = new int[initialArraySize];
    for (int i = 0; i < initialArraySize; i++)
        ary[i] = 0;
    int sh = 1;
    int j = 0;
    for (int i = 0; i < sizeArray; i++)
    {
        sh = shift(aray[i]);
        while (aray[i] > 0 && sh > 0)
        {
            if (ary[j] > 9)
                j++;
            ary[j] *= 10;
            ary[j] += aray[i] / sh;
            aray[i] = aray[i] % sh;
            sh /= 10;
        }
    }
    return ary;
}

int ShamirEncryption::shift(int sh)
{
    if (sh <= 0)
        return 0;
    int s = 1;
    while (true)
    {
        if (sh < s)
            return s / 10;
        s *= 10;
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
