// SimonKab. 5.1.12

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <locale.h>

#define MAX_INPUT_LENGTH 256
#define MAX_INPUT_NUMBER "4294967295"

int isValid(char* input) {
	for (unsigned int i = 0; i < strlen(input); i++) {
		if (!isdigit(*(input + i))) {
			return 0;
		}
	}

	if (strlen(input) < 3) {
		return 0;
	}

	/*if (strlen(input) == 10) {
		char* max = MAX_INPUT_NUMBER;
		for (unsigned int i = 0; i < strlen(input); i++) {
			if (*(input + i) - '0' < *(max + i) - '0') {
				return 1;
			}
			else {
				if (*(input + i) - '0' > *(max + i) - '0') {
					return 0;
				}
			}
		}
	}*/

	return 1;
}

/*Цифра в числе*/
typedef struct item {
	int digit;
	struct item *next;
	struct item *prev;
} Item;

/*Число*/
typedef struct number {
	Item *head;
	Item *tail;
	int n;
} Number;

/*Заполянем число*/
void fullNumber(Number *number, char* numberStr) {
	Item *item = (Item*)malloc(sizeof(Item));
	item->digit = numberStr[strlen(numberStr) - 1] - '0';
	number->head = number->tail = item;
	number->n = 1;
	item->prev = item->next = NULL;
	
	for (int i = strlen(numberStr) - 2; i >= 0; i--) {
		item = (Item*)malloc(sizeof(Item));
		item->digit = numberStr[i] - '0';
		
		item->next = NULL;
		item->prev = number->tail;
		number->tail->next = item;
		number->tail = item;
		number->n++;
	}

}

/*сумма двух чисел*/
Number summa(Number* first, Number* second) {
	Item *item;

	Number sum = { NULL, NULL, 0 };

	Item* iterFirst = first->head;
	Item* iterSecond = second->head;

	int f, s, ost=0;
	while (iterFirst || iterSecond) {
		item = (Item*)malloc(sizeof(Item));
		item->next = item->prev = NULL;

		if (iterFirst) 
			f = iterFirst->digit;
		else 
			f = 0;
		if (iterSecond) 
			s = iterSecond->digit; 
		else 
			s = 0;

		item->digit = (f + s + ost) % 10;
		ost = (f + s + ost) / 10;

		if (sum.head == NULL) {
			sum.tail = sum.head = item;
		} else {
			item->prev = sum.tail;
			sum.tail->next = item;
			sum.tail = item;
		}

		if (iterFirst) iterFirst = iterFirst->next;
		if (iterSecond) iterSecond = iterSecond->next;
	}
	
	if (ost != 0) {
		item = (Item*)malloc(sizeof(Item));
		item->next = item->prev = NULL;

		item->digit = ost;
		ost = 0;

		item->prev = sum.tail;
		sum.tail->next = item;
		sum.tail = item;
	}

	return sum;
}

/*Перемножаем большое число и цифру*/
Number multiplayWithOne(Number* first, int s) {
	Item *item;

	Number multiplay = { NULL, NULL, 0 };

	Item* iterFirst = first->head;

	int f, ost = 0;
	while (iterFirst) {
		item = (Item*)malloc(sizeof(Item));
		item->next = item->prev = NULL;

		if (iterFirst)
			f = iterFirst->digit;
		else
			f = 0;

		item->digit = (f * s + ost) % 10;
		ost = (f * s + ost) / 10;

		if (multiplay.head == NULL) {
			multiplay.tail = multiplay.head = item;
		} else {
			item->prev = multiplay.tail;
			multiplay.tail->next = item;
			multiplay.tail = item;
		}

		if (iterFirst) iterFirst = iterFirst->next;
	}

	if (ost != 0) {

		char ostStr[10000];
		_itoa_s(ost, ostStr, 10000, 10);
		ost = 0;

		for (int i = strlen(ostStr)-1; i >= 0; i--) {

			item = (Item*)malloc(sizeof(Item));
			item->next = item->prev = NULL;

			item->digit = ostStr[i]-'0';

			if (multiplay.head == NULL) {
				multiplay.tail = multiplay.head = item;
			}
			else {
				item->prev = multiplay.tail;
				multiplay.tail->next = item;
				multiplay.tail = item;
			}
		}
	}

	return multiplay;
}

/*Перемножаем два числа. Сначала мы перемножаем число и цифру и складываем это в стек (массив)
Потом ссумируем вме что в стеке*/
Number multiplay(Number *first, Number *second) {

	Number *multiAr = (Number*)malloc(sizeof(Number)*second->n); // стек
	int multiArI = 0;

	Item* iterSecond = second->head;

	int s, ost = 0;
	while (iterSecond) {
		if (iterSecond)
			s = iterSecond->digit;
		else
			s = 0;

		Number m = multiplayWithOne(first, s);
		multiAr[multiArI++] = m;

		if (iterSecond) iterSecond = iterSecond->next;
	}

	/*Добавляем нули в конец чисел*/
	Item *item;
	for (int i = 0; i < second->n; i++) {
		Number* number = &multiAr[i];
		for (int j = 0; j < i; j++) {
			item = (Item*)malloc(sizeof(Item));
			item->digit = 0;
			item->next = item->prev = NULL;
			
			number->head->prev = item;
			item->next = number->head;
			number->head = item;
		}
	}

	Number sumAll = multiAr[0];
	for (int i = 1; i < second->n; i++) {
		sumAll = summa(&sumAll, &multiAr[i]);
	}

	return sumAll;
}


int main(void) {
	setlocale(LC_CTYPE, "rus");

	puts("Лабароторная 5.1 Программирование");
	puts("Факториал большого числа");

	char input[MAX_INPUT_LENGTH];
	puts("Переменная n (целое число >= 100): \t");
	gets_s(input, MAX_INPUT_LENGTH);

	while (!isValid(input)) {
		puts("\nВы ввели неверные данные. Вы имеете право вводить только целые числа");
		puts("Итак, еще раз переменная n: \t");
		gets_s(input, MAX_INPUT_LENGTH);
	}
	

	unsigned long n = strtoul(input, 0, 10);

	Number number1 = { NULL, NULL, 0 };
	char buf[MAX_INPUT_LENGTH];
	_ultoa_s(1, buf, MAX_INPUT_LENGTH, 10); /* переводим число в строку потому что так удобней доставать цифры*/
	
	fullNumber(&number1, buf);

	for (unsigned long i = 2; i <= n; i++) {
		Number number2 = { NULL, NULL, 0 };
		char buf[MAX_INPUT_LENGTH];
		_ultoa_s(i, buf, MAX_INPUT_LENGTH, 10); /* переводим число в строку потому что так удобней доставать цифры*/
		
		fullNumber(&number2, buf);
		
		number1 = multiplay(&number1, &number2);
	}

	Item* item = number1.tail;
	while (item) {
		printf("%d", item->digit);
		item = item->prev;
	}

	_getch();
	return 0;
}