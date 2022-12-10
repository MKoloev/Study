//1. Увеличить яркость красной составляющей верхней половины картинки.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>
#include <ctime>

using namespace std;


// здесь должен быть фрагмент кода, время выполнения которого нужно измерить

void mmx(void* p1, int s);

int prgMain();

int main(int argc)
{
	unsigned int start_time = clock();
	for (int i = 0; i < 100; i++)
	prgMain();

	unsigned int end_time = clock(); // конечное время
	unsigned int search_time = end_time - start_time; // искомое время
	cout << "Time: " << search_time;
	return 0;
}

int prgMain()
{
	FILE* in, * out;
	unsigned __int8* buffer;
	unsigned __int32 wight, height;
	fopen_s(&in, "twilight.bmp", "rb");
	if (in == NULL)
	{
		printf("Error: Can't open twilight.bmp for reading\n");
		return 0;
	}
	buffer = (unsigned __int8*)malloc(54);
	fread(buffer, 1, 54, in);
	for (int i = 0; i <= 3; i++)
	{
		wight = buffer[21 - i] | wight << 8;
		height = buffer[25 - i] | height << 8;
	}

	fopen_s(&out, "out.bmp", "wb");
	if (out == NULL)
	{
		printf("Error: Can't open file %s for writing\n", "out.bmp");
		return 0;
	}

	fwrite(buffer, 1, 54, out);
	free(buffer);
	buffer = (unsigned __int8*)malloc(wight * height * 4);
	fread(buffer, 1, wight * height * 4, in);

	mmx(buffer ,  wight * height * 4);

	fclose(in);
	fwrite(buffer, 1, wight * height * 4, out);
	fclose(out);
	free(buffer);
	return 0;
}


void mmx(void* p1, int s)
{
	unsigned _int8 mask = 0xff;
	__int32 A = 2;
	__asm
	{
		mov esi, p1
		mov ecx, s
		mov eax, s
		mov edx, 0
		div A
		sub eax, A

		mov dl, mask//
		l1 :
				cmp eax, ecx//если eax = acx
				JNE l2;
					mov[esi], dl
					sub eax, 4
				l2:
				
			add esi, 1

			sub ecx, 1
			cmp ecx, 2
			jg l1
			

	}
}


/*

void mmx(void* p1, void* p2,  int s)
{
	cout << s << endl;
	//так можно определять 64-разрядные данные
	unsigned _int8 mask = 0xff;
	int A = s / 2 + 2;
	__asm
	{
		mov esi, p1
		mov edi, p2
		mov ecx, s
		mov eax, A
		l1 :
			movq mm2, mask
			movq mm0, [esi] //;загрузить восемь байтов спрайта 
			movq mm1, [edi] //;загрузить восемь байтов фона
				cmp eax, ecx//если eax = acx
				JNE l2;
					movq mm0, mask
					sub eax, 4
				l2:
			movq mm1, mm0
			//pcmpeqb mm2, mm0 //;сделать маску байтов, которые надо вывести
			//pand mm2, mm0 //;обнулить ненужные
			//por mm1, mm0 //;сложить их с байтами спрайта
			//paddw mm1, 0
			//movq[esi], mm1 //;сохранить их обратно на изображение
			movq [edi], mm0 //;сохранить их обратно на изображение

			add esi, 1
			add edi, 1
			sub ecx, 1
			cmp ecx, 0
			jg l1
			
	}


	cout << s << endl;
}
*/
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
