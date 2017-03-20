#pragma once

#include<string>
#include<vector>

using namespace std;

#define HOTEL_H "Отель"
#define CINEMA_H "Кинотеатр"
#define THEATER_H "Театр"
#define MESEUM_H "Музей"
#define RESTAURANT_H "Ресторан"
#define MONUMENT_H "Памятник"
#define BUILDING_H "Сооружение"

namespace model {
	class InterestingPlace;
	class Place;
	class Sight;
	class Town;
	class Comment;

	enum PlaceType { HOTEL, CINEMA, THEATER, MESEUM, RESTAURANT };
	enum SightType { MONUMENT, BUILDING };
}

class model::InterestingPlace {

public:

	void setName(string name) {
		mName = name;
	}

	void setAdress(string adress) {
		mAdress = adress;
	}

	void setOpenTime(string openTime) {
		mOpenTime = openTime;
	}

	void setCloseTime(string closeTime) {
		mCloseTime = closeTime;
	}

	void setAddtions(string additions) {
		mAdditions = additions;
	}

	string getName() {
		return mName;
	}

	string getAdress() {
		return mAdress;
	}

	string getOpenTime() {
		return mOpenTime;
	}

	string getCloseTime() {
		return mCloseTime;
	}

	string getAddtions() {
		return mAdditions;
	}

private:

	string mName;
	string mAdress;
	string mOpenTime;
	string mCloseTime;
	string mAdditions;

};

class model::Place : public InterestingPlace {

public:

	void setType(PlaceType type) {
		mType = type;
	}

	PlaceType getType() {
		return mType;
	}

private:

	PlaceType mType;

};


class model::Sight : public InterestingPlace {

public:

	void setType(SightType type) {
		mType = type;
	}

	SightType getType() {
		return mType;
	}

private:

	SightType mType;

};

class model::Town {

public:

	Town(string name) {
		mName = name;
	}
	~Town();

	void setName(string name) {
		mName = name;
	}

	string getName() {
		return mName;
	}

	void addPlace(Place* place) {
		mPlaces.push_back(place);
	}

	void setPlaceArray(vector<Place*> places) {
		mPlaces = places;
	}

	vector<Place*> getPlaceArray() {
		return mPlaces;
	}

	void addSight(Sight* sight) {
		mSights.push_back(sight);
	}

	void setSightArray(vector<Sight*> sights) {
		mSights = sights;
	}

	vector<Sight*> getSightArray() {
		return mSights;
	}

	void setId(long id) {
		mId = id;
	}

	long getId() {
		return mId;
	}

private:

	string mName;
	long mId;

	vector<Place*> mPlaces;
	vector<Sight*> mSights;
};

class model::Comment {

public:

	void setTownName(string townName) {
		mTownName = townName;
	}

	string getTownName() {
		return mTownName;
	}

	void setComment(string comment) {
		mComment = comment;
	}

	string getComment() {
		return mComment;
	}

private:

	string mTownName;
	string mComment;
};