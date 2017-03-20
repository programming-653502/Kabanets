#pragma once
#include "logicview.h"

#define SHOW_TOWNS_VIEW_NAME "�������� �������"

#define SHOW_TOWNS_EXIT "��������� �����"
#define SHOW_TOWNS_EXIT_INDEX 1


namespace ui {
	class ShowTownsView;
}

class ui::ShowTownsView : public LogicView {

public:

	ShowTownsView();

	vector<View*> onCreateView() override;
	ViewSize onResizeView(ViewSize) override;
	void onAttachView() override;
	void onDestroyView() override;

private:

	void onExitSelected(long);

};