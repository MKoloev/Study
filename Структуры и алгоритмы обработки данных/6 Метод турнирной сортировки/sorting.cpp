// Lab6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

//8. Пусть даны три файла вещественных чисел, состоящих из 100, 1000 и 10000 чисел.Выполнить сортировку
//данных с помощью метода турнирной сортировки.Подсчитать количество операций сравнения для каждого из трех файлов.


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;


struct nod
{
    char p = NULL;
    double n = NULL;
};

struct Node
{
    nod glav;
    nod left[3];
    nod right[3];
};

class TurnirSort
{
public:
    int* Mass;
    char* Mas;
    int Size;
    Node tree;

    int schet = 0;

    void outputFromFile(char* mass);//выводит из файла
    void fillin(char* mass);//заполнение файла
    void inFail(char* mass);

    void fillTree(int s);//добавление нового элимента в дерево
    void sort2();//заполняет 2 и 3 яейку
    void sort3();
    bool pust();//проверяеет пустое ли дерево

public:
    TurnirSort(int size = 0, char* mass = nullptr, char* mas = nullptr);
    ~TurnirSort();

    void sort();
    void startSort();//начало сортировки

    void output();

};



int main()
{
    char mass[] { "fail100.txt" }; 
    char mas[]{ "out100.txt" };
    TurnirSort i(100, mass, mas);
    i.sort();
}


TurnirSort::TurnirSort(int size, char* mass, char* mas)
{
    if (size == 0 || mass == nullptr) return;
    Mas = mas;
    Size = size;
    Mass = new int[size];
    fillin(mass);
}

TurnirSort::~TurnirSort()
{
    if (Mass == nullptr) return;
    delete[] Mass;
}


void TurnirSort::output()
{
    cout << endl << "-----------------------" << endl;
    for (size_t i = 0; i < Size; i++)
    {
        cout << Mass[i] << "  ";
    }
}

void TurnirSort::fillin(char* mass)
{
    ofstream fail1;
    fail1.open(mass);//открывает или создает файл

    if (!fail1.is_open())// проверка открылся он или нет
    {
        cout << "не открылся" << endl;
    }
    else
    {
        int enter = 0;
        for (size_t i = 0; i < Size; i++) {
            enter = -1 + rand() % Size * 89;// случайные числа
            fail1 << enter << " ";
            if ((i % 30) == 0 && i>0)
                fail1 << endl;
            Mass[i] = enter;
        }
    }
    fail1.close();
}


void TurnirSort::inFail(char* mass)
{
    ofstream fail1;
    fail1.open(mass);//открывает или создает файл

    if (!fail1.is_open())// проверка открылся он или нет
    {
        cout << "не открылся" << endl;
    }
    else
    {
        for (size_t i = 0; i < Size; i++)
        {
            fail1 << Mass[i] << " ";
            if ((i % 30) == 0 && i > 0)
                fail1 << endl;
        }
    }
    fail1.close();
}


void TurnirSort::outputFromFile(char* mass)
{
    ifstream fail1;

    fail1.open(mass);
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

            }
        }

    }
    fail1.close();
}




void TurnirSort::sort()
{
    if (Mass == nullptr || Size < 4)
    {
        cout << "error";
        return;
    }
    int* winner = new int[Size];
    int* loser = new int[Size];
    int w, l;
    do {
        w = 0; l = 0;

        startSort();
        for (size_t i = 4;( w+l ) < Size;)
        {
            
            if ((tree.left[0].p == NULL || tree.left[1].p == NULL || tree.right[0].p == NULL || tree.right[1].p == NULL) && i < Size)
            {
                fillTree(i);
                i++;
            }
            if ((tree.left[0].p == NULL || tree.left[1].p == NULL || tree.right[0].p == NULL || tree.right[1].p == NULL) && i < Size) continue;

            if (tree.left[2].p == NULL || tree.right[2].p == NULL)
                sort2();

            if ((tree.left[0].p == NULL || tree.left[1].p == NULL || tree.right[0].p == NULL || tree.right[1].p == NULL) && i < Size) continue;

            if (tree.glav.p == NULL)
            {   
                sort3();
                continue;
            }
            if (w == 0)
            {
                winner[w++] = tree.glav.n;
                tree.glav.p = NULL;
                continue;
            }

            if (winner[w - 1] <= tree.glav.n )
            {
                winner[w++] = tree.glav.n;
                tree.glav.p = NULL;
            }
            else
            {
                loser[l++] = tree.glav.n;
                tree.glav.p = NULL;
            }
        }
        int a = 0;
        for (size_t i = 0; i < l; i++ )
            Mass[a++] = loser[i];

        for (size_t i = 0; i < w; i++)
            Mass[a++] = winner[i];

    } while (l != 0);


    cout << endl << "--------------------" << endl;
    cout <<"Number of comparisons: " << schet;
    inFail(Mas);
    delete[] winner;
    delete[] loser;
}


void TurnirSort::startSort()
{

    tree.left[0].n = Mass[0];
    tree.left[1].n = Mass[1];
    tree.right[0].n = Mass[2];
    tree.right[1].n = Mass[3];
    tree.left[0].p = 1;
    tree.left[1].p = 1;
    tree.right[0].p = 1;
    tree.right[1].p = 1;
    Mass[0] = NULL;
    Mass[1] = NULL;
    Mass[2] = NULL;
    Mass[3] = NULL;
}



void TurnirSort::fillTree(int c)
{
    double s = 0;
    schet++;
        if (tree.left[0].p == NULL)
        {
            tree.left[0].n = Mass[c];
            tree.left[0].p = 1;
            if (tree.left[0].n < tree.left[2].n && tree.left[2].p != NULL)
            {
                s = tree.left[2].n;
                tree.left[2].n = tree.left[0].n;
                tree.left[0].n = s;

                if (tree.left[2].n < tree.glav.n && tree.glav.p != NULL)
                {
                    s = tree.left[2].n;
                    tree.left[2].n = tree.glav.n;
                    tree.glav.n = s;
                }
            }
        }
        else if (tree.left[1].p == NULL)
        {
            tree.left[1].n = Mass[c];
            tree.left[1].p = 1;
            if (tree.left[1].n < tree.left[2].n && tree.left[2].p != NULL)
            {
                s = tree.left[2].n;
                tree.left[2].n = tree.left[1].n;
                tree.left[1].n = s;
                if (tree.left[2].n < tree.glav.n && tree.glav.p != NULL)
                {
                    s = tree.left[2].n;
                    tree.left[2].n = tree.glav.n;
                    tree.glav.n = s;
                }
            }
        }
        else if (tree.right[0].p == NULL)
        {
            tree.right[0].n = Mass[c];
            tree.right[0].p = 1;
            if (tree.right[0].n < tree.right[2].n && tree.right[2].p != NULL)
            {
                s = tree.right[2].n;
                tree.right[2].n = tree.right[0].n;
                tree.right[0].n = s;

                if (tree.right[2].n < tree.glav.n && tree.glav.p != NULL)
                {
                    s = tree.right[2].n;
                    tree.right[2].n = tree.glav.n;
                    tree.glav.n = s;
                }
            }
        }
        else if (tree.right[1].p == NULL)
        {
            tree.right[1].n = Mass[c];
            tree.right[1].p = 1;
            if (tree.right[1].n < tree.right[2].n && tree.right[2].p != NULL)
            {
                s = tree.right[2].n;
                tree.right[2].n = tree.right[1].n;
                tree.right[1].n = s;
                if (tree.right[2].n < tree.glav.n && tree.glav.p != NULL)
                {
                    s = tree.right[2].n;
                    tree.right[2].n = tree.glav.n;
                    tree.glav.n = s;
                }
            }
        }
}


void TurnirSort::sort2()
{
    schet++;
    if (tree.left[2].p == NULL && (tree.left[0].p == 1 || tree.left[1].p == 1))
    {

            if (tree.left[0].p == NULL)
            {
                tree.left[2].n = tree.left[1].n;
                tree.left[1].p = NULL;
                tree.left[2].p = 1;
                return;
            }
            if (tree.left[1].p == NULL)
            {
                tree.left[2].n = tree.left[0].n;
                tree.left[0].p = NULL;
                tree.left[2].p = 1;
                return;
            }

            if (tree.left[0].n <= tree.left[1].n)
            {
                tree.left[2].n = tree.left[0].n;
                tree.left[2].p = 1;
                tree.left[0].p = NULL;
            }
            else
            {
                tree.left[2].n = tree.left[1].n;
                tree.left[2].p = 1;
                tree.left[1].p = NULL;
            }

    }
    else if (tree.right[2].p == NULL && (tree.right[0].p == 1 || tree.right[1].p == 1))
    {
        if (tree.right[0].p == NULL && tree.right[1].p == NULL)
            return;
        if (tree.right[0].p == NULL)
        {
            tree.right[2].n = tree.right[1].n;
            tree.right[1].p = NULL;
            tree.right[2].p = 1;
            return;
        }
        if (tree.right[1].p == NULL)
        {
            tree.right[2].n = tree.right[0].n;
            tree.right[0].p = NULL;
            tree.right[2].p = 1;
            return;
        }


        if (tree.right[0].n <= tree.right[1].n)
        {
            tree.right[2].n = tree.right[0].n;
            tree.right[2].p = 1;
            tree.right[0].p = NULL;
        }
        else
        {
            tree.right[2].n = tree.right[1].n;
            tree.right[2].p = 1;
            tree.right[1].p = NULL;
        }
    }
}


void TurnirSort::sort3()
{
    schet++;
    if (tree.glav.p == NULL)
    {
        if (tree.left[2].p == NULL && tree.right[2].p == NULL)
            return;

        if (tree.left[2].p == NULL)
        {
            tree.glav.n = tree.right[2].n;
            tree.glav.p = 1;
            tree.right[2].p = NULL;
            return;
        }
        if (tree.right[2].p == NULL)
        {
            tree.glav.n = tree.left[2].n;
            tree.glav.p = 1;
            tree.left[2].p = NULL;
            return;
        }


        if (tree.left[2].n <= tree.right[2].n)
        {
            tree.glav.n = tree.left[2].n;
            tree.glav.p = 1;
            tree.left[2].p = NULL;
        }
        else
        {
            tree.glav.n = tree.right[2].n;
            tree.glav.p = 1;
            tree.right[2].p = NULL;
        }
    }
}


bool TurnirSort::pust()//проверяеет пустое ли дерево
{
    if (tree.left[0].p == NULL || tree.left[1].p == NULL || tree.right[0].p == NULL || tree.right[1].p == NULL)
        if (tree.left[2].p == NULL || tree.right[2].p == NULL)
            if (tree.glav.p == NULL)
                return true;
    return false;
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

