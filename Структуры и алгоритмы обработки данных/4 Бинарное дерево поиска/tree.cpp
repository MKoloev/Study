//Напишите программу, которая формирует бинарное дерево поиска, выводит построенное дерево на экран.
//Данные для построения дерева могут вводиться с клавиатуры, из файла или генерироваться с помощью генератора случайных чисел.
//Выбор способа ввода данных выполняется во время работы программы.В построенном дереве необходимо подсчитать число элементов,
//которые попадают в заданный интервал.Числа, определяющие интервал вводятся с клавиатуры.
//Для реализации АТД «Дерево» используйте динамическое распределение памяти.
//Перед завершением работы программы освободить занимаемую динамическую память.
//Для этого используйте поэлементное удаление элементов динамической структуры данных.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;


class FILLINGWood;

struct Node
{
    int x;//// Информация в вершине.
    Node* left;// Левая сын.
    Node* right;// Правый сын.
};

class TREE
{
private:
    Node* tTree;//вершина дерева

	//Создает новый узел
	void addNodeImplementation(int x, Node*& Tree)
	{
		if (Tree == NULL)//как только доходим до конца каково нибудь ветви, то создается новый узел
		{
			Tree = new Node;
			Tree->x = x;
			Tree->left = NULL;
			Tree->right = NULL;
		}
		if ((Tree->x) > x) //Если число нового узла меньше чем у нынешнего узла, то идем в лево
		{
			addNodeImplementation(x, Tree->left);
		}
		if ((Tree->x) < x) //Если число нового узла больше чем у нынешнего узла, то идем в право
		{
			addNodeImplementation(x, Tree->right);
		}

	}

	//Определяет когда выводит на консоль число
	int consoleOutputImplementation(int x, Node*& Tree)
	{

		if (Tree == NULL)//если пустой узел, то значит нет на этой ветке такой длины, значит ветвь длиной (x)
		{
			return x;
		}
		x++;//узел не пустой значит надо будет ставить (x) пробелов
		x = consoleOutputImplementation(x, Tree->right);
		for (int i = 0; i < (x*3); i++)
		{
			cout << " ";
		}
		cout << Tree->x << endl;
		x = consoleOutputImplementation(x, Tree->left);
		return --x;
	}

	//поэлементно удаляет элементы динамической структуры
	void deleted(Node*& Tree)
	{
		if (Tree != NULL)
		{
			if ((Tree->right) != NULL) //Если число нового узла меньше чем у нынешнего узла, то идем в лево
			{
				deleted(Tree->right);
				Tree->right = NULL;
			}
			if ((Tree->left) != NULL) //Если число нового узла больше чем у нынешнего узла, то идем в право
			{
				deleted(Tree->left);
				Tree->left = NULL;
			}
		}
	}

	//подсчитывает числа на интервале [A,B]
	int segmentSearch(int x, Node*& Tree, int A, int B)
	{
		if (Tree != NULL)
		{
			if(A < (Tree->x))
				x = segmentSearch(x, Tree->left, A, B);
			if(B > (Tree->x))
				x = segmentSearch(x, Tree->right, A, B);
			if (A < (Tree->x) && (Tree->x) < B)
				x++;

		}
		return x;
	}

public:
	TREE()
	{
		tTree = NULL;
	}
	~TREE()
	{
		deleted(tTree);
		if (!isEmpty())
			tTree = NULL;
	}


	//просверяет пустое ли дерево
	bool isEmpty()
	{
		if (tTree == NULL)
			return true;
		else
			return false;
	}

	//Добовляет новый узел
	void addNode(int x)
	{
		addNodeImplementation(x, tTree);//реализация метода для добавления нового узла
	}

	//Выводит на экран дерево
	void consoleOutput()
	{
		cout << endl << "------------------------------------------" << endl;
		consoleOutputImplementation(0, tTree);
		cout << endl << "__________________________________________" << endl;
	}

	int segmentSearch(int A, int B)
	{
		return segmentSearch(0, tTree, A, B);
	}
};



class FILLINGWood
{
private:
	int choice;
	void fillinFail(int max);// Заполняет файл чиcлами
	void treeEntryFail(TREE *tree);//Заполняет дерево, числами из файла
	void treeEnterConsole(TREE *tree);//Чтобы заполнить дерево, через консоль
	void treeEnter(TREE* tree);//Заполняет дерево, случайными числами
public:
	FILLINGWood(TREE *tree)
	{
		do {
			choice = 0;
			//Чтобы заполнить дерево через файл, введите 1
			cout << "To populate the tree through a file, enter 1" << endl;
			//Чтобы заполнить дерево через консоль, введите 2
			cout << "To populate the tree through the console, enter 2" << endl;
			//Чтобы заполнить дерево случайными числами, введите 3
			cout << "To fill the tree with random numbers, enter 3" << endl;
			if (!(cin >> choice))
			{
				cout << "error";
				break;
			}
			cout << endl;
		} while (choice != 1 && choice != 2 && choice != 3);

		//определяет
		switch (choice)
		{
		case 1:
			fillinFail(20);// Заполняет файл чиcлами
			treeEntryFail(tree);//Заполняет дерево, числами из файла
				break;
		case 2:
			treeEnterConsole(tree);//Чтобы заполнить дерево, через консоль
				break;
		case 3:
			treeEnter(tree);//Заполняет дерево, случайными числами
				break;
		default:
			break;
		}
	}


};


int main()
{
	TREE tree;
	FILLINGWood fil(&tree);
	tree.consoleOutput();

	int x = tree.segmentSearch(0, 10);
	cout << "on the interval (0,10): " <<x << endl;
}


void FILLINGWood::fillinFail(int max)// Заполняет файл чилами
{
	string fail = "fail.txt";
	ofstream fail1;
	fail1.open(fail);//открывает или создает файл

	if (!fail1.is_open())// проверка открылся он или нет
	{
		cout << "не открылся" << endl;
	}
	else
	{
		int enter = 0;
		for (size_t i = 0; i < 12; i++) {
			enter = 0 + rand() % max;// случайные числа
			fail1 << enter << " ";
		}
	}
	fail1.close();
}

void FILLINGWood::treeEntryFail(TREE *tree)
{
	string fail = "fail.txt";
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
				tree->addNode(num);
			}
		}
	}
}

void FILLINGWood::treeEnterConsole(TREE* tree)
{
	cout << "enter the number of numbers" << endl;
	int col1 = 0;
	int number1 = 0;
	cin >> col1;
	for (int i = 0; i < col1; i++)
	{
		cout << "enter num: ";
		if (!(cin >> number1))
		{
			cout << "error";
			break;
		}
		tree->addNode(number1);
	}
}

void FILLINGWood::treeEnter(TREE* tree)
{
	int num = 0;
	for (int i = 0; i < 15; i++)
	{
		num = 0 + rand() %30;// случайные числа
		tree->addNode(num);

	}
}
