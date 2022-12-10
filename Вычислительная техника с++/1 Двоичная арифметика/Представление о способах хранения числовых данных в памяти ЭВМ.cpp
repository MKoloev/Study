// ВТлаб1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

void binaryTranslation(unsigned int value, int size);//Программу по выводу битовых данных (битов), Беззнаковое целое 1,2,4 байт
void binaryTranslation1(int value, int size); //Программу по выводу битовых данных(битов), Знаковое целое 1, 2, 4 байт
void binaryTranslation2(float value, int size);//Программу по выводу битовых данных (битов), float 
void binaryTranslation3(double value, int size);//Программу по выводу битовых данных (битов), double
void output1(char* Array, int size1, int size2);//выводит массив

int main()
{
    int value;
    unsigned __int8 value1;
    cout << "Unsigned integer 1 byte" << endl;
    cin >> value;
    value1 = value;
    binaryTranslation(value1, 8);
   
    unsigned short int value2;
    cout << "Unsigned integer 2 byte" << endl;
    cin >> value2;
    binaryTranslation(value2, 16);
    
    unsigned int value3;
    cout << "Unsigned integer 4 byte" << endl;
    cin >> value3;
    binaryTranslation(value3, 32);
   

    cout << "---------------------------------" << endl;
    signed __int8 value4;
    cout << "Signed integer 1 byte" << endl;
    cin >> value;
    value4 = value;
    binaryTranslation1(value4, 8);

    short int value5;
    cout << "Signed integer 2 byte" << endl;
    cin >> value5;
    binaryTranslation1(value5, 16);

    int value6;
    cout << "Signed integer 4 byte" << endl;
    cin >> value6;
    binaryTranslation1(value6, 32);



    float value7;
    cout << "Real 4 bytes" << endl;
    cin >> value7;
    binaryTranslation2(value7, 32);

    double value8;
    cout << "Real 8 bytes" << endl;
    cin >> value8;
    binaryTranslation3(value8, 64);
    
}

///===================================================================================
///===================================================================================
/// <summary>
/// Программу по выводу битовых данных (битов)
/// Беззнаковое целое 1,2,4 байт
/// </summary>
/// <param name="value"></param>
void binaryTranslation(unsigned int value, int size)
{
    unsigned char* array = (unsigned char*)&value;// указателю array присвоили адрес переменой value,
    char bit[32];
    for (int i = 0; i < size; i++)//заполняет массивиз нулями в зависимости сколько байтов в переменной 
        bit[i] = '0';

    for (int i = 0; i < (size / 8); i++)
        for (int j = size - i*8 - 1, t = 0; t < 8; j--, t++)
            bit[j] = (char)((array[i] >> t) % 2 + 48);

    output1(bit, 0, size);
}

///===================================================================================
///===================================================================================
/// <summary>
/// Программу по выводу битовых данных (битов)
/// Знаковое целое 1,2,4 байт
/// </summary>
/// <param name="value"></param>
/// <param name="size"></param>
void binaryTranslation1(int value, int size)
{
    unsigned char* array = (unsigned char*)&value;// указателю array присвоили адрес переменой value,
    char bit[32];
    for (int i = 0; i < size; i++)//заполняет массивиз нулями в зависимости сколько байтов в переменной 
        bit[i] = '0';

    for (int i = 0; i < (size / 8); i++)
        for (int j = size - i * 8 - 1, t = 0; t < 8; j--, t++)
            bit[j] = (char)((array[i] >> t) % 2 + 48);

    output1(bit, 0, size);
}

///===================================================================================
///===================================================================================
/// <summary>
/// Программу по выводу битовых данных (битов)
/// С запятой 4 байта
/// </summary>
/// <param name="value"></param>
/// <param name="size"></param>
void binaryTranslation2(float value, int size)//Программу по выводу битовых данных (битов), Беззнаковое целое 1,2,4 байт
{
    unsigned char* array = (unsigned char*)&value;// указателю array присвоили адрес переменой value,
    char bit[32];
    for (int i = 0; i < size; i++)//заполняет массивиз нулями в зависимости сколько байтов в переменной 
        bit[i] = '0';

    for (int i = 0; i < (size / 8); i++)
        for (int j = size - i * 8 - 1, t = 0; t < 8; j--, t++)
            bit[j] = (char)((array[i] >> t) % 2 + 48);

    output1(bit, 0, size);
}

///===================================================================================
///===================================================================================
void binaryTranslation3(double value, int size)//Программу по выводу битовых данных (битов), Беззнаковое целое 1,2,4 байт
{
    unsigned char* array = (unsigned char*)&value;// указателю array присвоили адрес переменой value,
    char bit[64];
    for (int i = 0; i < size; i++)//заполняет массивиз нулями в зависимости сколько байтов в переменной 
        bit[i] = '0';

    for (int i = 0; i < (size / 8); i++)
        for (int j = size - i * 8 - 1, t = 0; t < 8; j--, t++)
            bit[j] = (char)((array[i] >> t) % 2 + 48);

    output1(bit, 0, size);
}

/// <summary>
/// Выводит результат
/// </summary>
/// <param name="Array"></param>
/// <param name="size1"></param>
/// <param name="size2"></param>
void output1(char* Array, int size1, int size2)
{
    cout << endl;
    for (int i = size1; i < size2; i++) {
        cout << Array[i];
        if (((i + 1) % 4) == 0)//после вывода 4 бит делает отступ
            cout << " ";
    }
    cout << endl << endl;
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
