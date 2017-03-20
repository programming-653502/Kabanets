#pragma once
#include "logicview.h"

#define MAIN_MENU_NAME "������� ����"

#define MAIN_MENU_DB_OPEN "������� ���� ������ �������"
#define MAIN_MENU_DB_OPEN_INDEX 1
#define MAIN_MENU_NOTEBOOK_OPEN "������� �������� ������"
#define MAIN_MENU_NOTEBOOK_OPEN_INDEX 2
#define MAIN_MENU_EXIT "�����"
#define MAIN_MENU_EXIT_INDEX 3


namespace ui {
	class MainMenu;
}

class ui::MainMenu : public LogicView {

public :

	MainMenu();

	vector<View*> onCreateView() override;
	ViewSize onResizeView(ViewSize) override;
	void onAttachView() override;
	void onDestroyView() override;

private:

	void onMainMenuItemSelected(long);
};