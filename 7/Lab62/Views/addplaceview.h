#pragma once
#include "logicview.h"
#include "model.h"

#include <functional>

#define ADD_PLACE_VIEW_NAME "�������� ������ ����� ������"

#define ADD_PLACE_TYPE "�������� ��� ������"
#define ADD_PLACE_TYPE_HOTEL "�����"
#define ADD_PLACE_TYPE_HOTEL_INDEX 1
#define ADD_PLACE_TYPE_CINEMA "���������"
#define ADD_PLACE_TYPE_CINEMA_INDEX 2
#define ADD_PLACE_TYPE_THEATER "�����"
#define ADD_PLACE_TYPE_THEATER_INDEX 3
#define ADD_PLACE_TYPE_MUSEUM "�����"
#define ADD_PLACE_TYPE_MUSEUM_INDEX 4
#define ADD_PLACE_TYPE_RESTAURANT "��������"
#define ADD_PLACE_TYPE_RESTAURANT_INDEX 5

#define ADD_PLACE_NAME "������� �������� ����� ������"
#define ADD_PLACE_ADRESS "������� ������"
#define ADD_PLACE_OPEN_TIME "������� ����� ��������"
#define ADD_PLACE_CLOSE_TIME "������� ����� ��������"
#define ADD_PLACE_ADDITION "�������������� ����������"

#define ADD_PLACE_EXIT "��������� �����"

namespace ui {
	class AddPlaceView;

	typedef std::function<void(model::Place*)> PlaceCompleteCallback;
}

class ui::AddPlaceView : public LogicView {

public:

	AddPlaceView();
	~AddPlaceView();

	vector<View*> onCreateView() override;
	ViewSize onResizeView(ViewSize) override;
	void onAttachView() override;
	void onDestroyView() override;

	void setOnPlaceCompleteCallback(PlaceCompleteCallback callback) {
		onPlaceCompleteCallback = callback;
	}

private:

	model::Place* mTypedPlace;

	PlaceCompleteCallback onPlaceCompleteCallback;

	void onPlaceTypeSelected(long);
	void onPlaceNameTyped(string);
	void onPlaceAdressTyped(string);
	void onPlaceOpenTimeTyped(string);
	void onPlaceCloseTimeTyped(string);
	void onPlaceAddtionsTyped(string);

	void completePlace();
};