#pragma once
#include "logicview.h"
#include "model.h"
#include <functional>

#define TOWN_INFO_VIEW_NAME "Просмотр и редактирование информации о городе"

#define TOWN_INFO_TOWN_NAME "Введите название города"
#define TOWN_INFO_MENU_EDIT "Добавить информацию о городе"
#define TOWN_INFO_MENU_EDIT_INDEX 1
#define TOWN_INFO_EXIT "Вернуться назад"
#define TOWN_INFO_EXIT_INDEX 2

namespace ui {
	class TownInfoView;
}

class ui::TownInfoView : public LogicView {

public:

	TownInfoView();
	~TownInfoView();

	vector<View*> onCreateView() override;
	ViewSize onResizeView(ViewSize) override;
	void onAttachView() override;
	void onDestroyView() override;

private:

	model::Town* mTown;

	void onTownToFindTyped(string);
	void onExit();
	void onExitSelected(long);

	typedef function<void()> ExitCallback;

	class TownListInfo : public LogicView {

	public:

		TownListInfo(model::Town*);
		~TownListInfo();

		vector<View*> onCreateView() override;
		ViewSize onResizeView(ViewSize) override;
		void onAttachView() override;
		void onDestroyView() override;

		void setOnExitCallback(ExitCallback callback) {
			onExitCallback = callback;
		}

	private:

		ExitCallback onExitCallback;

		model::Town* mTown;

		void onEditMenuItemSelected(long);

	};

};
