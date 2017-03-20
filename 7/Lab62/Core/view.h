#ifndef H_VIEW
#define H_VIEW

#include <vector>

using namespace std;

namespace core {
	struct ViewSize;
	class View;
	class ViewManager;
}

struct core::ViewSize {
public:
	
	long width;
	long height;
	long paddingLeft;
	long paddingRight;
	long paddingTop;
	long paddingBottom;

	bool equals(ViewSize obj)
	{

		ViewSize compare = obj;
		if (compare.width == width && compare.height == height)
		{
			return true;
		}

		return false;
	}
};

class core::ViewManager {

public:

	ViewManager(View*);
	~ViewManager();

	const static ViewSize UNSPECIFIED;

	enum ResizeTypes { SCALE, CROP };

	static long generateId();

	bool isExist(long) const;

	bool isExist(View*) const;

	static bool consoleStartPrivius();

	bool addNewChild(View*);

	enum DestroyType { DESTROYED, WAIT, NOTDESTROYED };
	DestroyType destroy();

	void reattach();

	virtual bool removeView(View* );
	
	virtual View* getView(long) const;

	void setResizeType(ResizeTypes type) {
		mResizeType = type;
	}

	ResizeTypes getResizeType() {
		return mResizeType;
	}

protected:

	View* bindedView;

	ViewSize parentSize;

	vector<View*> viewChildren;

	vector<View*> additionChildList;

	vector<View*> ignoreChildList;

	bool cascadeStart(ViewManager*);

private:

	ResizeTypes mResizeType = ResizeTypes::CROP;

	static long idCreator;
	
	bool isInAttaching = false;
	bool isAttached = false;
	bool waitForDestroying = false;

	void consoleReturnPrevius();

	bool confirmChanges();

	ViewSize resolveSize(ViewSize);

	bool isValidChildrenList(vector<View*>);

	bool resolveCreate();

	bool actualStart();
};


class core::View
{
public:

	View();
	~View();

	virtual ViewManager* getManager();

	void changeSize(long width, long height);
	void addPaddings(long paddingLeft, long paddingTop, long paddingRight, long paddingBottom);

	ViewSize getActualViewSize() {
		return mActualViewSize;
	}

	virtual vector<View*> onCreateView() = 0;
	virtual ViewSize onResizeView(ViewSize size) = 0;
	virtual void onAttachView() = 0;
	virtual void onDestroyView() = 0;

	long getId() {
		return mId;
	}

	bool equals(View* view);

protected:
	ViewManager* mManager = 0;

	ViewSize mStandartSize = ViewManager::UNSPECIFIED;
	ViewSize mActualViewSize = ViewManager::UNSPECIFIED;

	void setStandartSize(ViewSize standartSize) {
		mStandartSize = standartSize;
	}

	ViewSize getStandartSize() {
		return mStandartSize;
	}

private:
	long mId;
};

#endif // !H_VIEW