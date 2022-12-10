//5. ��������� ����, ������ ��������� ������.
//� ��������� ����� T ������� �����, ���������������� �� ������� �������:
//<�����> ::= <�����> | <�������><�����><�������> ::= <�����> | (<�����>)
//��������� ��� ������ ���� ������ ���������� ������ �� ������� � ������ � ������� �����������
//������� ������� ����������� ������. ��������, ��� ������ A + (45 - F(X) * (B - C)) ����� ���������� 3 17; 8 10; 12 16.
//��� ���������� ��� ���� ������������ ������.


#include <iostream>
#include <fstream>
#include <cstdlib>
#define SIZE 100
using namespace std;
class Stack
{
private:
    int stack[SIZE];
    int numberLast;
public:
    Stack():numberLast(-1) { cout << "Stack created" << endl; }

    /// <summary>
    /// �������� � ����
    /// </summary>
    /// <param name="a"></param>
    void Push(int a)
    {
        if (numberLast == SIZE) // �������� �� ������� ��������� �������� � ����������
        {
            printf("������� ��������� �������� � ������ ����");
            exit(EXIT_FAILURE);
        }
        else
        {
            numberLast++;
            stack[numberLast] = a;
        }
    }

    /// <summary>
    /// ������� �� �����
    /// </summary>
    /// <returns></returns>
    int Pop()
    {
        if (numberLast == -1) // �������� �� ������� ������� ������� �� ������������
        {
            printf("������� ������ �� ������� �����");
            exit(EXIT_FAILURE);
        }
        else
        {
            int value = 0;
            value = stack[numberLast];
            numberLast--;
            return(value);
        }
    }


    /// <summary>
    /// �������� �������� �������� �������� �����
    /// </summary>
    /// <returns></returns>
    int Top() const
    {
        return(stack[numberLast]);
    }


    /// <summary>
    /// ���������, �������� �� ���� ������
    /// </summary>
    /// <returns></returns>
    bool IsEmpty()
    {
        if (numberLast == -1)
            return(true);
        else
            return(false);
    }

};

void fillin();// � ���� ������ �����
int outputFromFile(Stack*);/// �� ������� ������� ������ ������ ������

int main()
{
    Stack A;
    int numerseconParenthesiNumber[SIZE];
    fillin();
    int j = outputFromFile(&A);
    cout << endl;
}


/// ��������� ���� ��������
void fillin()
{
    ofstream fail1;
    fail1.open("fail.txt");//��������� ����

    if (!fail1.is_open())
    {
        cout << "Did not open" << endl;//��������� ���� ���� �� ��������
    }
    else
    {
        string text1 = "(A+(45-F(X)*(B-C)))";
        fail1 << text1 << endl;//�������� ������ ����� ��������� �� ��������� ������
    }
    fail1.close();
}


/// ������� � ������ ��� ����� �� �����
int outputFromFile(Stack* A)
{
    int j = 0;
    ifstream fail1;
    fail1.open("fail.txt");
    if (!fail1.is_open())
    {
        cout << "Did not open" << endl;
        return 0;
    }
    else
    {
        int i = 0;
        char elem = 0;

        while (!fail1.eof())
        {
            elem = 0;
            fail1 >> elem;//������� ������� �� �����
            cout << elem;
        }
        cout << endl;
        fail1.clear();
        fail1.seekg(0);

        while (!fail1.eof() && j < SIZE)
        {
            i++;
            elem = 0;
            fail1 >> elem;//������� ������� �� �����
            if (elem == '(')
                A->Push(i);//���������� � ���� ��������
            if (elem == ')')
                cout << A->Pop() << " " << i << "     ";
        }
    }
    fail1.close();
    return j;
}
