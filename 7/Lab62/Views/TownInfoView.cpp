#include "towninfoview.h"
#include "edittownview.h"

#include "menuview.h"
#include "editframeview.h"
#include "database.h"
#include "labelview.h"
#include "listview.h"

#include "consolehelper.h"

#define NOTHING_FOUND "Ничего не найдено"

#define TYPE_PLACE_POSTFIX "Место отдыха: "
#define NAME_PLACE_POSTFIX "Название места отдыха: "
#define ADRESS_PLACE_POSTFIX "Адресс места отдыха: "
#define OPENTIME_PLACE_POSTFIX "Время открытия места отдыха: "
#define CLOSETIME_PLACE_POSTFIX "Время закрытия места отдыха: "
#define ADDITIONS_PLACE_POSTFIX "Дополнительная информация: "

#define TYPE_SIGHT_POSTFIX "Достопримечательност: "
#define NAME_SIGHT_POSTFIX "Название достопримечательности: "
#define ADRESS_SIGHT_POSTFIX "Адресс достопримечательности: "
#define OPENTIME_SIGHT_POSTFIX "Время открытия достопримечательности: "
#define CLOSETIME_SIGHT_POSTFIX "Время закрытия достопримечательности: "
#define ADDITIONS_SIGHT_POSTFIX "Дополнительная информация: "


using namespace ui;
using namespace model;
using namespace database;

TownInfoView::TownInfoView() {
}

TownInfoView::~TownInfoView() {
	delete mTown;
}

vector<View*> TownInfoView::onCreateView() {
	vector<View*> views;

	EditFrameView* townToFind = new EditFrameView(TOWN_INFO_TOWN_NAME);
	townToFind->setOnAnswerTypedCallback(std::bind(&TownInfoView::onTownToFindTyped, this, std::placeholders::_1));
	townToFind->addPaddings(0, 1, 0, 0);
	views.push_back(townToFind);

	return views;
}

ViewSize TownInfoView::onResizeView(ViewSize size) {
	return ViewManager::UNSPECIFIED;
}

void TownInfoView::onAttachView() {
	util::ConsoleHelper::WriteNameOfView(TOWN_INFO_VIEW_NAME);
}

void TownInfoView::onDestroyView() {
}

void TownInfoView::onTownToFindTyped(string townName) {

	mTown = new Town(townName);

	vector<Town*> towns = (new database::XmlDataBase(database::XmlDataBase::DataBaseFileType::TOWNS))->getTowns();
	bool find = false;
	for (Town* town : towns) {
		if (town->getName().compare(townName) == 0) {
			find = true;

			mTown->setId(town->getId());

			TownListInfo* townInfo = new TownListInfo(mTown);
			townInfo->setOnExitCallback(std::bind(&TownInfoView::onExit, this));
			getManager()->addNewChild(townInfo);

			break;
		}
	}

	if (!find) {

		LabelView* label = new LabelView();
		label->setMode(LabelView::ALONE);
		label->setTitle(NOTHING_FOUND);
		getManager()->addNewChild(label);

		MenuItem exit(TOWN_INFO_EXIT, 1);

		MenuView* menu = new MenuView();
		menu->addItem(exit);
		menu->setOnItemSelectedCallback(std::bind(&TownInfoView::onExitSelected, this, std::placeholders::_1));
		getManager()->addNewChild(menu);

	}

}

void TownInfoView::onExit() {

	getManager()->destroy();
	ViewManager::consoleStartPrivius();

}


void TownInfoView::onExitSelected(long item) {
	if (item == 1) {
		onExit();
	}
}




TownInfoView::TownListInfo::TownListInfo(Town* town) {
	mTown = town;
}

TownInfoView::TownListInfo::~TownListInfo() {
	delete mTown;
}


vector<View*> TownInfoView::TownListInfo::onCreateView() {
	vector<View*> views;

	vector<Place*> placesArray = (new XmlDataBase(XmlDataBase::DataBaseFileType::PLACES_SIGHTS))->getPlaces(to_string(mTown->getId()));

	for (Place* place : placesArray) {
		ListView* placeList = new ListView();

		string typeItem = TYPE_PLACE_POSTFIX;
		switch (place->getType()) {
		case PlaceType::HOTEL:
			typeItem += HOTEL_H;
			break;
		case PlaceType::CINEMA:
			typeItem += CINEMA_H;
			break;
		case PlaceType::THEATER:
			typeItem += THEATER_H;
			break;
		case PlaceType::MESEUM:
			typeItem += MESEUM_H;
			break;
		case PlaceType::RESTAURANT:
			typeItem += RESTAURANT_H;
			break;
		}

		string nameItem = NAME_PLACE_POSTFIX + place->getName();
		string adressItem = ADDITIONS_PLACE_POSTFIX + place->getAdress();
		string openTimeItem = OPENTIME_PLACE_POSTFIX + place->getOpenTime();
		string closeTimeItem = CLOSETIME_PLACE_POSTFIX + place->getCloseTime();
		string additionsItem = ADDITIONS_PLACE_POSTFIX + place->getAddtions();

		placeList->addNewItem(typeItem)->addNewItem(nameItem)->addNewItem(adressItem)->addNewItem(openTimeItem)->
			addNewItem(closeTimeItem)->addNewItem(additionsItem);

		placeList->addPaddings(0, 1, 0, 2);

		views.push_back(placeList);
	}

	vector<Sight*> sightsArray = (new XmlDataBase(XmlDataBase::DataBaseFileType::PLACES_SIGHTS))->getSights(to_string(mTown->getId()));

	for (Sight* sight : sightsArray) {
		ListView* sightList = new ListView();

		string typeItem = TYPE_SIGHT_POSTFIX;
		switch (sight->getType()) {
		case SightType::MONUMENT:
			typeItem += MONUMENT_H;
			break;
		case SightType::BUILDING:
			typeItem += BUILDING_H;
			break;
		}

		string nameItem = NAME_SIGHT_POSTFIX + sight->getName();
		string adressItem = ADDITIONS_SIGHT_POSTFIX + sight->getAdress();
		string openTimeItem = OPENTIME_SIGHT_POSTFIX + sight->getOpenTime();
		string closeTimeItem = CLOSETIME_SIGHT_POSTFIX + sight->getCloseTime();
		string additionsItem = ADDITIONS_SIGHT_POSTFIX + sight->getAddtions();

		sightList->addNewItem(typeItem)->addNewItem(nameItem)->addNewItem(adressItem)->addNewItem(openTimeItem)->
			addNewItem(closeTimeItem)->addNewItem(additionsItem);

		sightList->addPaddings(0, 1, 0, 2);

		views.push_back(sightList);
	}

	for (Place* place : placesArray) {
		delete place;
	}
	placesArray.clear();

	for (Sight* sight : sightsArray) {
		delete sight;
	}
	sightsArray.clear();

	MenuItem editTownInfo(TOWN_INFO_MENU_EDIT, TOWN_INFO_MENU_EDIT_INDEX);
	MenuItem exit(TOWN_INFO_EXIT, TOWN_INFO_EXIT_INDEX);

	MenuView* menu = new MenuView();
	menu->addItem(editTownInfo)->addItem(exit);
	menu->setOnItemSelectedCallback(std::bind(&TownListInfo::onEditMenuItemSelected, this, std::placeholders::_1));
	views.push_back(menu);

	return views;
}

ViewSize TownInfoView::TownListInfo::onResizeView(ViewSize size) {
	return ViewManager::UNSPECIFIED;
}

void TownInfoView::TownListInfo::onAttachView() {
}

void TownInfoView::TownListInfo::onDestroyView() {
}

void TownInfoView::TownListInfo::onEditMenuItemSelected(long item) {
	
	EditTownView* editTownView;
	switch (item) {
	case TOWN_INFO_MENU_EDIT_INDEX:

		editTownView = new EditTownView(mTown);
		editTownView->getManager()->start();

		break;
	case TOWN_INFO_EXIT_INDEX:

		getManager()->destroy();
		onExitCallback();
		//ViewManager::consoleStartPrivius();

		break;
	}

}