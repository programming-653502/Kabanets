#include "addsightview.h"

#include "menuview.h"
#include "editframeview.h"
#include "edittownview.h"

#include "consolehelper.h"

using namespace ui;
using namespace model;

AddSightView::AddSightView() {
	mTypedSight = new Sight();
}

AddSightView::~AddSightView() {
	delete mTypedSight;
}

vector<View*> AddSightView::onCreateView() {
	vector<View*> views;

	MenuItem addPlaceHotel(ADD_SIGHT_TYPE_MONUMENT, ADD_SIGHT_TYPE_MONUMENT_INDEX);
	MenuItem addPlaceCinema(ADD_SIGHT_TYPE_BUILDING, ADD_SIGHT_TYPE_BUILDING_INDEX);

	MenuView* menu = new MenuView(ADD_SIGHT_TYPE);
	menu->addItem(addPlaceHotel)->addItem(addPlaceCinema);
	menu->setOnItemSelectedCallback(std::bind(&AddSightView::onSightTypeSelected, this, std::placeholders::_1));

	views.push_back(menu);

	EditFrameView* namePlaceEdit = new EditFrameView(ADD_SIGHT_NAME);
	namePlaceEdit->setCorrectChecking(new StringEmptyCorrect());
	namePlaceEdit->setOnAnswerTypedCallback(std::bind(&AddSightView::onSightNameTyped, this, std::placeholders::_1));
	views.push_back(namePlaceEdit);

	EditFrameView* adressPlaceEdit = new EditFrameView(ADD_SIGHT_ADRESS);
	adressPlaceEdit->setCorrectChecking(new StringEmptyCorrect());
	adressPlaceEdit->setOnAnswerTypedCallback(std::bind(&AddSightView::onSightAdressTyped, this, std::placeholders::_1));
	views.push_back(adressPlaceEdit);

	EditFrameView* openTimePlaceEdit = new EditFrameView(ADD_SIGHT_OPEN_TIME);
	openTimePlaceEdit->setCorrectChecking(new TimeCorrect());
	openTimePlaceEdit->setOnAnswerTypedCallback(std::bind(&AddSightView::onSightOpenTimeTyped, this, std::placeholders::_1));
	views.push_back(openTimePlaceEdit);

	EditFrameView* closeTimePlaceEdit = new EditFrameView(ADD_SIGHT_CLOSE_TIME);
	closeTimePlaceEdit->setCorrectChecking(new TimeCorrect());
	closeTimePlaceEdit->setOnAnswerTypedCallback(std::bind(&AddSightView::onSightCloseTimeTyped, this, std::placeholders::_1));
	views.push_back(closeTimePlaceEdit);

	EditFrameView* addtionPlaceEdit = new EditFrameView(ADD_SIGHT_ADDITION);
	//addtionPlaceEdit->setCorrectChecking(new StringEmptyCorrect());
	addtionPlaceEdit->setOnAnswerTypedCallback(std::bind(&AddSightView::onSightAddtionsTyped, this, std::placeholders::_1));
	views.push_back(addtionPlaceEdit);

	return views;
}

ViewSize AddSightView::onResizeView(ViewSize size) {
	return ViewManager::UNSPECIFIED;
}

void AddSightView::onAttachView() {
	util::ConsoleHelper::WriteNameOfView(ADD_SIGHT_VIEW_NAME);
}

void AddSightView::onDestroyView() {
}

void AddSightView::onSightTypeSelected(long item) {

	switch (item) {
	case ADD_SIGHT_TYPE_MONUMENT_INDEX:

		mTypedSight->setType(SightType::MONUMENT);

		break;
	case ADD_SIGHT_TYPE_BUILDING_INDEX:

		mTypedSight->setType(SightType::BUILDING);

		break;
	}
}
	
void AddSightView::onSightNameTyped(string name) {
	mTypedSight->setName(name);
}

void AddSightView::onSightAdressTyped(string adress) {
	mTypedSight->setAdress(adress);
}

void AddSightView::onSightOpenTimeTyped(string openTIme) {
	mTypedSight->setOpenTime(openTIme);
}

void AddSightView::onSightCloseTimeTyped(string closeTime) {
	mTypedSight->setCloseTime(closeTime);
}

void AddSightView::onSightAddtionsTyped(string additions) {
	mTypedSight->setAddtions(additions);

	completeSight();
}

void AddSightView::completeSight() {
	getManager()->destroy();

	onSightCompleteCallback(mTypedSight);
}
