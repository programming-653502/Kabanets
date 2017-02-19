// SimonKab. 2.1.14

#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define _USE_MATH_DEFINES
#include <math.h>


#define MAX_INPUT_LENGTH 256
#define MAX_INPUT_NUMBER "4294967295"

#define COMMAND_NEW_RADIUS '1'
#define COMMAND_SURFACE_AREA '2'
#define COMMAND_SIZE '3'
#define COMMAND_LENGTH_OF_EDGE '4'
#define COMMAND_SECTION_AREA '5'
#define COMMAND_VERSION '6'
#define COMMAND_EXIT '7'

/*
TODO: инкапсулировать вывод сообщений (хотя бы ошибки)
*/

int isValid(char* input) {
	for (unsigned int i = 0; i < strlen(input); i++) {
		if (!isdigit(*(input + i))) {
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

double getSurfaceArea(unsigned long radius) {
	return 4. * M_PI * pow(radius, 2);
}

double getSize(unsigned long radius) {
	return 4. / 3. * M_PI * pow(radius, 3);
}

double getLengthOfEdge(unsigned long radius) {
	return 4. * radius / pow(6, 1./6.);
}

double getSectionArea(unsigned long radius, unsigned long distance) {
	return (pow(radius, 2) - pow(distance, 2)) * M_PI;
}

void outputAuthorAndVersion() {
	puts("\nПрограмма для расчета данных шара. Версия 1.0. SimonKab©.");
	puts("All rights did not reserve");
}

unsigned long strToULInt(char* input) {
	unsigned long number = strtoul(input, 0, 10);
	return number;
}

/*
Метод инкапсулирует введнеие информации для пункта 5 (расстояние от центра шара).
*/
unsigned long getAdditionInformation(unsigned long radius) {
	unsigned long distance = 0;
	char addInput[MAX_INPUT_LENGTH];

	puts("Введите расстояние от центра шара:");
	gets_s(addInput, MAX_INPUT_LENGTH);

	while (!isValid(addInput)) {
		puts("\nВы ввели неверные данные. Вы имеете право вводить только целые числа\n");
		puts("Итак, расстояние от центра шара (не превышает 4 294 967 295): \t");
		gets_s(addInput, MAX_INPUT_LENGTH);
	}

	distance = strToULInt(addInput);


	while (distance > radius) {
		puts("\nНельзя посчитать площадь сечения, выходящего за пределы шара.");
		printf("Вы ввели %d раидус и %d расстояние\n", radius, distance);
		puts("Итак, расстояние от центра шара (не превышает 4 294 967 295): \t");
		gets_s(addInput, MAX_INPUT_LENGTH);
	}


	return distance;
}

unsigned long inputNewRadius() {
	char input[MAX_INPUT_LENGTH];
	puts("Итак, радиус шара (целое число, не превышает 4 294 967 295): \t");
	gets_s(input, MAX_INPUT_LENGTH);

	while (!isValid(input)) {
		puts("\nВы ввели неверные данные. Вы имеете право вводить только целые числа");
		puts("Итак, еще раз радиус шара (не превышает 4 294 967 295): \t");
		gets_s(input, MAX_INPUT_LENGTH);
	}

	unsigned long radius = strToULInt(input);
	return radius;
}

int main(void) {
	setlocale(LC_CTYPE, "rus");

	puts("Лабароторная 2.1 Программирование\n");
	puts("Программа позовляет узнавать данные о шаре, исходя из введенного радиуса\n\n");

	unsigned long radius = inputNewRadius();

	puts("\n\nВведите одну из указанных команд (вводите соответствующую цифру):");
	puts("(1) Ввести новый радиус:");
	puts("(2) Вывод площади поверхности шара:");
	puts("(3) Вывод объема шара:");
	puts("(4) Вывод длины ребра вписанного правильного тетраэдра:");
	puts("(5) Вывод площади сечения, проведенного на расстоянии k от центра шара:");
	puts("(6) Информация о версии и авторе программы:");
	puts("(7) Выход из программы:");

	int exit = 0;
	while (!exit) {

		int isRight = 0;
		while (!isRight) {
			
			puts("Ожидание ввода команды...");
			char query = _getch();
			
			unsigned long distance = 0;
			switch (query) {
			case COMMAND_NEW_RADIUS:
				radius = inputNewRadius();
				isRight = 1;
				break;
			case COMMAND_SURFACE_AREA:
				printf("\nПлощади поверхности шара:  %f\n", getSurfaceArea(radius));
				isRight = 1;
				break;
			case COMMAND_SIZE:
				printf("\nОбъема шара:  %f\n", getSize(radius));
				isRight = 1;
				break;
			case COMMAND_LENGTH_OF_EDGE:
				printf("\nДлина ребра вписанного правильного тетраэдра:  %f\n", getLengthOfEdge(radius));
				isRight = 1;
				break;
			case COMMAND_SECTION_AREA:
				distance = getAdditionInformation(radius);
				printf("\nПлощади сечения, проведенного на расстоянии %d от центра шара:  %f\n", distance, getSectionArea(radius, distance));
				isRight = 1;
				break;
			case COMMAND_VERSION:
				outputAuthorAndVersion();
				isRight = 1;
				break;
			case COMMAND_EXIT:
				exit = 1;
				isRight = 1;
				break;
			default:
				puts("Похоже Вы ввели неправильную команду. Номер команды указал в скобках\n");
			}
		}

	}


	return 0;
}
