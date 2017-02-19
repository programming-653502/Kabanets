// SimonKab. 5.2.12

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>

#define ACTION_INSERT 'A'
#define ACTION_DELETE 'D'

/*Узел дерева*/
typedef struct item
{
	int I;
	int D;
	struct item* left;
	struct item* right;
} Item;

/*Запрос на совершение каких-то действий с деревом*/
typedef struct query
{
	int D;
	int I;
	char act;
	struct query* next;
} Query;

/*Пул запросов*/
struct queryPool 
{
	Query* head;
	Query* last;
} Pool;

Item* tree; // корень дерева

int globalIndex = 1; 

int addNexItem(Item* root, int d) {
	if (root->D == -1) {
		root->D = d;
		root->I = globalIndex++;
		return 1;
	}
	if (d < root->D) {
		if (root->left) {
			addNexItem(root->left, d);
		} else {
			Item* item = (Item*)malloc(sizeof(Item));
			item->I = globalIndex++;
			item->D = d;
			item->right = item->left = NULL;
			root->left = item;
			return 1;
		}
	}
	if (d > root->D) {
		if (root->right) {
			addNexItem(root->right, d);
		} else {
			Item* item = (Item*)malloc(sizeof(Item));
			item->I = globalIndex++;
			item->D = d;
			item->right = item->left = NULL;
			root->right = item;
			return 1;
		}
	}

	return 0;
}

int deleteItem(Item* root, int data) {
	if (root->D == data) {
		if (!root->left && !root->right) {
			free(root);
			root->left = root->right = NULL;
			return 1;
		} else {
			if (!root->left || !root->right) {
				if (!root->left) {
					deleteItem(root->left, root->left->D);
				}
				if (!root->right) {
					deleteItem(root->right, root->right->D);
				}
				return 1;
			} else {
				Item* item = root->right;
				while (item->left) item = item->left;
				root->D = item->D;
				root->I = item->I;

				deleteItem(item, item->D);

				return 1;
			}
		}
	}

	if (root->left) {
		if (data < root->D) {
			return deleteItem(root->left, data);
		}
	}
	if (root->right) {
		if (data > root->D) {
			return deleteItem(root->right, data);
		}
	}

	return 0;
}

/*Находим поддерево и возвращаем его корень*/
Item* findSubTree(Item* item, int index) {

	if (item->I == index) {
		return item;
	}

	Item* resultL = NULL;
	if (item->left) {
		resultL = findSubTree(item->left, index);
	}
	Item* resultR = NULL;
	if (item->right) {
		resultR = findSubTree(item->right, index);
	}

	if (resultL)
		return resultL;
	else
		return resultR;
}

/*Выводим на экран дерево*/
void output(Item* item) {

	if (item->D < 0) { 
		printf("Дерево пустое\n");
	} else {
		printf("Элемент с номером %d и данными %d;\n", item->I, item->D);

		if (item->left) {
			if (item->left->D >= 0) // TODO: нормальная проверка на пустоту
				output(item->left);
		}
		if (item->right) {
			if (item->right->D >= 0) // TODO: нормальная проверка на пустоту
				output(item->right);
		}
	}

}

void main(void) {
	setlocale(LC_CTYPE, "rus");

	puts("Лабароторная 5.2 Программирование");
	puts("Работа с бинарным деревом поиска\n");

	tree = (Item*)malloc(sizeof(Item));
	tree->left = tree->right = NULL;
	tree->D = -1;

	Pool.head = Pool.last = NULL;

	puts("Введите следующие элементы дерева (ключи узлов пронумерованы от 1 до n):");
	puts("Ввод будет продолжаться пока Вы не введете -1\n");

	int countEl = 0;
	do {
		int data;
		printf("данные - ");
		scanf_s("%d", &data);
		
		if (data == -1) {
			break;
		}

		addNexItem(tree, data);
		countEl++;
	} while (1);

	puts("\n\n\n");
	output(tree);
	puts("\n\n\n");

	char stop = ' ';
	do {
		Query* query = (Query*)malloc(sizeof(Query));
		query->next = NULL;

		puts("Введите следующий запрос:");
		printf("индекс дерева (число от 1 до %d) - ", countEl);
		scanf_s("%d", &(query->I));

		printf("данные - ");
		scanf_s("%d", &(query->D));

		printf("действие (A - добавить, D - удалить) - ");
		char action;
		scanf_s("%c", &action, 1);
		scanf_s("%c", &action, 1);
		if (action == 'A' || action == 'D') {
			query->act = action;
		}
		else {
			puts("Ошибка заполнения данных\n");
			continue;
		}

		Query* h = Pool.head;
		Query* l = Pool.last;
		if (h == NULL && l == NULL) {
			Pool.head = Pool.last = query;
		} else {
			l->next = query;
			Pool.last = query;
		}

		puts("Еще будем добавлять запросы? (s (stop) чтобы остановить. Любой символ чтобы продолжить)");
		stop = _getch();
	} while (stop != 's');

	Query* query = Pool.head;
	int success = 1;
	do {
		
		Item* subTree = findSubTree(tree, query->I);
		if (subTree != NULL) {
			if (query->act == ACTION_INSERT) {
				int r = addNexItem(subTree, query->D);
				if (!r) {
					printf("Ошибка. Не удалось вставить %d\n", query->D);
					success = 0;
				}
			}
			if (query->act == ACTION_DELETE) {
				int r = deleteItem(subTree, query->D);
				
				if (!r) {
					printf("Ошибка. Не удалось удалить элемент %d\n", query->I);
					success = 0;
				}
			}
		} else {
			printf("Ошибка. Не удалось найти данное дерево %d\n", query->I);
			success = 0;
		}
		query = query->next;
	} while (query);

	if (success) {
		puts("\n\nОперации выполнены успешно");
	} else {
		puts("\n\nОперации не были выполнены полностью");
	}

	puts("\n\n\n");
	output(tree);
	puts("\n\n\n");

	_getch();
}