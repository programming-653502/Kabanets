#pragma once
#include "logicview.h"
#include "model.h"
#include "editframeview.h"

#define EDIT_TOWN_VIEW_NAME "�������� ����� ���������� � ������"

#define EDIT_TOWN_IS_PLACE "��� ����� ����� ������?"
#define EDIT_TOWN_IS_PLACE_INDEX 1
#define EDIT_TOWN_IS_SIGHT "��� ����� ������������ ��������?"
#define EDIT_TOWN_IS_SIGHT_INDEX 2
#define EDIT_TOWN_EXIT "��������� �����"
#define EDIT_TOWN_EXIT_INDEX 3

namespace ui {
	class EditTownView;

	class TimeCorrect;
}

class ui::EditTownView : public LogicView {

public:

	EditTownView(model::Town*);
	~EditTownView();

	vector<View*> onCreateView() override;
	ViewSize onResizeView(ViewSize) override;
	void onAttachView() override;
	void onDestroyView() override;

private:

	model::Town* mTown;

	void onEditTownItemSelected(long);
	void onPlaceComplete(model::Place*);
	void onSightComplete(model::Sight*);

};



class ui::TimeCorrect : public Correct {

public:

	bool isCorrect(void*);
	string getDescription();

};