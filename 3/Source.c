// SimonKab. 3.2.13

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

int** matrix; // наш массив

void fullMatrix(int n, int m) {
	puts("Заполните массив. Цифры вводите через пробел. Следующая строка массива - Enter\n");
	matrix = (int**)malloc(sizeof(int)*n*m);
	int* matrixStr;
	for (int i = 0; i < n; i++) {
		matrixStr = (int*) malloc(sizeof(int)*m);
		
		printf("\nВведите %d строку:\n", i+1);
		int j = 0;
		while (j < m) {
			char symbol = _getche();
			if (symbol - '0' >= 0 && symbol - '0' <= 9) {
				matrixStr[j] = symbol - '0';
				j++;
			}
		}

		matrix[i] = matrixStr;
	}
}

// QuickSort
void sort(int* mass, int count) {
	int i = 0, j = count - 1;

	int p = mass[count / 2];

	int temp;
	do {
		while (mass[i] < p) i++;
		while (mass[j] > p) j--;

		if (i <= j) {
			temp = mass[i]; mass[i] = mass[j]; mass[j] = temp;
			i++; j--;
		}
	} while (i <= j);

	if (j > 0) sort(mass, j);
	if (i < count) sort(mass+i, count - i);
}

void sortDiagonals(int n, int m) {
	int i = n-1, j = 0; // нижний левый угол
	int di = 0, dj = 0;
	int* diagonal;
	while (i != 0 || j != m-1) { // вверхний правый угол
		diagonal = (int*)malloc(sizeof(int)*min(n,m));
		int diagonalIter = 0;

		di = i; dj = j; // выбираем диагональ
		while (di != n && dj != m) {

			diagonal[diagonalIter++] = matrix[di][dj];

			di++; dj++; // идем по диагонали
		}

		sort(diagonal, diagonalIter); // соритруем
		
		diagonalIter = 0;
		di = i; dj = j; // вставляем диагональ обратно
		while (di != n && dj != m) {

			matrix[di][dj] = diagonal[diagonalIter++];

			di++; dj++; // идем по диагонали
		}

		free(diagonal);

		// здесь изменяем точку старта. Идем по левой кромке, потом по верхней.
		if (i == 0) {
			j++;
		} else {
			i--;
		}
	}
}

void main(void) {
	setlocale(LC_CTYPE, "rus");

	puts("Лабароторная 4.2 Программирование");
	puts("Работа с упорядочиванием массива\n");

	long n, m;
	puts("Введите размерность массива в формате mXn или m, n или m n");
	scanf_s("%d%*c%d", &n, &m);

	fullMatrix(n, m);

	sortDiagonals(n, m);

	puts("\n\nРезультат:\n");

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", matrix[i][j]);
		}
		puts("");
	}

	for (int i = 0; i < n; i++) {
		free(matrix[i]);
	}
	free(matrix);

	_getch();
}