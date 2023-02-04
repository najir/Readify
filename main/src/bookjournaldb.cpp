/************************************************************
* Book Journal DataBase Functions
* 
* Insert/Edit/Delete, DB creation
* and initialization.
************************************************************/
#include "bookjournaldb.h"

const char DIR = "../rsc/";

int main() {


}


/******************************
*  Internal DB Calls
******************************/
static int bookjournaldb::createDB(const char dir) {
	sqlite3* DB;
	int exit = 0;

	exit = sqlite3_open(dir, &DB);
	sqlite3_close(DB);

	return 0;
}
static int bookjounaldb::createTable(const char dir) {
	sqlite3* DB;
	std::string sql = "CREATE TABLE IF NOT EXISTS BOOKS("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"NAME			TEXT NOT NULL, "
		"AUTHOR			TEXT NOT NULL, "
		"DESCRIPTION	TEXT, "
		"NOTES			TEXT, "
		"PAGES			INT NOT NULL);";

	try {
		int exit = 0;
		exit = sqlite3(dir, &DB);

		char* messageError;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

		if (exit != SQLITE_OK) {
			std::cerr << "Error Create Table" << endl;
			sqlite3_free(messageError);
		}
		else {
			std::cout << "Table created successfully" << endl;
			sqlite3_close(DB);
		}
		catch (const exception& e) {
			std::cerr << e.what();
		}
	}
}
static int bookjournaldb::insert(const char dir) {
	sqlite3* DB;
	char* messageError;

	int exit = sqlite3_open(dir, &DB);
	std::string sql("INSERT INTO GRADES(NAME, AUTHOR, DESCRIPTION, NOTES, PAGES) VALUES();");
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert" << endl;
		sqlite3_free(messageError);
	}
	else {
		std::cout << "Records created successfully!" << endl;
	}
	return 0;
}


/******************************
* Helper Functions
******************************/
void bookjournaldb::initiateDB() {

}
void bookjournaldb::insertBook() {

}
void bookjournaldb::deleteBook() {

}
void bookjournaldb::editBook() {

}