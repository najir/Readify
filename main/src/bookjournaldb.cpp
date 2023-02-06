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
	int status = 0;

	try {
		status = sqlite3_open(dir, &DB);
		if (status != SQLITE_OK) {
			std::cerr << "Error Open DB" << endl;
			sqlite3_free(messageError);
		}
		else {
			std::cout << "DB Opened successfully" << endl;
		}
	}
	catch (exception& e) {
		std::cerr << e.what();
	}

	return 0;
}
static int bookjournaldb::finalizeDB(sqlite3* DB) {
	sqlite3_close(DB);
}
static int bookjounaldb::createTable(sqlite3* DB) {
	int status = 0;
	char* messageError;
	std::string sql = "CREATE TABLE IF NOT EXISTS BOOKS("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"NAME			TEXT NOT NULL, "
		"AUTHOR			TEXT NOT NULL, "
		"DESCRIPTION	TEXT, "
		"NOTES			TEXT, "
		"PAGES			INT NOT NULL);";

	try {
		status = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

		if (status != SQLITE_OK) {
			std::cerr << "Error Create Table" << endl;
			sqlite3_free(messageError);
		}
		else {
			std::cout << "Table created successfully" << endl;
		}
	}
	catch (const exception& e) {
		std::cerr << e.what();
	}
	return 0;
}
static int bookjounraldb::callBack(void* notUsed, int colNumber, char** rowFields, char** colNames) {

}
static int bookjournaldb::insert(sqlite3* DB) {
	int status = 0;
	char* messageError;
	std::string sql("INSERT INTO BOOKS(NAME, AUTHOR, DESCRIPTION, NOTES, PAGES) VALUES();");

	try {
		status = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (status != SQLITE_OK) {
			std::cerr << "Error Insert" << endl;
			sqlite3_free(messageError);
		}
		else {
			std::cout << "Records created successfully!" << endl;
		}
	}
	catch (const exception& e) {
		std::cerr << e.what();
	}
	return 0;
}
static int bookjournaldb::update(sqlite3* DB) {
	int status = 0;
	char* messageError;
	std::string sql("UPDATE BOOKS SET BOOK - ???");

	try {
		status = sqlite3_exec(DB, sql.c_str(), callBack, NULL, &messageError);
		if (status != SQLITE_OK) {
			std::cerr << "Error Update" << endl;
			sqlite3_free(messageError);
		}
		else {
			cout << "Record updated successfully!" << endl;
		}
	}
	catch (const exception& e) {
		std::cerr << e.what();
	}
	return 0;
}
static int bookjournaldb::get(sqlite3* DB, int ID, std::string bookName) {
	int status = 0;
	char* messageError;
	std::string sql("");

	try {
		if (bookName) {

		}
		else if (ID) {

		}
	}
	catch (const exception& e) {
		std::cerr << e.what();
	}
	return 0;
};
static int bookjournaldb::getAll(sqlite3* DB) {
	int status = 0;
	char* messageError;
	std::string sql = "SELECT * FROM BOOKS;";

	try {
		status = sqlite3_exec(DB, sql.c_str(), bookjournaldb::callBack, NULL, &messageError);
		if (status != SQLITE_OK) {
			std::cerr << "Error Get" << endl;
			sqlite3_free(messageError);
		}
		else {
			std::cout << "Records retrieved successfully!" << endl;
		}
	}
	catch (const exception& e) {
		std::cerr << e.what();
	}
	return 0;
};
static int bookjournaldb::deleteBook(const char dir, int ID, std::string bookName) {
	int status = 0;
	char* messageError;
	std::string sql = "";

	try {
		if (bookName) {
			std::string sql = "";
		}
		else if (ID) {
			std::string sql = "";
			status = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &messageError)
		}
	}
	catch (const exception& e) {
		std::cerr << e.what();
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
void bookjournaldb::deleteBook(int ID, std::string bookName) {

}
void bookjournaldb::updateBook(int ID, std::string bookName) {

}
void bookjournaldb::getBook(int ID, std::string bookName) {

}
void bookjournaldb::getAllBooks() {

}
void bookjournaldb::finalizeDB() {

}
