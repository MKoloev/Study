// lab3.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;



struct ListNode//���� ������
{
    int info;
    ListNode* next;
};


class List
{
private:
    struct ListNode* list;
    int country;

    void add(int number, int data);//��������� ������ ���� �� ����� (number), � ������� (data)
    void inputEmpty(int data);//���� ������ ������ �� ������� ����� ����
public:
    List() : country(0) { list = NULL; }
    ~List() { delete list; }

    void addBeginning(int data);
    void addEnd(int data);

    void outputDisplay();

    int numberedOutput(int number);//������� ����� �� �������

    int Size() const;//������� ������ ������

    void removeNode(int number);//�������� ���� �� �������
};



void fillin(string fail, int max);// ��������� ���� ������
void outputFromFile(string fail, List *list0);//� ������ ������������ ������ �� �����
void selection(List* list0, List* list1, List* list3);//� ������ ������ ���������� ����� �� �������, ������� ��� �� ������
void removalIdentical(List* list0);//������� ��� �������������

int main()
{
    string fail1 = "fail0.txt";//�������� ��� ������� �����
    string fail2 = "fail1.txt";//�������� ��� ������� ����� 

    fillin(fail1, 15);//������� ��� ��������� ������ ����, � ���������� � ���� ���������� ����� �� 0 �� 15
    fillin(fail2, 20);//������� ��� ��������� ������ ����, � ���������� � ���� ���������� ����� �� 0 �� 20

    List list1;//������� ������
    List list2;
    List list3;

    outputFromFile(fail1, &list1);//� ������ ������ ���������� ������ �� ������� �����
    outputFromFile(fail2, &list2);//� ������ ������ ���������� ������ �� ������� �����

    list1.outputDisplay();//������� �� ����� ���������� ������� ������
    list2.outputDisplay();//������� �� ����� ���������� ������� ������

    selection(&list1, &list2, &list3);//� ������ ������ ���������� ����� �� �������, ������� ��� �� ������
    selection(&list2, &list1, &list3);//� ������ ������ ���������� ����� �� �������, ������� ��� � ������

    removalIdentical(&list3);//������� �� �������� ������ ������������� �����

    list3.outputDisplay();// ������� �� ����� ������ ������
}

void fillin(string fail, int max)// ��������� ���� ������
{
    ofstream fail1;
    fail1.open(fail);//��������� ��� ������� ����

    if (!fail1.is_open())// �������� �������� �� ��� ���
    {
        cout << "�� ��������" << endl;
    }
    else
    {
        int enter = 0;
        for (size_t i = 0; i < 13; i++) {
            enter = 0 + rand() % max;// ��������� �����
            fail1 << enter << " ";
        }
    }
    fail1.close();
}

void outputFromFile(string fail, List *list0)//� ������ ������������ ������ �� �����
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
            fail1 >> enter;//������� ����� �� �����
            if (enter != "")
            {
                num = stoi(string(enter));//���������� ��� �� string � int
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
    if (number > (country + 1))//���� ����� ������ ��� ����������� �����
        number = country + 1;
    int countryNode = 1;
    struct ListNode* node;
    node = list;

    while (number >= countryNode && node != NULL)
    {
        if ((countryNode) == (number))//���� ���������� ���� ����� ����, ���� ��������� �����
        {
            struct ListNode* newNode = new ListNode;
            newNode->info = node->info;//� ����� ���� ����������, ������ �� ���� � ����� �������� �� ������ ��������� �����
            newNode->next = node->next;
            node->info = data;//� ����� ���� ��������� ����� ������
            node->next = newNode;
            country++;
            break;
        }
        if (node->next == NULL)//���� ��� ��������� ����
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

void List::inputEmpty(int data)//���� � ������ ����� ���
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

int List::numberedOutput(int number)//������� ����� �� �������
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
// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.
