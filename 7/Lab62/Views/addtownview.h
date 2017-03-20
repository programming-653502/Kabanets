#pragma once
#include "logicview.h"

#include "editframeview.h"
#include "model.h"

#define ADD_TOWN_VIEW_NAME "Добавление нового города"

#define ADD_TOWN_NAME "Введите название города"

namespace ui {
	class AddTownView;

	class AddTownCorrect;
}

class ui::AddTownView : public LogicView {

public:

	AddTownView();

	vector<View*> onCreateView() override;
	ViewSize onResizeView(ViewSize) override;
	void onAttachView() override;
	void onDestroyView() override;

private:

	void onTownNameTyped(string);

};

class ui::AddTownCorrect : public Correct {

public:

	AddTownCorrect(vector<model::Town*>);
	~AddTownCorrect();

	bool isCorrect(void*);
	string getDescription();

private:

	vector<model::Town*> mTowns;

};