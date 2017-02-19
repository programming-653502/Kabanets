// SimonKab. 3.2.13

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

int** matrix; // ��� ������

void fullMatrix(int n, int m) {
	puts("��������� ������. ����� ������� ����� ������. ��������� ������ ������� - Enter\n");
	matrix = (int**)malloc(sizeof(int)*n*m);
	int* matrixStr;
	for (int i = 0; i < n; i++) {
		matrixStr = (int*) malloc(sizeof(int)*m);
		
		printf("\n������� %d ������:\n", i+1);
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
	int i = n-1, j = 0; // ������ ����� ����
	int di = 0, dj = 0;
	int* diagonal;
	while (i != 0 || j != m-1) { // �������� ������ ����
		diagonal = (int*)malloc(sizeof(int)*min(n,m));
		int diagonalIter = 0;

		di = i; dj = j; // �������� ���������
		while (di != n && dj != m) {

			diagonal[diagonalIter++] = matrix[di][dj];

			di++; dj++; // ���� �� ���������
		}

		sort(diagonal, diagonalIter); // ���������
		
		diagonalIter = 0;
		di = i; dj = j; // ��������� ��������� �������
		while (di != n && dj != m) {

			matrix[di][dj] = diagonal[diagonalIter++];

			di++; dj++; // ���� �� ���������
		}

		free(diagonal);

		// ����� �������� ����� ������. ���� �� ����� ������, ����� �� �������.
		if (i == 0) {
			j++;
		} else {
			i--;
		}
	}
}

void main(void) {
	setlocale(LC_CTYPE, "rus");

	puts("������������ 4.2 ����������������");
	puts("������ � ��������������� �������\n");

	long n, m;
	puts("������� ����������� ������� � ������� mXn ��� m, n ��� m n");
	scanf_s("%d%*c%d", &n, &m);

	fullMatrix(n, m);

	sortDiagonals(n, m);

	puts("\n\n���������:\n");

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