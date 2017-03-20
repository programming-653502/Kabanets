#pragma once
#include "menuview.h"
#include "logicview.h"

#include "model.h"

#define NOTEBOOK_EDIT_NAME "����� �����������"

#define NOTEBOOK_EDIT_TOWN "������� �����"
#define NOTEBOOK_EDIT_COMMENT "������� �����������"
#define NOTEBOOK_EXIT "��������� �����"

namespace ui {
	class NotebookEdit;
}

class ui::NotebookEdit : public LogicView {

public:

	NotebookEdit();

	vector<View*> onCreateView() override;
	ViewSize onResizeView(ViewSize) override;
	void onAttachView() override;
	void onDestroyView() override;

private:

	model::Comment* mComment;

	void onCommentTownTyped(string);
	void onCommentTyped(string);

	void completeComment();
};
