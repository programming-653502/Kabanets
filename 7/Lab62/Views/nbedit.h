#pragma once
#include "menuview.h"
#include "logicview.h"

#include "model.h"

#define NOTEBOOK_EDIT_NAME "Новый комментарий"

#define NOTEBOOK_EDIT_TOWN "Введите город"
#define NOTEBOOK_EDIT_COMMENT "Введите комментарий"
#define NOTEBOOK_EXIT "Вернуться назад"

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
