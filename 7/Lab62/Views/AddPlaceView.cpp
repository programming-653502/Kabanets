#include "addplaceview.h"

#include "menuview.h"
#include "editframeview.h"
#include "edittownview.h"

#include "consolehelper.h"

using namespace ui;
using namespace model;

AddPlaceView::AddPlaceView() {
	mTypedPlace = new Place();
}

AddPlaceView::~AddPlaceView() {
	delete mTypedPlace;
}

vector<View*> AddPlaceView::onCreateView() {
	vector<View*> views;

	MenuItem addPlaceHotel(ADD_PLACE_TYPE_HOTEL, ADD_PLACE_TYPE_HOTEL_INDEX);
	MenuItem addPlaceCinema(ADD_PLACE_TYPE_CINEMA, ADD_PLACE_TYPE_CINEMA_INDEX);
	MenuItem addPlaceTheater(ADD_PLACE_TYPE_THEATER, ADD_PLACE_TYPE_THEATER_INDEX);
	MenuItem addPlaceMuseum(ADD_PLACE_TYPE_MUSEUM, ADD_PLACE_TYPE_MUSEUM_INDEX);
	MenuItem addPlaceRestaurant(ADD_PLACE_TYPE_RESTAURANT, ADD_PLACE_TYPE_RESTAURANT_INDEX);

	MenuView* menu = new MenuView(ADD_PLACE_TYPE);
	menu->addItem(addPlaceHotel)->addItem(addPlaceCinema)->
		addItem(addPlaceTheater)->addItem(addPlaceMuseum)->
		addItem(addPlaceRestaurant);
	menu->setOnItemSelectedCallback(std::bind(&AddPlaceView::onPlaceTypeSelected, this, std::placeholders::_1));
	views.push_back(menu);

	EditFrameView* namePlaceEdit = new EditFrameView(ADD_PLACE_NAME);
	namePlaceEdit->setCorrectChecking(new StringEmptyCorrect());
	namePlaceEdit->setOnAnswerTypedCallback(std::bind(&AddPlaceView::onPlaceNameTyped, this, std::placeholders::_1));
	views.push_back(namePlaceEdit);

	EditFrameView* adressPlaceEdit = new EditFrameView(ADD_PLACE_ADRESS);
	adressPlaceEdit->setCorrectChecking(new StringEmptyCorrect());
	adressPlaceEdit->setOnAnswerTypedCallback(std::bind(&AddPlaceView::onPlaceAdressTyped, this, std::placeholders::_1));
	views.push_back(adressPlaceEdit);

	EditFrameView* openTimePlaceEdit = new EditFrameView(ADD_PLACE_OPEN_TIME);
	openTimePlaceEdit->setCorrectChecking(new TimeCorrect());
	openTimePlaceEdit->setOnAnswerTypedCallback(std::bind(&AddPlaceView::onPlaceOpenTimeTyped, this, std::placeholders::_1));
	views.push_back(openTimePlaceEdit);

	EditFrameView* closeTimePlaceEdit = new EditFrameView(ADD_PLACE_CLOSE_TIME);
	closeTimePlaceEdit->setCorrectChecking(new TimeCorrect());
	closeTimePlaceEdit->setOnAnswerTypedCallback(std::bind(&AddPlaceView::onPlaceCloseTimeTyped, this, std::placeholders::_1));
	views.push_back(closeTimePlaceEdit);

	EditFrameView* addtionPlaceEdit = new EditFrameView(ADD_PLACE_ADDITION);
	//addtionPlaceEdit->setCorrectChecking(new StringEmptyCorrect());
	addtionPlaceEdit->setOnAnswerTypedCallback(std::bind(&AddPlaceView::onPlaceAddtionsTyped, this, std::placeholders::_1));
	views.push_back(addtionPlaceEdit);

	return views;
}

ViewSize AddPlaceView::onResizeView(ViewSize size) {
	return ViewManager::UNSPECIFIED;
}

void AddPlaceView::onAttachView() {
	util::ConsoleHelper::WriteNameOfView(ADD_PLACE_VIEW_NAME);
}

void AddPlaceView::onDestroyView() {
}

void AddPlaceView::onPlaceTypeSelected(long item) {

	switch (item) {
	case ADD_PLACE_TYPE_HOTEL_INDEX:

		mTypedPlace->setType(PlaceType::HOTEL);

		break;
	case ADD_PLACE_TYPE_CINEMA_INDEX:

		mTypedPlace->setType(PlaceType::CINEMA);

		break;
	case ADD_PLACE_TYPE_THEATER_INDEX:

		mTypedPlace->setType(PlaceType::THEATER);

		break;
	case ADD_PLACE_TYPE_MUSEUM_INDEX:

		mTypedPlace->setType(PlaceType::MESEUM);

		break;
	case ADD_PLACE_TYPE_RESTAURANT_INDEX:

		mTypedPlace->setType(PlaceType::RESTAURANT);

		break;
	}
}

void AddPlaceView::onPlaceNameTyped(string name) {
	mTypedPlace->setName(name);
}

void AddPlaceView::onPlaceAdressTyped(string adress) {
	mTypedPlace->setAdress(adress);
}

void AddPlaceView::onPlaceOpenTimeTyped(string openTIme) {
	mTypedPlace->setOpenTime(openTIme);
}

void AddPlaceView::onPlaceCloseTimeTyped(string closeTime) {
	mTypedPlace->setCloseTime(closeTime);
}

void AddPlaceView::onPlaceAddtionsTyped(string additions) {
	mTypedPlace->setAddtions(additions);

	completePlace();
}

void AddPlaceView::completePlace() {
	getManager()->destroy();
	//ViewManager::consoleStartPrivius();

	onPlaceCompleteCallback(mTypedPlace);
}


