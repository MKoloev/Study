// Lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.


//8. Написать программу, которая реализует метод открытого хеширования с хеш - функцией, 
//основанной на методе умножения.Данные, хранящиеся в файле занести в хеш - таблицу.Файл 
//должен содержать не менее 15 целых чисел.Вывести построенную хеш - таблицу на 
//экран(вместе с количеством выполненных проб).Организовать поиск данных в хеш - таблице.
//Результаты поиска данных вывести на экран.Также вывести количество проб, которые были затрачены при поиске.


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


struct node
{
    //int prob;
    int key;
    node *next;
};


class HechTab
{
private:
    const int m = 10;
    node* array[10];

    int hk(int k);//функция умножения
    void outputFromFile();
    void fillin();

public:
    HechTab();
    ~HechTab();

    void getKey(int k);
    void output(int k);
    void Delete(int k);
    void outputConsole();

};



int main()
{
    HechTab A;

    A.outputConsole();
    A.output(96);
    A.output(100);
    A.Delete(62);
    A.outputConsole();

    return 0;
}



HechTab::HechTab()
{
    fillin();
    for (int i = 0; i < m; i++)
    {
        array[i] = new node;
      //  array[i]->prob = 0;
        array[i]->key = NULL;
        array[i]->next = NULL;
    }
    outputFromFile();
}


HechTab::~HechTab()
{
    if(array != NULL)
        delete[] *array;
}




void HechTab::getKey(int k)
{
    int j = hk(k);
    if (array[j]->key == NULL)
    {
        array[j]->key = k;
      //  array[j]->prob = 1;
        array[j]->next = NULL;
        return;
    }

    node *newNext = new node;
    node *next = array[j];
    newNext->key = k;
    newNext->next = NULL;
    
    while (next->next != NULL && next->key != k)
    {   
        next = next->next;
    }
    if (next->key == k)
        return;
   // newNext->prob = next->prob + 1;
    next->next = newNext;

}


void HechTab::fillin()
{
    ofstream fail1;
    fail1.open("fail.txt");//открывает или создает файл

    if (!fail1.is_open())// проверка открылся он или нет
    {
        cout << "не открылся" << endl;
    }
    else
    {
        int enter = 0;
        for (size_t i = 0; i < 15; i++) {
            enter = 0 + rand() % 99;// случайные числа
            fail1 << enter << " ";
        }
    }
    fail1.close();
}


void HechTab::outputFromFile()
{
    ifstream fail1;
    fail1.open("fail.txt");
    if (!fail1.is_open())
    {
        cout << "No" << endl;
        return;
    }
    else
    {
        int num = 0;
        string enter;

        while (!fail1.eof())
        {
            num = 0;
            enter = "";
            fail1 >> enter;//выводит число из файла
            if (enter != "") {
                num = stoi(string(enter));//преврашает его из string в int

                getKey(num);
            }
        }

    }
    fail1.close();
}


void HechTab::output(int k)
{
    int j = hk(k);
    int prob = 1;
    node* next = array[j];
    while (next != NULL)
    {
        if (next->key == k)
        {
            cout << "------------------------------------------------------"<<endl;
            cout << "proba: " << prob << endl << "key: " << next->key << endl << "echeika: " << j << endl;
            cout << "------------------------------------------------------" << endl;
            return;
        }
        prob++;
        next = next->next;
    }
    cout << "------------------------------------------------------" << endl;
    cout << "net takogo" << endl;
    cout << "------------------------------------------------------" << endl;
}


void HechTab::Delete(int k)
{
    int j = hk(k);
    if (array[j]->key == k && array[j] != NULL)
    {
        if (array[j]->next == NULL)
            array[j]->key = NULL;
        else
            array[j] = array[j]->next;
        return;
    }

    
    node* next = array[j];
    node* next1 = array[j];

    while (next != NULL)
    {
        if (next->key == k)
        {
            if (next->next == NULL)
                next1->next = NULL;
            else
                next1->next = next->next;
            return;
        }
        next1 = next;
        next = next->next;
    }
    cout << "net takogo" << endl;
}



void HechTab::outputConsole()
{
    int prob = 1;
    for (int i = 0; i < m; i++)
    {
        prob = 0;
        node* next = array[i];
        cout << "|\t";
        while (next != NULL)
        {
            if (next->key != NULL)
                prob++;
            cout << "["<< prob <<"]:"<< next->key << "\t|\t";
            next = next->next;
        }
        cout << endl;
    }
}

int HechTab::hk(int k)
{
    double i;
    i = (0.618 * k);
    k = i;
    i -= k;
    i *= m;
    k = i;
    return  k ;
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
