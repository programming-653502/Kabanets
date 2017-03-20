#pragma once
#include "menuview.h"
#include "logicview.h"

#define DATABASE_MENU_NAME "���� ������ �������"

#define DATABASE_MENU_ADD_TOWN "�������� ����� �������� ������"
#define DATABASE_MENU_ADD_TOWN_INDEX 1
#define DATABASE_MENU_SHOW_TOWNS "����������� ����� ���������� � �������"
#define DATABASE_MENU_SHOW_TOWNS_INDEX 2
#define DATABASE_MENU_FIND_TOWN "����� �������� ������������� ������"
#define DATABASE_MENU_FIND_TOWN_INDEX 3
#define DATABASE_MENU_EXIT "��������� �����"
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
