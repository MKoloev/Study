// lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;



struct ListNode//узел списка
{
    int info;
    ListNode* next;
};


class List
{
private:
    struct ListNode* list;
    int country;

    void add(int number, int data);//добовляет навыйй узел на место (number), с данными (data)
    void inputEmpty(int data);//если список пустой то создает новый узел
public:
    List() : country(0) { list = NULL; }
    ~List() { delete list; }

    void addBeginning(int data);
    void addEnd(int data);

    void outputDisplay();

    int numberedOutput(int number);//выводит число по индексу

    int Size() const;//выводит размер списка

    void removeNode(int number);//удаление узла по индексу
};



void fillin(string fail, int max);// Заполняет файл чилами
void outputFromFile(string fail, List *list0);//в список записываются данные из файла
void selection(List* list0, List* list1, List* list3);//в третий список записываем числа из первого, которых нет во втором
void removalIdentical(List* list0);//удаляет все повторяюшиеся

int main()
{
    string fail1 = "fail0.txt";//название для первого файла
    string fail2 = "fail1.txt";//название для второго файла 

    fillin(fail1, 15);//создаем или открываем первый файл, и записываем в него случаййные числа от 0 до 15
    fillin(fail2, 20);//создаем или открываем второй файл, и записываем в него случаййные числа от 0 до 20

    List list1;//создаем списки
    List list2;
    List list3;

    outputFromFile(fail1, &list1);//в первый список записываем данные из первого файла
    outputFromFile(fail2, &list2);//в второй список записываем данные из второго файла

    list1.outputDisplay();//выводим на экран содержимое первого списка
    list2.outputDisplay();//выводим на экран содержимое второго списка

    selection(&list1, &list2, &list3);//в третий список записываем числа из первого, которых нет во втором
    selection(&list2, &list1, &list3);//в третий список записываем числа из второго, которых нет в первом

    removalIdentical(&list3);//удаляем из третьего списка повторяюшиеся числа

    list3.outputDisplay();// выводим на экран третий список
}

void fillin(string fail, int max)// Заполняет файл чилами
{
    ofstream fail1;
    fail1.open(fail);//открывает или создает файл

    if (!fail1.is_open())// проверка открылся он или нет
    {
        cout << "не открылся" << endl;
    }
    else
    {
        int enter = 0;
        for (size_t i = 0; i < 13; i++) {
            enter = 0 + rand() % max;// случайные числа
            fail1 << enter << " ";
        }
    }
    fail1.close();
}

void outputFromFile(string fail, List *list0)//в список записываются данные из файла
{
    ifstream fail1;
    fail1.open(fail);
    if (!fail1.is_open())
    {
        cout << "No" << endl;
        return;
    }
    else
    {
        string enter;
        int num = 0;
        while (!fail1.eof())
        {
            num = 0;   enter = "";
            fail1 >> enter;//выводит число из файла
            if (enter != "")
            {
                num = stoi(string(enter));//преврашает его из string в int
                list0->addEnd(num);
            }
        }
    }
}

void selection(List* list0, List* list1, List* list3)
{
    int dataList1 = 0;
    int dataList2 = 0;
    for (int i = 1; i < (list0->Size() + 1); i++)
    {
        dataList1 = list0->numberedOutput(i);
        for (int j = 1; j < (list1->Size() + 1); j++)
        {
            dataList2 = list1->numberedOutput(j);
            if (dataList1 == dataList2)
                break;
            if (j == list1->Size())
                list3->addEnd(dataList1);
        }
    }
}


void removalIdentical(List* list0)
{
    if (list0->Size() == 0)
    {
        cout << "error" << endl;
        return;
    }
    else
    {
        int dataList1 = 0;
        int dataList2 = 0;
        for (int i = 1; i <= list0->Size(); i++)
        {
            dataList1 = list0->numberedOutput(i);
            for (int j = i + 1; j <= list0->Size(); j++)
            {
                dataList2 = list0->numberedOutput(j);
                if (dataList1 == dataList2)
                {
                    list0->removeNode(j);
                }
            }
        }
    }
}


void List::add(int number, int data)
{
    if (number > (country + 1))//если номер больше чем колличество узлов
        number = country + 1;
    int countryNode = 1;
    struct ListNode* node;
    node = list;

    while (number >= countryNode && node != NULL)
    {
        if ((countryNode) == (number))//Если следуююший узел место куда, надо вставлять новый
        {
            struct ListNode* newNode = new ListNode;
            newNode->info = node->info;//в новый узел записываем, данные из узла в место которого мы должны постовать новый
            newNode->next = node->next;
            node->info = data;//в стары узел записывам новые данные
            node->next = newNode;
            country++;
            break;
        }
        if (node->next == NULL)//если это последний узел
        {
            struct ListNode* newNode = new ListNode;
            newNode->info = data;
            newNode->next = NULL;
            node->next = newNode;
            country++;
            break;
        }
        node = node->next;
        countryNode++;
    }
}

void List::inputEmpty(int data)//если в списке ничго нет
{
    struct ListNode* node = new ListNode;
    node->info = data;
    node->next = NULL;
    list = node;
    country++;
}


void List::addBeginning(int data)
{
    if (list == NULL)
        inputEmpty(data);
    else
        add(1, data);
}

void List::addEnd(int data)
{
    if (list == NULL)
        inputEmpty(data);
    else
        add(country + 1, data);
}

void  List::outputDisplay()
{
    struct ListNode* node;
    node = list;
    int countryNode = 1;
    while (node != NULL)
    {
        std::cout << countryNode << ")" << node->info << "      ";
        node = node->next;
        countryNode++;
    }
    cout << endl<<endl;
}

int List::numberedOutput(int number)//выводит число по индексу
{
    struct ListNode* node;
    node = list;
    int countryNode = 1;
    if (list == NULL)
    {
        cout << "error" << endl;
        return 0;
    }
    if (number > country || number < 1)
    {
        cout << "error" << endl;
        return 0;
    }

    while (node != NULL || countryNode >= number)
    {
        if (countryNode == number && node != NULL)
            return (node->info);
        node = node->next;
        countryNode++;
    }
    return 0;
}

int List::Size() const
{
    return country;
}

void List::removeNode(int number)
{
    if (list == NULL || number > country || number < 1)
    {
        cout << "error no node" << endl;
        return;
    }
    else
    {
        int countryNode = 1;
        struct ListNode* node;
        node = list;
        while (countryNode <= number || node->next != NULL)
        {
            if (countryNode == (number-1))
            {
                country--;
                node->next = node->next->next;
            }
            node = node->next;
            countryNode++;
        }
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
