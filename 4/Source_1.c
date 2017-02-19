// SimonKab. 4.1.13

#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define P_I 'i'
#define P_R 'r'
#define P_D 'd'
#define P_V 'v'
#define P_T 't'
#define P_P 'p'

/* база для заполнения слов. Здесь в основном корни слов*/
char base[][10] = { "од","дв","тр","четыр", "пят", "шест", "сем", "вос","девят" ,"десят" ,"надцат" ,"дцат" 
,"десят" ,"девяносто","сто" ,"сти" ,"тысяча" };

/* подбазы. Т.е. слова которые употребляются в составе с другими (шестнадцать, пятьсот)*/
char subBase10[][10] = {"один","две","три", "четыр", "пят", "шест", "сем", "восем", "девят"};
char subBase20[][10] = { "два","три"};
char subBase100[][10] = { "сот","сот","стам","сот","стами","стах"};

/* некоторые числа не поддаются стандартному склонению. Поэтому пишем их жестко.*/
char eightT[6][10] = { "восемь","восьми", "восьми", "восемь", "восьмью", "восьми" };
char fourtyT[6][10] = { "сорок","сорока", "сорокам", "сорок", "сороками", "сорока" };
char oneH[6][15] = { "сто","ста","стам", "сто", "сто", "ста" };
char twoH[6][15] = {"двести","двухсот","двумстам", "двести", "двумястами", "двухстах"};
char threeH[6][15] = { "триста","трехсот","трехстам", "триста", "тремястами", "трехсот"};
char fourH[6][15] = { "четыреста","четырехсот","четыремстам", "четыреста", "четырехстами", "четырехсот" };
char thousand[6][15] = { "тысяча","тысячи", "тысяче", "тысячу", "тысячей", "тысяче" };

/* 1 2 3 4 не поддаются нормальному склонению. Пишем их сразу.*/
char ex[1000][50] = {"один","одного","одному" ,"одного" ,"одним" ,"одном" 
					,"два" ,"двух" ,"двум" ,"двух" ,"двумя" ,"двух",
					"три" ,"трех" ,"трем" ,"трех" ,"тремя" ,"трех",
					"четыре" ,"четырех" ,"четырем" ,"четырех" ,"четыремя" ,"четырех"};

/* объединяем строку str1 и str2 без изменения строки str1.
 результат сохраняем в temp*/
void copy(char* str1, char* str2, char* temp) {
	strcpy(temp, str1);
	strcat(temp, str2);
}

/*Суть метода такова. Сразу заполняем массив всеми спряжениями всех составных слов.
Таким образов чтобы построить искомое число словми в нужном падеже можно просто выбрать
соответствующие слова из массива. Жертвую памятью в пользу скорости*/

void fullEx() {
	int exI = 24;
	char* l = ex[5];
	char* temp = (char*) malloc(25);

	/*5-7*/
	for (int i = 4; i < 7; i++) {
		copy(base[i], "ь", temp);
		strcpy(ex[exI++], temp);
		copy(base[i], "и", temp);
		strcpy(ex[exI++], temp);
		copy(base[i], "и", temp);
		strcpy(ex[exI++], temp);
		copy(base[i], "ь", temp);
		strcpy(ex[exI++], temp);
		copy(base[i], "ью", temp);
		strcpy(ex[exI++], temp);
		copy(base[i], "и", temp);
		strcpy(ex[exI++], temp);
	}

	/*8*/
	for (int i = 0; i < 6; i++) {
		strcpy(ex[exI++], eightT[i]);
	}

	/*9-10*/
	for (int i = 8; i < 10; i++) {
		copy(base[i], "ь", temp);
		strcpy(ex[exI++], temp);
		copy(base[i], "и", temp);
		strcpy(ex[exI++], temp);
		copy(base[i], "и", temp);
		strcpy(ex[exI++], temp);
		copy(base[i], "ь", temp);
		strcpy(ex[exI++], temp);
		copy(base[i], "ью", temp);
		strcpy(ex[exI++], temp);
		copy(base[i], "и", temp);
		strcpy(ex[exI++], temp);
	}

	/*11-19*/
	char* _temp = (char*)malloc(25);
	for (int i = 0; i < 9; i++) {
		copy(subBase10[i], base[10], temp);
		
		copy(temp, "ь", _temp);
		strcpy(ex[exI++], _temp);
		copy(temp, "и", _temp);
		strcpy(ex[exI++], _temp);
		copy(temp, "и", _temp);
		strcpy(ex[exI++], _temp);
		copy(temp, "ь", _temp);
		strcpy(ex[exI++], _temp);
		copy(temp, "ью", _temp);
		strcpy(ex[exI++], _temp);
		copy(temp, "и", _temp);
		strcpy(ex[exI++], _temp);
	}

	/*20-30*/
	for (int i = 0; i < 2; i++) {
		copy(subBase20[i], base[11], temp);

		copy(temp, "ь", _temp);
		strcpy(ex[exI++], _temp);
		copy(temp, "и", _temp);
		strcpy(ex[exI++], _temp);
		copy(temp, "и", _temp);
		strcpy(ex[exI++], _temp);
		copy(temp, "ь", _temp);
		strcpy(ex[exI++], _temp);
		copy(temp, "ью", _temp);
		strcpy(ex[exI++], _temp);
		copy(temp, "и", _temp);
		strcpy(ex[exI++], _temp);
	}

	free(_temp);

	/*40*/
	for (int i = 0; i < 6; i++) {
		strcpy(ex[exI++], fourtyT[i]);
	}

	/*50-80*/
	for (int i = 24; i < 48;) {
		for (int j = 54; j < 60; j++) {
			
			if (j == 54) {
				copy(ex[i++], base[9], temp);
			} else
				copy(ex[i++], ex[j], temp);

			strcpy(ex[exI++], temp);
		}
	}

	/*90*/
	for (int i = 0; i < 6; i++) {
		strcpy(ex[exI++], base[13]);
	}

	/*100*/
	for (int i = 0; i < 6; i++) {
		strcpy(ex[exI++], oneH[i]);
	}

	/*200*/
	for (int i = 0; i < 6; i++) {
		strcpy(ex[exI++], twoH[i]);
	}

	/*300*/
	for (int i = 0; i < 6; i++) {
		strcpy(ex[exI++], threeH[i]);
	}

	/*400*/
	for (int i = 0; i < 6; i++) {
		strcpy(ex[exI++], fourH[i]);
	}

	/*500-900*/
	for (int i = 24; i < 54;) {
		for (int j = 0; j < 6; j++) {
			copy(ex[i++], subBase100[j], temp);
			strcpy(ex[exI++], temp);
		}
	}

	/*1000*/
	for (int i = 0; i < 6; i++) {
		strcpy(ex[exI++], thousand[i]);
	}

	free(temp);
}


/*Слова в массиве идут друг за другом. Чтобы переходить с одной цифры на другую
нужно добавлять к предыдущей 6 пропуская лишние падежи*/

char* getStrForInt(int number, int shift) {
	if (number >= 1 && number <= 20) {
		return ex[(number - 1) * 6 + shift];
	}
	switch (number) {
	case 30:
		return ex[20 * 6 + shift];
	case 40:
		return ex[21 * 6 + shift];
	case 50:
		return ex[22 * 6 + shift];
	case 60:
		return ex[23 * 6 + shift];
	case 70:
		return ex[24 * 6 + shift];
	case 80:
		return ex[25 * 6 + shift];
	case 90:
		return ex[26 * 6 + shift];
	case 100:
		return ex[27 * 6 + shift];
	case 200:
		return ex[28 * 6 + shift];
	case 300:
		return ex[29 * 6 + shift];
	case 400:
		return ex[30 * 6 + shift];
	case 500:
		return ex[31 * 6 + shift];
	case 600:
		return ex[32 * 6 + shift];
	case 700:
		return ex[33 * 6 + shift];
	case 800:
		return ex[34 * 6 + shift];
	case 900:
		return ex[35 * 6 + shift];
	case 1000:
		return ex[36 * 6 + shift];
	}

	return "";
}

void main(void) {
	setlocale(LC_CTYPE, "rus");

	puts("Лабароторная 4.1 Программирование");
	puts("Перевод числа в текст в определенном падеже");

	fullEx();

	char exit;
	do {

		puts("Натуральное число n ( <= 1000)");

		int number = -1;
		scanf_s("%d", &number);

		while (number > 1000 || number < 0) {
			puts("Ошибка. Число должно быть в диапазон [0...1000]");
			scanf_s("%d", &number);
		}


		puts("Введите падеж. Один из следующих символов:");
		puts("Именительный - i");
		puts("Родительный - r");
		puts("Дательный - d");
		puts("Винительный - v");
		puts("Творительный - t");
		puts("Предложный - p");
		char p = _getch();

		int shift = 0;
		switch (p) {
		case P_I:
			shift = 0;
			break;
		case P_R:
			shift = 1;
			break;
		case P_D:
			shift = 2;
			break;
		case P_V:
			shift = 3;
			break;
		case P_T:
			shift = 4;
			break;
		case P_P:
			shift = 5;
			break;
		}

		long del = 10;
		while (number % del != number) del *= 10;

		do {
			int n = (number % del) / (del / 10) * (del / 10); /* n - одна цифра в числе number */

			if (n == 10) {
				n += number % 10;
				del /= 10;
			}

			if (n != 0)
				printf("%s ", getStrForInt(n, shift));

			del /= 10;
		} while (del != 1);

		puts("\nЕще разок? (q - выйти, любая клавиша - продолжить)\n");
		exit = _getch();
	} while (exit != 'q');

}
