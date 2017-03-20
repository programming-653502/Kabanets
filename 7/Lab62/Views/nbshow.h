#pragma once
#include "menuview.h"
#include "logicview.h"

#define NOTEBOOK_SHOW_NAME "�������� ������"

#define NOTEBOOK_ADD_ENTIRE "�������� ����� ������"
#define NOTEBOOK_ADD_ENTIRE_INDEX 1
#define NOTEBOOK_EXIT "��������� �����"
#define NOTEBOOK_EXIT_INDEX 2


namespace ui {
	class NotebookShow;
}

class ui::NotebookShow : public LogicView {

public:

	NotebookShow();

	vector<View*> onCreateView() override;
	ViewSize onResizeView(ViewSize) override;
	void onAttachView() override;
	void onDestroyView() override;

private:

	void onNotebookMenuItemSelected(long);
};
