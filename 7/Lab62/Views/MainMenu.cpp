#include "mainmenu.h"
#include "menuview.h"
#include "consolehelper.h"

#include "nbshow.h"
#include "dbmenu.h"

using namespace ui;

MainMenu::MainMenu() {
	
}

vector<View*> MainMenu::onCreateView() {
	vector<View*> views;

	MenuItem addEntire(MAIN_MENU_DB_OPEN, MAIN_MENU_DB_OPEN_INDEX);
	MenuItem showEntires(MAIN_MENU_NOTEBOOK_OPEN, MAIN_MENU_NOTEBOOK_OPEN_INDEX);
	MenuItem exit(MAIN_MENU_EXIT, MAIN_MENU_NOTEBOOK_OPEN_INDEX);

	MenuView* menu = new MenuView();
	menu->addItem(addEntire)->addItem(showEntires)->addItem(exit);
	menu->setOnItemSelectedCallback( std::bind(&MainMenu::onMainMenuItemSelected, this, std::placeholders::_1) );

	views.push_back(menu);

	return views;
}

ViewSize MainMenu::onResizeView(ViewSize size) {
	return ViewManager::UNSPECIFIED;
}

void MainMenu::onAttachView() {
	util::ConsoleHelper::WriteNameOfView(MAIN_MENU_NAME);
}

void MainMenu::onDestroyView() {
}

void MainMenu::onMainMenuItemSelected(long item) {

	DatabaseMenu* dbMenu;
	NotebookShow* notebookShow;
	switch (item) {
	case MAIN_MENU_DB_OPEN_INDEX:

		dbMenu = new DatabaseMenu();
		dbMenu->getManager()->start();

		break;
	case MAIN_MENU_NOTEBOOK_OPEN_INDEX:

		notebookShow = new NotebookShow();
		notebookShow->getManager()->start();

		break;
	case MAIN_MENU_EXIT_INDEX:

		getManager()->destroy();

		break;
	}

}