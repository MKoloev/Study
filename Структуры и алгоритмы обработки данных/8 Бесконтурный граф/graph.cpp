//5. Напишите программу, которая будет находить кратчайшие пути от фиксированной вершины в произвольном бесконтурном графе.
//Граф задан списками смежности.Предусмотрите ввод данных из файла.
//После завершения работы с динамическими структурами данных необходимо освободить занимаемую ими память.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

struct connections;

struct node
{
    node *Next = NULL;
    connections *Point = NULL;
};

struct connections
{
    int Length = 1000000;
    int* Path = NULL;
    int connect = -1;
    node *Next = NULL;
};


class GRAPH
{
private:
    int Size = 0;
    connections* graph = nullptr;

    void fillin();//создает файл
    void outputFromFile();

    //заполняет список
    void yzel(string enter, connections* yze);//заполняет узел 
    void addationYzel(connections* yze, int n);//добовляет отдельный элимент в спиок смежности

    void pathLength();//находит длину пути и путь
    void findPath(int* Path, int Length, node* Node);//метод который вызывает себя, ятобы пройти все вершины и найти кратчайший путь
    void replace(int* Path, int Length, connections* Node);//
public:
    ~GRAPH();

    void start();

    void outPut();
};


int main()
{
    GRAPH graph;
    graph.start();
    graph.outPut();
}


void GRAPH::start()
{
    fillin();
    outputFromFile();
    pathLength();
}


GRAPH::~GRAPH()
{
    for (size_t i = 0; i < Size; i++)
        if (graph[i].Path != NULL)
            delete[] graph[i].Path;

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
        fail << ':';
        fail << setw(5) << 1;
        fail << setw(5) << 2;
        fail << endl;

        //-----------------------
        fail << setw(4) << 1;
        fail << ':';
        fail << setw(5) << 3;
        fail << setw(5) << 4;
        fail << endl;

        //-----------------------
        fail << setw(4) << 2;
        fail << ':';
        fail << endl;

        //-----------------------
        fail << setw(4) << 3;
        fail << ':';
        fail << setw(5) << 4;
        fail << setw(5) << 5;
        fail << endl;

        //-----------------------
        fail << setw(4) << 4;
        fail << ':';
        fail << setw(5) << 5;
        fail << endl;

        //-----------------------
        fail << setw(4) << 5;
        fail << ':';
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

            if ((int)fail.tellg() <= 1)
            {                                       // If the data was at or before the 0th byte
                fail.seekg(0);                       // The first line is the last line
                keepLooping = false;                // So stop there
            }
            else if (ch == '\n')                 // If the data was a newline
                keepLooping = false;                // Stop at the current position.
            else                                 // If the data was neither a newline nor at the 0 byte
                fail.seekg(-2, ios_base::cur);        // Move to the front of that data, then to the front of the data before it
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
        graph[0].Length = 0;
    }
    fail.close();
}

void GRAPH::yzel(string enter, connections* yze)
{
    int ind = enter[3] - 48;
    yze->connect = ind;
    yze->Path = new int[Size];
    for (int i = 6; i < enter.size(); i++)
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
    if (yze->Next == NULL)
    {
        yze->Next = new node;
        yze->Next->Point = &graph[n];
        return;
    }
    node* pro = yze->Next;
    
    do
    {
        if (pro->Next == NULL)
        {
            pro->Next = new node;
            pro->Next->Point = &graph[n];
            return;
        }
        pro = pro->Next;
        if (pro == NULL)
            throw"error";
    } while (pro != NULL);
}



void GRAPH::outPut()
{
    node* pro;
    cout << endl << "---------------------------------------" << endl;
    for (int i = 0; i < Size; i++)
    {
        cout << graph[i].connect << ": ";
        pro = graph[i].Next;
        while (pro != NULL)
        {
            cout << setw(4) << pro->Point->connect;
            pro = pro->Next;
        }
        cout << endl;
    }
    cout << endl << "---------------------------------------" << endl;
    for (int i = 1; i < Size; i++)
    {
        cout << graph[i].connect<<": ";
        for (size_t j = 0; j <= graph[i].Length; j++)
            cout << graph[i].Path[j] << "   ";
        cout << endl;
    }
    pro = nullptr;
}


void GRAPH::pathLength()
{
    int Length = 0;
    int* Path = new int[Size];
    Path[Length] = 0;
    findPath(Path, Length, graph[0].Next);
    delete[] Path;
}

void GRAPH::findPath(int* Path, int Length, node* Node)
{
    Length++;
    node* pro = Node;
    while (pro != NULL)
    {
        Path[Length] = pro->Point->connect;
        replace(Path, Length, pro->Point);
        findPath(Path, Length, pro->Point->Next);
        pro = pro->Next;
    }
}


void GRAPH::replace(int* Path, int Length, connections* Node)
{
    if (Length < Node->Length)
    {
        Node->Length = Length;
        for (size_t i = 0; i <= Length; i++)
            Node->Path[i] = Path[i];
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
