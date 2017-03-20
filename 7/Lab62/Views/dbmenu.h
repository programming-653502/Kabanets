#pragma once
#include "menuview.h"
#include "logicview.h"

#define DATABASE_MENU_NAME "База данных городов"

#define DATABASE_MENU_ADD_TOWN "Добавить новую карточку города"
#define DATABASE_MENU_ADD_TOWN_INDEX 1
#define DATABASE_MENU_SHOW_TOWNS "Просмотреть общую информацию о городах"
#define DATABASE_MENU_SHOW_TOWNS_INDEX 2
#define DATABASE_MENU_FIND_TOWN "Найти карточку определенного города"
#define DATABASE_MENU_FIND_TOWN_INDEX 3
#define DATABASE_MENU_EXIT "Вернуться назад"
#define DATABASE_MENU_EXIT_INDEX 4

namespace ui {
	class DatabaseMenu;
}

class ui::DatabaseMenu : public LogicView {

public:

	DatabaseMenu();

	vector<View*> onCreateView() override;
	ViewSize onResizeView(ViewSize) override;
	void onAttachView() override;
	void onDestroyView() override;

private:

	void onMainMenuItemSelected(long);
};
