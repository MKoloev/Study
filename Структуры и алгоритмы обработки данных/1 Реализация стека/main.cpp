//5. Используя стек, решить следующую задачу.
//В текстовом файле T записан текст, сбалансированный по круглым скобкам:
//<текст> ::= <пусто> | <элемент><текст><элемент> ::= <буква> | (<текст>)
//Требуется для каждой пары скобок напечатать номера их позиций в тексте в порядке возрастания
//номером позиций открывающих скобок. Например, для текста A + (45 - F(X) * (B - C)) нужно напечатать 3 17; 8 10; 12 16.
//Для реализации АТД Стек использовать массив.


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
    /// положить в стек
    /// </summary>
    /// <param name="a"></param>
    void Push(int a)
    {
        if (numberLast == SIZE) // проверка на попытку занесения элемента в полныйстек
        {
            printf("Попытка занесения значения в полный стек");
            exit(EXIT_FAILURE);
        }
        else
        {
            numberLast++;
            stack[numberLast] = a;
        }
    }

    /// <summary>
    /// забрать из стека
    /// </summary>
    /// <returns></returns>
    int Pop()
    {
        if (numberLast == -1) // проверка на попытку забрать элемент из пустогостека
        {
            printf("Попытка чтения из пустого стека");
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
    /// получить значение верхнего элемента стека
    /// </summary>
    /// <returns></returns>
    int Top() const
    {
        return(stack[numberLast]);
    }


    /// <summary>
    /// проверить, является ли стек пустым
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

void fillin();// в файл вводит текст
int outputFromFile(Stack*);/// на консоль выводит номера парных скобки

int main()
{
    Stack A;
    int numerseconParenthesiNumber[SIZE];
    fillin();
    int j = outputFromFile(&A);
    cout << endl;
}


/// Заполняет файл формулой
void fillin()
{
    ofstream fail1;
    fail1.open("fail.txt");//открывает файл

    if (!fail1.is_open())
    {
        cout << "Did not open" << endl;//выводится если файл не открылся
    }
    else
    {
        string text1 = "(A+(45-F(X)*(B-C)))";
        fail1 << text1 << endl;//вводится первое число переходит на следуюшюю строку
    }
    fail1.close();
}


/// выводит в массив все числа из файла
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
            fail1 >> elem;//выводит элимент из файла
            cout << elem;
        }
        cout << endl;
        fail1.clear();
        fail1.seekg(0);

        while (!fail1.eof() && j < SIZE)
        {
            i++;
            elem = 0;
            fail1 >> elem;//выводит элимент из файла
            if (elem == '(')
                A->Push(i);//записывает в стэк скобочку
            if (elem == ')')
                cout << A->Pop() << " " << i << "     ";
        }
    }
    fail1.close();
    return j;
}
