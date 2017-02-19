// SimonKab. 2.2.6

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

int isValid(char* input) {
	for (unsigned int i = 0; i < strlen(input); i++) {
		if (!isdigit(*(input + i))) {
			if (*(input + i) != '.')
				return 0;
		}
	}

	/*if (strlen(input) > 10)
		return 0;

	if (strlen(input) == 10) {
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

double calculate(unsigned long x, unsigned long n) {
	double result = 1;
	for (unsigned long i = 1; i <= 2 * n - 1; i++) {
		result *= ((double)x / (double)i);
	}
	return result;
}

/*����� �����������*/
double iterResult(unsigned long x, unsigned long n) {
	double result = 0;
	for (unsigned long i = 1; i <= n; i++) {
		result += pow(-1, i - 1)*calculate(x, i);
	}

	return result;
}

double recursResult(long double *res, unsigned long *i, unsigned long *x, unsigned long *n) {
	
	if (*i == *n) {
		return *res + pow(-1, *i - 1)*calculate(*x, *i);
	}

	*res += pow(-1, *i - 1)*calculate(*x, *i);

	(*i)++;

	return recursResult(res, i, x, n);
}

int strToULInt(char* input) {
	return strtoul(input, 0, 10);
}

int main(void) {
	setlocale(LC_CTYPE, "rus");

	puts("������������ 2.2 ����������������\n");
	puts("���������� �� ������� �������-���������\n\n");

	char input[MAX_INPUT_LENGTH];
	puts("���������� x (����� �����): \t");
	gets_s(input, MAX_INPUT_LENGTH);

	while (!isValid(input)) {
		puts("\n�� ����� �������� ������. �� ������ ����� ������� ������ ����� �����");
		puts("����, ��� ��� ���������� x: \t");
		gets_s(input, MAX_INPUT_LENGTH);
	}

	unsigned long x = strToULInt(input); // ���������� � �������

	double e = -1; // ��������

	puts("�������� �������� e (����� ������� �����): \t");
	scanf_s("%lf", &e);

	if (e <= 0) {
		// TODO: ����� �� ������ ����� ��������?
		puts("������. �������� ����� ���� ������ ������������� ������� ������");
		_getch();
		return 0;
	}

	//TODO: ��������

	double simpleResult = sin(x);
	unsigned long n = 1;
	double iterationResult = iterResult(x, n);
	
	long double res = 0;
	int i = 1;
	double recursiveResult = recursResult(&res, &i, &x, &n);
	
	do {
		iterationResult = iterResult(x, ++n);
		// TODO: ����� �� ������ ����� ��������?
		if (n > 1000) {
			puts("�������� �������� �� ���� ����������. ��� �������� x �� ��������");
			_getch();
			return 0;
		}
		printf("%f\n", iterationResult);

	} while (fabs (simpleResult - iterationResult) > e);
	
	printf("������� ������ %f. ��� ������ ������������ ������� %f. �������� �������� ���������� ��� %d", simpleResult, iterationResult, n);

	_getch();
	return 0;
}
