#include "mainmenu.h"

#include "database.h"

#include <locale>

int main() {
	setlocale(LC_CTYPE, "rus");

	ui::MainMenu* mainView = new ui::MainMenu();

	mainView->getManager()->start();

	return 0;
}