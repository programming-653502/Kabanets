#pragma once
#include "model.h"

#include <string>
#include <vector>

#define DEFAULT_FILE_NAME "database.txt"
#define TOWNS_FILE_NAME "towns_database.txt"
#define PLACES_SIGHTS_FILE_NAME "places_sights_database.txt"
#define COMMENT_FILE_NAME "comment_database.txt"

#define PLACE_TAG "place"
#define SIGHT_TAG "sight"
#define COMMENT_TAG "comment"

#define ID_TAG "id"
#define TOWN_TAG "town"
#define TOWNID_TAG "townId"
#define TYPE_TAG "type"
#define NAME_TAG "name"
#define ADRESS_TAG "adress"
#define OPENTIME_TAG "open_time"
#define CLOSETIME_TAG "close_time"
#define ADDTIONS_TAG "additions"
#define TOWNNAME_TAG "townName"

using namespace std;
using namespace model;

namespace database {
	class XmlDataBase;
}

class database::XmlDataBase {

public:

	enum DataBaseFileType { TOWNS, PLACES_SIGHTS, COMMENT };

	XmlDataBase();
	XmlDataBase(string);
	XmlDataBase(DataBaseFileType);
	~XmlDataBase();

	void writePlace(Place*, string);
	void writeSight(Sight*, string);

	vector<Place*> getPlaces(string);
	vector<Sight*> getSights(string);

	void writeTown(Town*);
	vector<Town*> getTowns();

	void writeComment(Comment*);
	vector<Comment*> getComment();

private:
	string mFileName;
};