#include "showtownsview.h"

#include "listview.h"
#include "labelview.h" 
#include "menuview.h"
#include "database.h"
#include "model.h"

#include "consolehelper.h"

#include <vector>

#define EMPTY "Ничего не найдено"

#define TOWN_POSTFIX "Город: "

#define TYPE_PLACE_POSTFIX "Место отдыха: "
#define NAME_PLACE_POSTFIX "Название места отдыха: "

#define TYPE_SIGHT_POSTFIX "Достопримечательност: "
#define NAME_SIGHT_POSTFIX "Название достопримечательности: "

using namespace std;
using namespace ui;
using namespace database;
using namespace model;

ShowTownsView::ShowTownsView() {

}

vector<View*> ShowTownsView::onCreateView() {
	vector<View*> views;

	XmlDataBase* databaseTowns = new XmlDataBase(XmlDataBase::DataBaseFileType::TOWNS);
	XmlDataBase* databasePlacesAndSights = new XmlDataBase(XmlDataBase::DataBaseFileType::PLACES_SIGHTS);

	vector<Town*> townsArray = databaseTowns->getTowns();

	for (Town* town : townsArray) {
		vector<Place*> placesArray = databasePlacesAndSights->getPlaces(to_string(town->getId()));

		string townName = TOWN_POSTFIX + town->getName();
		LabelView* townLabel = new LabelView();
		townLabel->setTitle(townName);
		townLabel->setMode(LabelView::ALONE);
		views.push_back(townLabel);

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
			
			placeList->addNewItem(typeItem)->addNewItem(nameItem);
			placeList->addPaddings(0, 1, 0, 1);

			views.push_back(placeList);
			
		}

		vector<Sight*> sightsArray = databasePlacesAndSights->getSights(to_string(town->getId()));

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
			
			sightList->addNewItem(typeItem)->addNewItem(nameItem);

			sightList->addPaddings(0, 1, 0, 0);

			views.push_back(sightList);
		}

		if (placesArray.empty() && sightsArray.empty()) {
			LabelView* townLabel = new LabelView();
			townLabel->setTitle(EMPTY);
			townLabel->setMode(LabelView::ALONE);
			views.push_back(townLabel);
		}

		for (Place* place : placesArray) {
			delete place;
		}
		placesArray.clear();

		for (Sight* sight : sightsArray) {
			delete sight;
		}
		sightsArray.clear();
	}

	for (Town* town : townsArray) {
		delete town;
	}
	townsArray.clear();

	MenuItem itemExit(SHOW_TOWNS_EXIT, 1);

	MenuView* menu = new MenuView();
	menu->setOnItemSelectedCallback(std::bind(&ShowTownsView::onExitSelected, this, std::placeholders::_1));
	menu->addItem(itemExit);
	views.push_back(menu);

	return views;
}

ViewSize ShowTownsView::onResizeView(ViewSize size) {
	return ViewManager::UNSPECIFIED;
}

void ShowTownsView::onAttachView() {
	util::ConsoleHelper::WriteNameOfView(SHOW_TOWNS_VIEW_NAME);
}

void ShowTownsView::onDestroyView() {
}

void ShowTownsView::onExitSelected(long index) {
	if (index == SHOW_TOWNS_EXIT_INDEX) {
		getManager()->destroy();
		ViewManager::consoleStartPrivius();
	}
}

