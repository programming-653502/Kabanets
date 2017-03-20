#pragma once
#include "logicview.h"
#include "model.h"

#include <functional>

#define ADD_SIGHT_VIEW_NAME "�������� ����� ������������ ��������"

#define ADD_SIGHT_TYPE "�������� ��� ������"
#define ADD_SIGHT_TYPE_MONUMENT "��������"
#define ADD_SIGHT_TYPE_MONUMENT_INDEX 1
#define ADD_SIGHT_TYPE_BUILDING "����������"
#define ADD_SIGHT_TYPE_BUILDING_INDEX 2

#define ADD_SIGHT_NAME "������� �������� ������������ ��������"
#define ADD_SIGHT_ADRESS "������� ������"
#define ADD_SIGHT_OPEN_TIME "������� ����� ��������"
#define ADD_SIGHT_CLOSE_TIME "������� ����� ��������"
#define ADD_SIGHT_ADDITION "�������������� ����������"

#define ADD_SIGHT_EXIT "��������� �����"

namespace ui {
	class AddSightView;

	typedef std::function<void(model::Sight*)> SightCompleteCallback;
}

class ui::AddSightView : public LogicView {

public:

	AddSightView();
	~AddSightView();

	vector<View*> onCreateView() override;
	ViewSize onResizeView(ViewSize) override;
	void onAttachView() override;
	void onDestroyView() override;

	void setOnSightCompleteCallback(SightCompleteCallback callback) {
		onSightCompleteCallback = callback;
	}

private:

	model::Sight* mTypedSight;

	// TODO: make if referce?
	SightCompleteCallback onSightCompleteCallback;

	void onSightTypeSelected(long);
	void onSightNameTyped(string);
	void onSightAdressTyped(string);
	void onSightOpenTimeTyped(string);
	void onSightCloseTimeTyped(string);
	void onSightAddtionsTyped(string);

	void completeSight();

};