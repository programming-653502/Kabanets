#pragma once
#include "logicview.h"
#include "model.h"

#include <functional>

#define ADD_PLACE_VIEW_NAME "Создание нового места отдыха"

#define ADD_PLACE_TYPE "Выберите тип записи"
#define ADD_PLACE_TYPE_HOTEL "Отель"
#define ADD_PLACE_TYPE_HOTEL_INDEX 1
#define ADD_PLACE_TYPE_CINEMA "Кинотеатр"
#define ADD_PLACE_TYPE_CINEMA_INDEX 2
#define ADD_PLACE_TYPE_THEATER "Театр"
#define ADD_PLACE_TYPE_THEATER_INDEX 3
#define ADD_PLACE_TYPE_MUSEUM "Музей"
#define ADD_PLACE_TYPE_MUSEUM_INDEX 4
#define ADD_PLACE_TYPE_RESTAURANT "Ресторан"
#define ADD_PLACE_TYPE_RESTAURANT_INDEX 5

#define ADD_PLACE_NAME "Введите название места отдыха"
#define ADD_PLACE_ADRESS "Введите адресс"
#define ADD_PLACE_OPEN_TIME "Введите время открытия"
#define ADD_PLACE_CLOSE_TIME "Введите время закрытия"
#define ADD_PLACE_ADDITION "Дополнительная информация"

#define ADD_PLACE_EXIT "Вернуться назад"

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