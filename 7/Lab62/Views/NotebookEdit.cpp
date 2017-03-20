#include "nbedit.h"

#include "editframeview.h"
#include "database.h"

#include "consolehelper.h"

using namespace ui;
using namespace database;

NotebookEdit::NotebookEdit() {
	mComment = new Comment();
}

vector<View*> NotebookEdit::onCreateView() {
	vector<View*> views;

	EditFrameView* townToComment = new EditFrameView(NOTEBOOK_EDIT_TOWN);
	townToComment->setOnAnswerTypedCallback(std::bind(&NotebookEdit::onCommentTownTyped, this, std::placeholders::_1));
	townToComment->addPaddings(0, 1, 0, 0);
	views.push_back(townToComment);

	EditFrameView* comment = new EditFrameView(NOTEBOOK_EDIT_COMMENT);
	comment->setOnAnswerTypedCallback(std::bind(&NotebookEdit::onCommentTyped, this, std::placeholders::_1));
	comment->addPaddings(0, 1, 0, 0);
	views.push_back(comment);

	return views;
}

ViewSize NotebookEdit::onResizeView(ViewSize) {
	return ViewManager::UNSPECIFIED;
}

void NotebookEdit::onAttachView() {
	util::ConsoleHelper::WriteNameOfView(NOTEBOOK_EDIT_NAME);
}

void NotebookEdit::onDestroyView() {
}

void NotebookEdit::onCommentTownTyped(string town) {
	mComment->setTownName(town);
}


void NotebookEdit::onCommentTyped(string comment) {
	mComment->setComment(comment);

	completeComment();
}

void NotebookEdit::completeComment() {

	(new database::XmlDataBase(database::XmlDataBase::DataBaseFileType::COMMENT))->writeComment(mComment);

	getManager()->destroy();
	ViewManager::consoleStartPrivius();
}