//5)Используя очередь, решить следующую задачу.За один просмотр файла 
//с данными и без использования дополнительных файлов напечатать элементы 
//этого файла в следующем порядке : сначала – все числа, меньшие A, 
//затем – все числа из отрезка[A, B], и наконец – все остальные числа, 
//сохраняя исходный взаимный порядок в каждой из этих групп чисел.A и B – вводятся
//с клавиатуры(A < B).
//Для реализации АТД Очередь использовать динамическое распределение памяти.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

struct QueueNode
{
    int info;
    QueueNode* next;
};

struct Queue
{
    QueueNode* BeginQueue;
    QueueNode* EndQueue;
};



void fillin();// Заполняет файл чилами
int outputFromFile(Queue*, Queue*, Queue*);

void init(Queue*);//освобождение очереди.
void EnQueue(int, Queue*);//добовление элимента в очередь
int DeQueue(Queue*);//вывести первое число

void outputOnDisplay(Queue*);

int main()
{
    fillin();
    struct Queue* lessA = new Queue;//чила до А
    init(lessA);
    struct Queue* gap = new Queue;//числа от А до В
    init(gap);
    struct Queue* rest = new Queue;//все остальные числа
    init(rest);
    outputFromFile(lessA, gap, rest);

    outputOnDisplay(lessA);
    outputOnDisplay(gap);
    outputOnDisplay(rest);

    delete lessA;
    delete gap;
    delete rest;
}


/// <summary>
/// Заполняет файл чилами
/// </summary>
void fillin()
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
            enter = 0 + rand() % 20;
            fail1 << enter << " ";
        }
    }
    fail1.close();
}


void init(Queue* A)//освобождение очереди.
{
    A->BeginQueue = NULL;
    A->EndQueue = NULL;
}

void EnQueue(int x, Queue* A) 
{
    QueueNode* p;//новый узел очереди
    p = new QueueNode;
    p->info = x;
    p->next = NULL;
    if (A->BeginQueue == NULL)
        A->BeginQueue = p;
    else
        A->EndQueue->next = p;
    A->EndQueue = p;
}

int DeQueue(Queue* A)
{
    int val;
    QueueNode* p;
    p = new QueueNode;
    p = A->BeginQueue;
    val = A->BeginQueue->info;
    A->BeginQueue = p->next;
    if (A->BeginQueue == NULL)
        A->EndQueue = NULL;
    delete p;
    return(val);
}


/// <summary>
/// выводит в массив все числа из файла
/// </summary>
/// <param name="Array1"></param>
/// <returns></returns>
int outputFromFile(Queue* lessA, Queue* gap, Queue* rest)
{
    ifstream fail1;
    fail1.open("fail.txt");
    if (!fail1.is_open())
    {
        cout << "No" << endl;
        return 0;
    }
    else
    {
        int num = 0;
        string enter;
        int A = 0, B = 0;
        do {
            cout << "Enter A: ";
            cin >> A;
            cout << "Enter B: ";
            cin >> B;
            if (A >= B)
                cout << "error" << endl << endl;
        } while (A >= B);

        while (!fail1.eof())
        {
            num = 0;
            enter = "";
            fail1 >> enter;//выводит число из файла
            if (enter != "") {
                num = stoi(string(enter));//преврашает его из string в int
                
                if (num < A)
                    EnQueue(num, lessA);
                if (num >= A && num < B)
                    EnQueue(num, gap);
                if(num >= B)
                    EnQueue(num, rest);
            }
        }

    }
    fail1.close();
    return 0;
}


void outputOnDisplay(Queue* A)
{
    int n = 0;
    while (A->BeginQueue != NULL || A->EndQueue != NULL)
    {
        if (A->BeginQueue != NULL)
        {
            n = A->BeginQueue->info;
            cout << n << "  ";
        }
        DeQueue(A);
    }
    cout << endl;
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
