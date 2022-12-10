//�������� ���������, ������� ��������� �������� ������ ������, ������� ����������� ������ �� �����.
//������ ��� ���������� ������ ����� ��������� � ����������, �� ����� ��� �������������� � ������� ���������� ��������� �����.
//����� ������� ����� ������ ����������� �� ����� ������ ���������.� ����������� ������ ���������� ���������� ����� ���������,
//������� �������� � �������� ��������.�����, ������������ �������� �������� � ����������.
//��� ���������� ��� ������� ����������� ������������ ������������� ������.
//����� ����������� ������ ��������� ���������� ���������� ������������ ������.
//��� ����� ����������� ������������ �������� ��������� ������������ ��������� ������.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;


class FILLINGWood;

struct Node
{
    int x;//// ���������� � �������.
    Node* left;// ����� ���.
    Node* right;// ������ ���.
};

class TREE
{
private:
    Node* tTree;//������� ������

	//������� ����� ����
	void addNodeImplementation(int x, Node*& Tree)
	{
		if (Tree == NULL)//��� ������ ������� �� ����� ������ ������ �����, �� ��������� ����� ����
		{
			Tree = new Node;
			Tree->x = x;
			Tree->left = NULL;
			Tree->right = NULL;
		}
		if ((Tree->x) > x) //���� ����� ������ ���� ������ ��� � ��������� ����, �� ���� � ����
		{
			addNodeImplementation(x, Tree->left);
		}
		if ((Tree->x) < x) //���� ����� ������ ���� ������ ��� � ��������� ����, �� ���� � �����
		{
			addNodeImplementation(x, Tree->right);
		}

	}

	//���������� ����� ������� �� ������� �����
	int consoleOutputImplementation(int x, Node*& Tree)
	{

		if (Tree == NULL)//���� ������ ����, �� ������ ��� �� ���� ����� ����� �����, ������ ����� ������ (x)
		{
			return x;
		}
		x++;//���� �� ������ ������ ���� ����� ������� (x) ��������
		x = consoleOutputImplementation(x, Tree->right);
		for (int i = 0; i < (x*3); i++)
		{
			cout << " ";
		}
		cout << Tree->x << endl;
		x = consoleOutputImplementation(x, Tree->left);
		return --x;
	}

	//����������� ������� �������� ������������ ���������
	void deleted(Node*& Tree)
	{
		if (Tree != NULL)
		{
			if ((Tree->right) != NULL) //���� ����� ������ ���� ������ ��� � ��������� ����, �� ���� � ����
			{
				deleted(Tree->right);
				Tree->right = NULL;
			}
			if ((Tree->left) != NULL) //���� ����� ������ ���� ������ ��� � ��������� ����, �� ���� � �����
			{
				deleted(Tree->left);
				Tree->left = NULL;
			}
		}
	}

	//������������ ����� �� ��������� [A,B]
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


	//���������� ������ �� ������
	bool isEmpty()
	{
		if (tTree == NULL)
			return true;
		else
			return false;
	}

	//��������� ����� ����
	void addNode(int x)
	{
		addNodeImplementation(x, tTree);//���������� ������ ��� ���������� ������ ����
	}

	//������� �� ����� ������
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
	void fillinFail(int max);// ��������� ���� ��c����
	void treeEntryFail(TREE *tree);//��������� ������, ������� �� �����
	void treeEnterConsole(TREE *tree);//����� ��������� ������, ����� �������
	void treeEnter(TREE* tree);//��������� ������, ���������� �������
public:
	FILLINGWood(TREE *tree)
	{
		do {
			choice = 0;
			//����� ��������� ������ ����� ����, ������� 1
			cout << "To populate the tree through a file, enter 1" << endl;
			//����� ��������� ������ ����� �������, ������� 2
			cout << "To populate the tree through the console, enter 2" << endl;
			//����� ��������� ������ ���������� �������, ������� 3
			cout << "To fill the tree with random numbers, enter 3" << endl;
			if (!(cin >> choice))
			{
				cout << "error";
				break;
			}
			cout << endl;
		} while (choice != 1 && choice != 2 && choice != 3);

		//����������
		switch (choice)
		{
		case 1:
			fillinFail(20);// ��������� ���� ��c����
			treeEntryFail(tree);//��������� ������, ������� �� �����
				break;
		case 2:
			treeEnterConsole(tree);//����� ��������� ������, ����� �������
				break;
		case 3:
			treeEnter(tree);//��������� ������, ���������� �������
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


void FILLINGWood::fillinFail(int max)// ��������� ���� ������
{
	string fail = "fail.txt";
	ofstream fail1;
	fail1.open(fail);//��������� ��� ������� ����

	if (!fail1.is_open())// �������� �������� �� ��� ���
	{
		cout << "�� ��������" << endl;
	}
	else
	{
		int enter = 0;
		for (size_t i = 0; i < 12; i++) {
			enter = 0 + rand() % max;// ��������� �����
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
			fail1 >> enter;//������� ����� �� �����
			if (enter != "")
			{
				num = stoi(string(enter));//���������� ��� �� string � int
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
		num = 0 + rand() %30;// ��������� �����
		tree->addNode(num);

	}
}
