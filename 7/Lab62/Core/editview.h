#ifndef H_EDITVIEW
#define H_EDITVIEW

#include "funcview.h"

#include <functional>
#include <queue>

using namespace core;

namespace core {
	class EditView;

	typedef std::function<void(string)> AnswerTypedCallback;
	
	class Correct;
	class IntCorrect;
	class DoubleCorrect;
	class StringEmptyCorrect;
}


class core::EditView : public FuncView {

public:

	EditView();

	void onAttachView() override;
	vector<View*> onCreateView() override;
	void onDestroyView() override;
	ViewSize onResizeView(ViewSize) override;

	void setOnAnswerTypedCallback(AnswerTypedCallback callback) {
		onAnswerTypedCallback = callback;
	}

	void setCorrectChecking(Correct*);
	void setCorrectChecking(queue<Correct*>);

private:
	AnswerTypedCallback onAnswerTypedCallback;
	
	queue<Correct*> correctAnswerCallbacks;
};

class core::Correct
{

public:

	virtual bool isCorrect(void*) = 0;
	virtual string getDescription() = 0;
};

class core::IntCorrect : public Correct
{
public:

	IntCorrect();

	string getDescription() override;
	bool isCorrect(void*) override;

};

class core::DoubleCorrect : public Correct
{
public:

	string getDescription() override;
	bool isCorrect(void*) override;

};

class core::StringEmptyCorrect : public Correct
{
public:

	string getDescription() override;
	bool isCorrect(void*) override;

};

#endif //!EDITVIEW