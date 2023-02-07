/************************************************************
* Book Journal DataBase Functions
* 
* Insert/Edit/Delete, DB creation
* and initialization.
************************************************************/
#include "bookjournaldb.h"

const char DIR = "../rsc/bookDB.db";

int main() {


}


/******************************
*  Internal DB Calls
******************************/
static int bookjournaldb::createDB(sqlite3* DB) {
	int status = 0;

	try {
		status = sqlite3_open(DIR, DB);
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
static int bookjournaldb::deleteDB(sqlite3* DB) {
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
		"READ?			BOOL, "	
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
static int bookjounraldb::callBack(void* dbData, int colNumber, char** rowFields, char** colNames) {

}
static int bookjournaldb::dbQuery(sqlite3* db, std::string query) {
	int status = 0;
	char* messageError;

	try {
		status = sqlite3_exec(DB, query.c_str(), callBack , 0, &messageError);
		if (status != SQLITE_OK) {
			std::cerr << "Query Error" << endl;
			sqlite3_free(messageError);
		}
		else {
			std::cout << "Query Successfully passed!" << endl;
		}
	}
	catch (const exception& e) {
		std::cerr << e.what();
	}
	return 0;

}

/******************************
* Helper Functions
* 
* Abstraction Layer that processes query info and manages returned data if needed.
******************************/
sqlite3* bookjournaldb::initiateDB() {
	sqlite3* DB;
	createDB(&DB);
	createTable(&DB);
	
	return DB;
}
void bookjournaldb::finalizeDB(sqlite3* DB) {
	deleteDB(DB)
}
void bookjournaldb::insertBook(sqlite3* DB, std::string bookName, std::string author, std::string bookNotes, bool readValue, int pageNumber) {
	std::string insertQuery = "INSERT INTO BOOKS(NAME, AUTHOR, DESCRIPTION, NOTES, READ?, PAGES) VALUES(";		
	insertQuery += bookName + ', ';
	insertQuery += author + ', ';
	insertQuery += bookNotes + ', ';
	insertQuery += readValue + ', ';
	insertQuery += pageNumber + ');';

	dbQuery(DB, insertQuery);

}
void bookjournaldb::deleteBook(sqlite3* DB, int ID, std::string bookName) {
	std::string deleteQuery = "DELETE FROM BOOKS WHERE ";
	if (ID) { deleteQuery += "ID = " + ID; }
	else if (bookName) { deleteQuery += "NAME = bookName" + ID; }

	dbQuery(DB, deleteQuery);
}
void bookjournaldb::updateBook(sqlite3* DB, int ID, std::string bookName, std::string author, std::string bookNotes, bool readValue, int pageNumber) {
	int idValue = 0;
	std::string updateSearch = "";

	//Need to get id of bookname location then use that value for WHERE
	dbQuery(DB, updateSearch);

	std::string updateQuery = "UPDATE BOOKS SET NAME, AUTHOR, DESCRIPTION, NOTES, READ?, PAGES) WHERE(";
	updateQuery += 'NAME = ' + bookName;
	updateQuery += 'AUTHOR = ' + author;
	updateQuery += 'NOTES = ' + bookNotes;
	updateQuery += 'READ? = ' + readValue;
	updateQuery += 'PAGES = ' + pageNumber;
	updateQuery += " WHERE ID = " + idValue;

	dbQuery(DB, updateQuery);

}
std::string bookjournaldb::getBook(sqlite3* DB, int ID, std::string bookName) {
	std::string getQuery = "SELECT * FROM BOOKS WHERE ";
	if (ID) { getQuery += "ID = " + ID; }
	else if (bookName) { getQuery += "NAME = " + bookName; }
	
	dbQuery(DB, getQuery);


}
std::string bookjournaldb::getAllBooks(sqlite3* DB) {
	std::string getAllQuery = "SELECT * FROM BOOKS";

	dbQuery(DB, getAllQuery);

}