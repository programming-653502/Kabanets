#include "dbmenu.h"

#include "addtownview.h"
#include "showtownsview.h"
#include "towninfoview.h"

#include "consolehelper.h"

using namespace ui;

DatabaseMenu::DatabaseMenu() {
}

vector<View*> DatabaseMenu::onCreateView() {
	vector<View*> views;

	MenuItem addTown(DATABASE_MENU_ADD_TOWN, DATABASE_MENU_ADD_TOWN_INDEX);
	MenuItem showTowns(DATABASE_MENU_SHOW_TOWNS, DATABASE_MENU_SHOW_TOWNS_INDEX);
	MenuItem findTown(DATABASE_MENU_FIND_TOWN, DATABASE_MENU_FIND_TOWN_INDEX);
	MenuItem exit(DATABASE_MENU_EXIT, DATABASE_MENU_EXIT_INDEX);

	MenuView* menu = new MenuView();
	menu->addItem(addTown)->addItem(showTowns)->addItem(findTown)->addItem(exit);
	menu->setOnItemSelectedCallback(std::bind(&DatabaseMenu::onMainMenuItemSelected, this, std::placeholders::_1));

	views.push_back(menu);

	return views;
}

ViewSize DatabaseMenu::onResizeView(ViewSize) {
	return ViewManager::UNSPECIFIED;
}

void DatabaseMenu::onAttachView() {
	util::ConsoleHelper::WriteNameOfView(DATABASE_MENU_NAME);
}

void DatabaseMenu::onDestroyView() {
}

void DatabaseMenu::onMainMenuItemSelected(long item) {

	AddTownView* addTownView;
	ShowTownsView* showTownsView;
	TownInfoView* townInfoView;
	switch (item) {
	case DATABASE_MENU_ADD_TOWN_INDEX:

		addTownView = new AddTownView();
		addTownView->getManager()->start();

		break;
	case DATABASE_MENU_SHOW_TOWNS_INDEX:

		showTownsView = new ShowTownsView();
		showTownsView->getManager()->start();

		break;
	case DATABASE_MENU_FIND_TOWN_INDEX:

		townInfoView = new TownInfoView();
		townInfoView->getManager()->start();

		break;
	case DATABASE_MENU_EXIT_INDEX:

		getManager()->destroy();
		ViewManager::consoleStartPrivius();

		break;
	}

}