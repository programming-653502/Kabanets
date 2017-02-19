// SimonKab. 1.2.14

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>
#include <string.h>

#define MAX_NUMBER_LENGTH 256
#define MAX_INPUT_NUMBER "4294967295"

int isValid(char* input) {

	for (unsigned int i=0; i < strlen(input); i++) {
		if (!isdigit( *(input+i) )) {
			return 0;
		}
	}

	if (strlen(input) > 10)
		return 0;

	if (strlen(input) == 10) {
		char* max = MAX_INPUT_NUMBER;
		for (unsigned int i = 0; i < strlen(input); i++) {
			if (*(input + i) - '0' < *(max + i) - '0') {
				return 1;
			} else {
				if (*(input + i) - '0' > *(max + i) - '0') {
					return 0;
				}
			}
		}
	}

	return 1;
}

// TODO: можно применить решито Эратосфена
int isItSimpleNumber(unsigned long number) {
	for (unsigned long i = 2; i < number; i++) {
		if (number % i == 0)
			return 0;
	}
	return 1;
}

unsigned long strToULInt(char* input) {
	unsigned long number = strtoul(input, 0, 10);
	return number;
}

int main() {
	setlocale(LC_CTYPE, "rus");

	puts("Лабароторная 1. Программирование.");
	puts("Введите число n. Прогрмма выведет совершенные числа до него.\n");

	char input[MAX_NUMBER_LENGTH];

	char exit = '\0';
	while (exit != 'q') {
		puts("\nИтак, Ваше число (не превышает 4 294 967 295): \t");
		gets_s(input, MAX_NUMBER_LENGTH);

		while (!isValid(input)) {
			puts("\nВы ввели неверные данные. Вы имеете право вводить только целые числа");
			puts("Итак, еще раз Ваше число (не превышает 4 294 967 295): \t");
			gets_s(input, MAX_NUMBER_LENGTH);
		}

		unsigned long numberInput = strToULInt(input);

		/*
		Совершенные числа можно вычеслять по формуле pow(2, x - 1)*(pow(2, x) - 1)
		где x - простое число и pow(2, x) - 1 - простое число.
		*/

		int x = 1;
		while (numberInput >= pow(2, x - 1)*(pow(2, x) - 1)) {
			if (!isItSimpleNumber(x) || !isItSimpleNumber( (unsigned long) pow(2, x) - 1)) {
				x++;
				continue;
			}
			printf("%d ", (unsigned long) pow(2, x - 1)*( (unsigned long) pow(2, x) - 1));

			x++;
		}

		puts("\n\nМожет, еще раз? (q - чтобы выйти, любой другой символ для продолжения)\t");
		exit = _getch();
	}
	
	return 0;
}