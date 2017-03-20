#pragma once
#include "logicview.h"
#include "model.h"

#include <functional>

#define ADD_SIGHT_VIEW_NAME "Создание новой исторической ценности"

#define ADD_SIGHT_TYPE "Выберите тип записи"
#define ADD_SIGHT_TYPE_MONUMENT "Памятник"
#define ADD_SIGHT_TYPE_MONUMENT_INDEX 1
#define ADD_SIGHT_TYPE_BUILDING "Сооружение"
#define ADD_SIGHT_TYPE_BUILDING_INDEX 2

#define ADD_SIGHT_NAME "Введите название исторической ценности"
#define ADD_SIGHT_ADRESS "Введите адресс"
#define ADD_SIGHT_OPEN_TIME "Введите время открытия"
#define ADD_SIGHT_CLOSE_TIME "Введите время закрытия"
#define ADD_SIGHT_ADDITION "Дополнительная информация"

#define ADD_SIGHT_EXIT "Вернуться назад"

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