#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
using namespace std;

const int SizeArray = 1000;
const int BlockSize = 64;

char Key[] { 1, 0, 0, 0, 1, 1, 0, 1,
                   0, 1, 0, 0, 1, 1, 0, 1,
                   1, 1, 0, 0, 1, 1, 0, 0,
                   0, 0, 1, 0, 1, 1, 0, 1,
                   1, 0, 1, 0, 1, 1, 0, 0,
                   0, 1, 1, 0, 1, 1, 0, 0,
                   1, 1, 1, 0, 1, 1, 0, 1,
                   0, 0, 0, 1, 1, 1, 0, 1 };

const int IP[] {58, 50, 42, 34, 26, 18, 10, 2,  60, 52, 44, 36, 28, 20, 12, 4,
                62,	54,	46,	38,	30,	22,	14,	6,	64,	56,	48,	40,	32,	24, 16,	8,
                57,	49,	41,	33,	25,	17,	9,	1,	59,	51,	43,	35,	27,	19,	11,	3,
                61,	53,	45,	37,	29,	21,	13,	5,	63,	55,	47,	39,	31,	23,	15,	7};

const int IP_1[]{ 40, 8, 48,	16,	56,	24,	64,	32,	39,	7,	47,	15,	55,	23,	63,	31,
                  38, 6, 46,	14,	54,	22,	62,	30,	37,	5,	45,	13,	53,	21,	61,	29,
                  36, 4, 44,	12,	52,	20,	60,	28,	35,	3,	43,	11,	51,	19,	59,	27,
                  34, 2, 42,	10,	50,	18,	58,	26,	33,	1,	41,	9,	49,	17,	57,	25 };




int PC_1[] = { 57, 49, 41, 33, 25, 17, 9,
               1, 58, 50, 42, 34, 26, 18,
              10,  2, 59, 51, 43, 35, 27,
              19, 11,  3, 60, 52, 44, 36,
              63, 55, 47, 39, 31, 23, 15,
               7, 62, 54, 46, 38, 30, 22,
              14,  6, 61, 53, 45, 37, 29,
              21, 13,  5, 28, 20, 12,  4 };

int PC_2[] = { 14, 17, 11, 24,  1,  5,
               3, 28, 15,  6, 21, 10,
              23, 19, 12,  4, 26,  8,
              16,  7, 27, 20, 13,  2,
              41, 52, 31, 37, 47, 55,
              30, 40, 51, 45, 33, 48,
              44, 49, 39, 56, 34, 53,
              46, 42, 50, 36, 29, 32 };

int shiftBits[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

char subKey[16][48];


int E[] = { 32,  1,  2,  3,  4,  5,
            4,  5,  6,  7,  8,  9,
            8,  9, 10, 11, 12, 13,
           12, 13, 14, 15, 16, 17,
           16, 17, 18, 19, 20, 21,
           20, 21, 22, 23, 24, 25,
           24, 25, 26, 27, 28, 29,
           28, 29, 30, 31, 32,  1 };

int S_BOX[8][4][16] = {
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

int P[] = { 16,  7, 20, 21,
           29, 12, 28, 17,
            1, 15, 23, 26,
            5, 18, 31, 10,
            2,  8, 24, 14,
           32, 27,  3,  9,
           19, 13, 30,  6,
           22, 11,  4, 25 };


class DES
{
private:
    static char ciphertext[1000];
   // static char subKey[16][48];


    static void extract64Bit(char* textInBinarySystem, char* array64Bit, int satartIdex);//выделение в массив 64 бит
    static void return64Bit(char* textInBinarySystem, char* array64Bit, int satartIdex);

    static void initialPermutation(char* array64Bit);//первичное преобразование
    static void initialPermutation_1(char* array64Bit);

    static void feisteelEncryption();

    static void leftShift(char* k, int shift);

    static void f(char* R, char* k);

public:
    static int binarization(char* text, char* textInBinarySystem, int sizeText);
    static int conversionToChar(char* textInBinarySystem, char* text, int sizeBinarText);

    static void generatgenerateKeys(char* key);

    static void encryptionDes(char* textInBinarySystem, char* encryptedBinar, int sizeBinarText);
    static void decryptedDes(char* encryptedBinar, char* textInBinarySystem, int sizeBinarText);


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
    char textInBinarySystem[SizeArray];
    char encryptedBinar[SizeArray];

    DES::generatgenerateKeys(Key);


    //Щифрование
    int sizeText = outputFromFile(encryptFileInput, sourceText);
    int sizeBinarText = DES::binarization(sourceText, textInBinarySystem, sizeText);
    DES::encryptionDes(textInBinarySystem, encryptedBinar, sizeBinarText);
    sizeText = DES::conversionToChar(encryptedBinar, ciphertext, sizeBinarText);

    inputFromFile(encryptFileOutput, ciphertext, sizeText);



    //РАСШИФРОВКА
    char decipherFileInput[]{ "DecipherTextInput.txt" };
    char decipherFileOutput[]{ "DecipherTextOutput.txt" };

    sizeText = outputFromFile(decipherFileInput, ciphertext);
    sizeBinarText = DES::binarization(ciphertext, encryptedBinar, sizeText);

    DES::decryptedDes(encryptedBinar, textInBinarySystem, sizeBinarText);

    sizeText = DES::conversionToChar(textInBinarySystem, sourceText, sizeBinarText);
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
            fail << ciphertext[i];//вводит число в файл
        }
        fail.close();
    }
}


/// <summary>
/// преобразует текст в двоичную систуму
/// </summary>
/// <param name="text"></param>
/// <param name="textInBinarySystem"></param>
/// <param name="sizeText"></param>
/// <returns></returns>
int DES::binarization(char* text, char* textInBinarySystem, int sizeText)
{
    int sizeBinarText = sizeText * 8;
    for (int i = 0; i < sizeText; i++)
    {
        char letter = text[i];
        for (int j = 0; sizeBinarText < SizeArray && j < 8; j++)
        {
            if (letter <= 0)
                textInBinarySystem[i * 8 + j] = 0;
            else
            {
                textInBinarySystem[i * 8 + j] = letter % 2;
                letter /= 2;
            }
        }
    }

    for (;sizeBinarText % 64 != 0; sizeBinarText++)
        textInBinarySystem[sizeBinarText - 1] = 0;
    textInBinarySystem[sizeBinarText] = 0;
    return sizeBinarText;
}


/// <summary>
/// преобразует биты в текст
/// </summary>
/// <param name="textInBinarySystem"></param>
/// <param name="text"></param>
/// <param name="sizeBinarText"></param>
/// <returns></returns>
int DES::conversionToChar(char* textInBinarySystem, char* text, int sizeBinarText)
{
    int sizeText = sizeBinarText / 8;
    for (int i = 0; i < sizeText; i++)
    {
        text[i] = 0;
        for (int j = 0; sizeBinarText < SizeArray && j < 8; j++)
        {
            int y = textInBinarySystem[i * 8 + j];
            if(y == 1)
                text[i] += (int)pow(2, j);
        }
    }

    return sizeText;
}


/// <summary>
/// создает 16 ключей для шифрования
/// </summary>
/// <param name="key"></param>
void DES::generatgenerateKeys(char* key)
{
    char realKey[56];
    char left[28];
    char right[28];
    char compressKey[48];
    
    for (int i = 0; i < 56; ++i)
        realKey[55 - i] = key[64 - PC_1[i]];
    
    for (int round = 0; round < 16; ++round)
    {
        
        for (int i = 28; i < 56; ++i)
            left[i - 28] = realKey[i];
        for (int i = 0; i < 28; ++i)
            right[i] = realKey[i];
        
        leftShift(left, shiftBits[round]);
        leftShift(right, shiftBits[round]);
        
        for (int i = 28; i < 56; ++i)
            realKey[i] = left[i - 28];
        for (int i = 0; i < 28; ++i)
            realKey[i] = right[i];
        for (int i = 0; i < 48; ++i)
            compressKey[47 - i] = realKey[56 - PC_2[i]];

        for (int i = 0; i < 48; i++)
            subKey[round][i] = compressKey[i];
        //memcpy(subKey[round], compressKey, 48);
    }
}

void DES::leftShift(char* k, int shift)
{
    char tmp[28];
    memcpy(tmp, k, 28);
    for (int i = 27; i >= 0; --i)
    {
        if (i - shift < 0)
            k[i] = tmp[i - shift + 28];
        else
            k[i] = tmp[i - shift];
    }
}


void DES::f(char* R, char* k)
{
    char expandR[48];
    
    for (int i = 0; i < 48; ++i)
        expandR[47 - i] = R[32 - E[i]];
    
    for (int i = 0; i < 48; i++)
        expandR[i] = expandR[i] == k[i] ? 0 : 1;

    char output[32];
    int x = 0;
    for (int i = 0; i < 48; i = i + 6)
    {
        int row = expandR[47 - i] * 2 + expandR[47 - i - 5];
        int col = expandR[47 - i - 1] * 8 + expandR[47 - i - 2] * 4 + expandR[47 - i - 3] * 2 + expandR[47 - i - 4];
        int num = S_BOX[i / 6][row][col];
        bitset<4> binary(num);
        output[31 - x] = binary[3];
        output[31 - x - 1] = binary[2];
        output[31 - x - 2] = binary[1];
        output[31 - x - 3] = binary[0];
        x += 4;
    }
    
    char tmp[32];
    memcpy(tmp, output, 32);
    for (int i = 0; i < 32; ++i)
        output[31 - i] = tmp[32 - P[i]];
    memcpy(R, output, 32);
}


void DES::encryptionDes(char* textInBinarySystem, char* encryptedBinar, int sizeBinarText)
{
    char array64Bit[64];

    for (int i = 0; i < sizeBinarText; i += 64)
    {
        extract64Bit(textInBinarySystem, array64Bit, i);
        initialPermutation(array64Bit);

        char cipher[64];
        char left[32];
        char right[32];
        char newLeft[32];


        
        for (int i = 32; i < 64; ++i)
            left[i - 32] = array64Bit[i];
        for (int i = 0; i < 32; ++i)
            right[i] = array64Bit[i];
        
        for (int round = 0; round < 16; ++round)
        {
            for (int i = 0; i < 32; i++)
                newLeft[i] = right[i];

            f(right, subKey[round]);

            for (int i = 0; i < 32; i++)
            {
                right[i] = left[i] == right[i] ? 0 : 1;
                left[i] = newLeft[i];
            }
        }
        
        for (int i = 0; i < 32; ++i)
            cipher[i] = left[i];
        for (int i = 32; i < 64; ++i)
            cipher[i] = right[i - 32];
        
        
        for (int i = 0; i < 64; ++i)
            array64Bit[i] = cipher[i];

        initialPermutation_1(array64Bit);

        return64Bit(encryptedBinar, array64Bit, i);
    }
}

void DES::decryptedDes(char* encryptedBinar, char* textInBinarySystem, int sizeBinarText)
{
    char array64Bit[64];

    for (int i = 0; i < sizeBinarText; i += 64)
    {
        extract64Bit(textInBinarySystem, array64Bit, i);
        initialPermutation(array64Bit);

        char cipher[64];
        char left[32];
        char right[32];
        char newLeft[32];



        for (int i = 32; i < 64; ++i)
            left[i - 32] = array64Bit[i];
        for (int i = 0; i < 32; ++i)
            right[i] = array64Bit[i];

        for (int round = 0; round < 16; ++round)
        {
            for (int i = 0; i < 32; i++)
                newLeft[i] = right[i];

            f(right, subKey[15 - round]);

            for (int i = 0; i < 32; i++)
            {
                right[i] = left[i] == right[i] ? 0 : 1;
                left[i] = newLeft[i];
            }
        }

        for (int i = 0; i < 32; ++i)
            cipher[i] = left[i];
        for (int i = 32; i < 64; ++i)
            cipher[i] = right[i - 32];


        for (int i = 0; i < 64; ++i)
            array64Bit[i] = cipher[i];

        initialPermutation_1(array64Bit);

        return64Bit(encryptedBinar, array64Bit, i);
    }
}


/// <summary>
/// записывает 64 бит в array64Bit из textInBinarySystem, начиная с statrtIdex
/// </summary>
/// <param name="textInBinarySystem"></param>
/// <param name="array64Bit"></param>
/// <param name="satartIdex"></param>
void DES::extract64Bit(char* textInBinarySystem, char* array64Bit, int startIdex)
{
    for (int i = 0; i < BlockSize; i++)
        array64Bit[i] = textInBinarySystem[startIdex + i];
}

void DES::return64Bit(char* textInBinarySystem, char* array64Bit, int startIdex)
{
    for (int i = 0; i < BlockSize; i++)
        textInBinarySystem[startIdex + i] = array64Bit[i];
}


/// <summary>
/// начальное преобразование
/// </summary>
/// <param name="array64Bit"></param>
void DES::initialPermutation(char* array64Bit)
{
    char temporaryArray[BlockSize];
    memcpy(temporaryArray, array64Bit, BlockSize);
    for (int i = 0; i < BlockSize; i++)
        array64Bit[i] = temporaryArray[IP[i] - 1];
}

void DES::initialPermutation_1(char* array64Bit)
{
    char temporaryArray[BlockSize];
    memcpy(temporaryArray, array64Bit, BlockSize);
    for (int i = 0; i < BlockSize; i++)
        array64Bit[i] = temporaryArray[IP_1[i] - 1];
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
