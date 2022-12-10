//6. Напишите программу, которая находит множество фундаментальных циклов связного неориентированного графа.Для представления графа в
//программе использовать списки смежности.Данные о графе вводятся из файла. .
//Программа должна вывести для каждого фундаментального цикла множество вершин, входящих в каждый из найденных циклов.
//После завершения работы с динамическими структурами данных необходимо освободить занимаемую ими память.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;


struct node
{
    int connect = -1;
    node *Next = NULL;
};

struct connections
{
    int vertex = -1;
    node* Next = NULL;
};


class GRAPH
{
public:
    int Size = 4;
    connections* graph = nullptr;

    void fillin();//создает файл
    void outputFromFile();//выводит из файла

    //заполняет список
    void yzel(string enter, connections* yze);//
    void addationYzel(connections* yze, int n);

    void fundZikl();
    void outPut();
    bool proverka(int a, int b, int c);

    ~GRAPH();
};



int main()
{
    GRAPH graph;
    graph.fillin();
    graph.outputFromFile();
    graph.outPut();
    graph.fundZikl();
}


GRAPH::~GRAPH()
{
    if (graph != nullptr)
        delete[] graph;
}


void GRAPH::fillin()
{
    ofstream fail;
    fail.open("graph.txt");//открывает или создает файл

    if (!fail.is_open())// проверка открылся он или нет
    {
        cout << "не открылся" << endl;
    }
    else
    {
       //-----------------------
        fail << setw(4) << 0;
        fail <<':';
        fail << setw(5) << 1; 
        fail << setw(5) << 4;
        fail << endl;

        //-----------------------
        fail << setw(4) << 1;
        fail << ':';
        fail << setw(5) << 0;
        fail << setw(5) << 2;
        fail << setw(5) << 3;
        fail << setw(5) << 4;
        fail << endl;

        //-----------------------
        fail << setw(4) << 2;
        fail << ':';
        fail << setw(5) << 1;
        fail << setw(5) << 3;
        fail << endl;

        //-----------------------
        fail << setw(4) << 3;
        fail << ':';
        fail << setw(5) << 1;
        fail << setw(5) << 2;
        fail << setw(5) << 4;
        fail << endl;

        //-----------------------
        fail << setw(4) << 4;
        fail << ':';
        fail << setw(5) << 0;
        fail << setw(5) << 1;
        fail << setw(5) << 3;
    }
    fail.close();
}

void GRAPH::outputFromFile()
{
    ifstream fail;

    fail.open("graph.txt");
    if (!fail.is_open())
    {
        cout << "No" << endl;
        return;
    }
    else
    {
        fail.seekg(-1, ios_base::end);                // go to one spot before the EOF

        bool keepLooping = true;
        while (keepLooping) {
            char ch;
            fail.get(ch);                            // Get current byte's data

            if ((int)fail.tellg() <= 1) {             // If the data was at or before the 0th byte
                fail.seekg(0);                       // The first line is the last line
                keepLooping = false;                // So stop there
            }
            else if (ch == '\n') {                   // If the data was a newline
                keepLooping = false;                // Stop at the current position.
            }
            else {                                  // If the data was neither a newline nor at the 0 byte
                fail.seekg(-2, ios_base::cur);        // Move to the front of that data, then to the front of the data before it
            }
        }
        fail >> Size;
        Size++;

        fail.seekg(0, ios::beg);
        graph = new connections[Size];
        string enter;
        int i = 0;
        while (!fail.eof())
        {
            enter = "";
            getline(fail, enter);
            yzel(enter, &graph[i++]);
        }
    }
    fail.close();
}


void GRAPH::yzel(string enter, connections* yze)
{
    int ind = 0;
    for (int i = 3; i < enter.size(); i++)
    {
        if (enter[i] > 47 && enter[i] < 58)
        {
            ind = enter[i] - 48;
            addationYzel(yze, ind);
        }
    }
}

void GRAPH::addationYzel(connections* yze, int n)
{
    if (yze->vertex < 0)
    {
        yze->vertex = n;
        return;
    }
    node* pro = yze->Next;
    if (pro == NULL)
    {
        yze->Next = new node;
        yze->Next->connect = n;
        return;
    }
    do 
    {
        if (pro->Next == NULL)
        {
            pro->Next = new node;
            pro->Next->connect = n;
            return;
        }
        pro = pro->Next;
        if (pro == NULL)
            throw"error";
    } while (pro != NULL);
}



void GRAPH::fundZikl()
{
    node* pro;
    node* pro1;
    int zikl1 = 0, zikl2 = 0;
    cout << endl << "---------------------------------------" << endl;
    for (int i = 0; i < Size - 2; i++)
    {
        pro = graph[i].Next;
        while (pro != NULL)
        {
            while ((pro->connect < graph[i].vertex) && pro->Next != NULL)
                pro = pro->Next;
            if (pro->Next == NULL)
                break;

            pro1 = pro->Next;
            while (pro1 != NULL)
            {
                if(proverka(graph[i].vertex, pro->connect, pro1->connect))
                    cout << graph[i].vertex << "   " << pro->connect << "   " << pro1->connect<<endl;
               // cout << graph[i].vertex << "   " << pro->connect << "   " << pro1->connect << endl;
                pro1 = pro1->Next;
            } 
            pro = pro->Next;
        } 
    }
}



bool GRAPH::proverka(int a, int b, int c)
{
    node* pro;
    int prov = 0;
    pro = graph[b].Next;
    while (pro != NULL)
    {
        if (pro->connect == a)
            prov++;
        if (pro->connect == c)
            prov++;
        pro = pro->Next;
    }
    pro = graph[c].Next;
    while (pro != NULL)
    {
        if (pro->connect == a)
            prov++;
        if (pro->connect == b)
            prov++;
        pro = pro->Next;
    }
    if (prov == 4)
        return true;
    else
        return false;
}



void GRAPH::outPut()
{
    node* pro;
    cout << endl << "---------------------------------------" << endl;
    for (int i = 0; i < Size; i++)
    {
        cout << graph[i].vertex << ": ";
        pro = graph[i].Next;
        do
        {
            cout << setw(4) << pro->connect;
            pro = pro->Next;
        } while (pro != NULL);

        cout << endl;
    }
    pro = nullptr;
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
