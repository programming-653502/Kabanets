#include "addtownview.h"

#include "editframeview.h"
#include "database.h"
#include "model.h"
#include "consolehelper.h"

#include "consolehelper.h"

#define NAME_IS_EXIST "Такой город уже существует"

using namespace ui;
using namespace database;
using namespace model;

AddTownView::AddTownView() {

}

vector<View*> AddTownView::onCreateView() {
	vector<View*> views;

	EditFrameView* townName = new EditFrameView(ADD_TOWN_NAME);
	townName->setCorrectChecking(new AddTownCorrect( (new XmlDataBase(XmlDataBase::DataBaseFileType::TOWNS))->getTowns() ));
	townName->setOnAnswerTypedCallback( std::bind(&AddTownView::onTownNameTyped, this, std::placeholders::_1) );
	views.push_back(townName);

	return views;
}

ViewSize AddTownView::onResizeView(ViewSize size) {
	return ViewManager::UNSPECIFIED;
}

void AddTownView::onAttachView() {
	util::ConsoleHelper::WriteNameOfView(ADD_TOWN_VIEW_NAME);
}

void AddTownView::onDestroyView() {
}

void AddTownView::onTownNameTyped(string townName) {
	Town* town = new Town(townName);
	XmlDataBase* database = new XmlDataBase(XmlDataBase::DataBaseFileType::TOWNS);
	database->writeTown(town);

	getManager()->destroy();
	ViewManager::consoleStartPrivius();
}

AddTownCorrect::AddTownCorrect(vector<Town*> towns) {
	mTowns = towns;
}

AddTownCorrect::~AddTownCorrect() {
	for (Town* town : mTowns) {
		delete town;
	}
	mTowns.clear();
}


bool AddTownCorrect::isCorrect(void* obj) {
	string* stringObj = reinterpret_cast<string*>(obj);
	if (stringObj != 0)
	{
		string input = *stringObj;

		for (Town* town : mTowns)
		{
			if (town->getName().compare(input) == 0)
			{
				return false;
			}
		}
	} else {
		return false;
	}

	return true;
}

string AddTownCorrect::getDescription() {
	return NAME_IS_EXIST;
}