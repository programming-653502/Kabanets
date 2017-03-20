#pragma once
#include "database.h"
#include "vector"
#include "model.h"

using namespace std;

using namespace model;
using namespace database;

namespace database {
	class ProductDataBase;
}

class database::ProductDataBase {

public:

	void addProduct(Product*);
	bool removeProduct(Product*);
	vector<Product*> getProducts();
	int findProduct(Product*);

	void confirmChanges();
	vector<Product*> readProductInDatabase();

private:
	XmlDataBase mDatabase;

	Note* parseProduct(Product*);
	Product* parseNote(Note*);

};