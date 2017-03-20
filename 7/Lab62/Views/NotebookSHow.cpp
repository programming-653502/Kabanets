#include "nbshow.h"

#include "listview.h"
#include "database.h"
#include "nbedit.h"

#include "consolehelper.h"

#define TOWN_POSTFIX "Город: "

using namespace ui;
using namespace database;

NotebookShow::NotebookShow() {
}

vector<View*> NotebookShow::onCreateView() {
	vector<View*> views;

	vector<Comment*> comments = (new XmlDataBase(XmlDataBase::COMMENT))->getComment();

	for (Comment* comment : comments) {

		ListView* commentList = new ListView();

		string townName = TOWN_POSTFIX + comment->getTownName();
		string commentStr = comment->getComment();

		commentList->addNewItem(townName)->addNewItem(commentStr);
		commentList->addPaddings(0, 2, 0, 1);

		views.push_back(commentList);
	}

	MenuItem addTown(NOTEBOOK_ADD_ENTIRE, NOTEBOOK_ADD_ENTIRE_INDEX);
	MenuItem exit(NOTEBOOK_EXIT, NOTEBOOK_EXIT_INDEX);

	MenuView* menu = new MenuView();
	menu->addItem(addTown)->addItem(exit);
	menu->setOnItemSelectedCallback(std::bind(&NotebookShow::onNotebookMenuItemSelected, this, std::placeholders::_1));

	views.push_back(menu);

	return views;
}

ViewSize NotebookShow::onResizeView(ViewSize) {
	return ViewManager::UNSPECIFIED;
}

void NotebookShow::onAttachView() {
	util::ConsoleHelper::WriteNameOfView(NOTEBOOK_SHOW_NAME);
}

void NotebookShow::onDestroyView() {
}

void NotebookShow::onNotebookMenuItemSelected(long item) {

	NotebookEdit* notebookEdit;
	switch (item) {
	case NOTEBOOK_ADD_ENTIRE_INDEX:

		notebookEdit = new NotebookEdit();
		notebookEdit->getManager()->start();

		break;
	case NOTEBOOK_EXIT_INDEX:

		getManager()->destroy();
		ViewManager::consoleStartPrivius();

		break;
	}

}