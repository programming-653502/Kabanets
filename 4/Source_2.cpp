// SimonKab. 4.2.13

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <locale.h>

#define MAX_INPUT_LENGTH 256

unsigned long from8to10(char* numberStr) {
	int power = 0;
	unsigned long result = 0;
	for (int i = strlen(numberStr)-1; i >= 0; i--) {
		
		int symbol = numberStr[i] - '0';
		result += symbol * (long) pow(8, power);

		power++;
	}

	return result;
}

int main(void) {
	setlocale(LC_CTYPE, "rus");

	puts("Лабароторная 4.2 Программирование");
	puts("Чтение файлов. Замена в файле восьмеричный чисел на десятичные\n");

	FILE *fi;
	FILE *ft;

	char input[MAX_INPUT_LENGTH];

	puts("Введите имя файла полностью (включая .txt):");
	gets_s(input, MAX_INPUT_LENGTH);

	fi = fopen(input, "r+");
	
	while (fi == NULL) {
		puts("Ошибка чтения файла. Убедитесь, что такой файл существует");
		puts("Введите имя txt файла полностью (в формате .txt):");
		
		gets_s(input, MAX_INPUT_LENGTH);
		fi = fopen(input, "r");
	}

	ft = fopen("temp", "w");

	char symbol;
	char numberStr[MAX_INPUT_LENGTH];
	int numberStrI = 0;
	while ((symbol = fgetc(fi)) != -1) {
		
		if (0 <= symbol - '0' && symbol - '0' <= 7) {
			
			while (0 <= symbol - '0' && symbol - '0' <= 7) {
				numberStr[numberStrI++] = symbol;
				symbol = fgetc(fi);
			}

			numberStr[numberStrI] = '\0';

			unsigned long number10 = from8to10(numberStr);

			char p[34];
			char* number10Str = _ultoa(number10, p, 10);
			while (*number10Str) {
				fputc(*number10Str, ft);
				number10Str++;
			}

			if (symbol != -1)
				fputc(symbol, ft);

			numberStrI = 0;
		} else {
			fputc(symbol, ft);
		}
	}

	fclose(fi);
	fclose(ft);

	remove(input);
	rename("temp", input);

	puts("Работа с файлом завершена");
	_getch();
	return 0;
}