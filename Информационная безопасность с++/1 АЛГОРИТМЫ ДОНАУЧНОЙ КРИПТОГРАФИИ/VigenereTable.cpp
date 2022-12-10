#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int SizeArray = 256;

class VigenereTable
{
private:
    static const int sizeKey = 4;
    static const int alphabetShift = 65;
    static const int numberLastLetter = 90;

    static char encryptLetter(char letter, int nummberletter);
    static char decipherLetter(char letter, int nummberletter);

public:
    static char* encryptText(char* sourceText, char* ciphertext, int sizeText);
    static char* decipherText(char* ciphertext, char* sourceText, int sizeText);


};


int outputFromFile(char* outputFile, char* sourceText);
void inputFromFile(char* outputFile, char* ciphertext, int sizeText);


int main()
{
    char encryptFileInput[]{ "EncryptTextInput.txt" };
    char encryptFileOutput[]{ "EncryptTextOutput.txt" };
    char sourceText[SizeArray];
    char ciphertext[SizeArray];

    //ШИФРОВКА
    int sizeText = outputFromFile(encryptFileInput, sourceText);
    VigenereTable::encryptText(sourceText, ciphertext, sizeText);
    inputFromFile(encryptFileOutput, ciphertext, sizeText);

    //РАСШИФРОВКА
    char decipherFileInput[]{ "DecipherTextInput.txt" };
    char decipherFileOutput[]{ "DecipherTextOutput.txt" };

    sizeText = outputFromFile(decipherFileInput, ciphertext);
    VigenereTable::decipherText(ciphertext, sourceText, sizeText);
    inputFromFile(decipherFileOutput, sourceText, sizeText);

    return 0;
}



int outputFromFile(char* outputFile, char* sourceText)
{
    ifstream fail;
    
    fail.open(outputFile, 'a');
    if (!fail.is_open())
    {
        cout << "No" << endl;
        return NULL;
    }
    else
    {
        char enter;
        int sizeText = 0;
        for (int i = 0; i < SizeArray && !fail.eof(); i++, sizeText++)
        {
            fail >> enter;//выводит число из файла
            sourceText[i] = enter;
        }
        fail.close();
        return sizeText - 1;
    }
}

void inputFromFile(char* inputFile, char* ciphertext, int sizeText)
{
    ofstream fail;

    fail.open(inputFile, ios_base::app);
    if (!fail.is_open())
    {
        cout << "No" << endl;
        return;
    }
    else
    {
        fail << '\n';
        for (int i = 0; i < sizeText; i++)
        {
            fail << ciphertext[i];//выводит число из файла
        }
        fail.close();
    }
}


char* VigenereTable::decipherText(char* ciphertext, char* sourceText, int sizeText)
{
    for (int i = 0; i < sizeText; i++)
    {
        sourceText[i] = decipherLetter(ciphertext[i], i);
    }
    return sourceText;
}

char VigenereTable::decipherLetter(char letter, int nummberletter)
{
    int numberCount = nummberletter % sizeKey;
    if (int(letter) - numberCount < alphabetShift)
        return numberLastLetter - (numberCount - (int(letter) - alphabetShift)) + 1;
    else
        return int(letter) - numberCount;
}


char* VigenereTable::encryptText(char* sourceText, char* ciphertext, int sizeText)
{
    for (int i = 0; i < sizeText; i++)
    {
        ciphertext[i] = encryptLetter(sourceText[i], i);
    }
    return ciphertext;
}

char VigenereTable::encryptLetter(char letter, int nummberletter)
{
    int numberCount = nummberletter % sizeKey;
    if (int(letter) + numberCount > numberLastLetter)
        return ((int(letter) + numberCount) % numberLastLetter) + alphabetShift - 1;
    else
        return int(letter) + numberCount;
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
