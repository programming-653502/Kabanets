#include "edittownview.h"

#include "addplaceview.h"
#include "addsightview.h"
#include "database.h"

#include "menuview.h"

#include "consolehelper.h"

using namespace ui;
using namespace model;

EditTownView::EditTownView(Town* town) {
	mTown = town;
}

EditTownView::~EditTownView() {
	delete mTown;
}

vector<View*> EditTownView::onCreateView() {
	vector<View*> views;

	MenuItem isPlace(EDIT_TOWN_IS_PLACE, EDIT_TOWN_IS_PLACE_INDEX);
	MenuItem isSight(EDIT_TOWN_IS_SIGHT, EDIT_TOWN_IS_SIGHT_INDEX);
	MenuItem exit(EDIT_TOWN_EXIT, EDIT_TOWN_EXIT_INDEX);

	MenuView* menu = new MenuView();
	menu->addItem(isPlace)->addItem(isSight)->addItem(exit);
	menu->setOnItemSelectedCallback(std::bind(&EditTownView::onEditTownItemSelected, this, std::placeholders::_1));

	views.push_back(menu);

	return views;
}

ViewSize EditTownView::onResizeView(ViewSize size) {
	return ViewManager::UNSPECIFIED;
}

void EditTownView::onAttachView() {
	util::ConsoleHelper::WriteNameOfView(EDIT_TOWN_VIEW_NAME);
}

void EditTownView::onDestroyView() {
}

void EditTownView::onEditTownItemSelected(long item) {

	AddPlaceView* addPlaceView;
	AddSightView* addSightView;
	switch (item) {
	case EDIT_TOWN_IS_PLACE_INDEX:

		addPlaceView = new AddPlaceView();
		addPlaceView->setOnPlaceCompleteCallback(std::bind(&EditTownView::onPlaceComplete, this, std::placeholders::_1));
		addPlaceView->getManager()->start();

		break;
	case EDIT_TOWN_IS_SIGHT_INDEX:

		addSightView = new AddSightView();
		addSightView->setOnSightCompleteCallback(std::bind(&EditTownView::onSightComplete, this, std::placeholders::_1));
		addSightView->getManager()->start();

		break;
	case EDIT_TOWN_EXIT_INDEX:

		getManager()->destroy();
		ViewManager::consoleStartPrivius();
		
		break;
	}
}

void EditTownView::onPlaceComplete(model::Place* place) {

	(new database::XmlDataBase(database::XmlDataBase::DataBaseFileType::PLACES_SIGHTS))->writePlace(place, to_string(mTown->getId()));

	getManager()->destroy();
	ViewManager::consoleStartPrivius();
}

void EditTownView::onSightComplete(model::Sight* sight) {

	(new database::XmlDataBase(database::XmlDataBase::DataBaseFileType::PLACES_SIGHTS))->writeSight(sight, to_string(mTown->getId()));

	getManager()->destroy();
	ViewManager::consoleStartPrivius();
}