/************************************************************
* Book Journal DataBase Functions
* 
* Insert/Edit/Delete, DB creation
* and initialization.
************************************************************/
#include "bookjournaldb.h"

const char* DIR = "../rsc/bookDB.db";

int main() {


}

/******************************
*  Internal DB Calls
******************************/
int createDB(sqlite3* DB) {
	int status = 0;
	char* messageError;

	try {
		status = sqlite3_open(DIR, &DB);
		if (status != SQLITE_OK) {
			std::cerr << "Error Open DB" << std::endl;
			sqlite3_free(messageError);
		}
		else {
			std::cout << "DB Opened successfully" << std::endl;
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what();
	}

	return 0;
}
int deleteDB(sqlite3* DB) {
	sqlite3_close(DB);
	return 0;
}
int createTable(sqlite3* DB) {
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
			std::cerr << "Error Create Table" << std::endl;
			sqlite3_free(messageError);
		}
		else {
			std::cout << "Table created successfully" << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
	return 0;
}
int callBack(void* dbData, int colNumber, char** colFields, char** colNames, std::vector<dbStruct>* dbVector) {
	int i;
	dbStruct* returnData = (dbStruct*)dbData;
	if (colNumber > 1) {							// If getAll is called
	
	}
	for (i = 0; i < colNumber; i++) {
		if (strcmp(colNames[i], 'PAGES') == 0) {
			returnData->PAGES = atoi(colFields[i])
		}
		else if (strcmp(colNames[i], 'ID') == 0) {
			returnData->ID = atoi(colFields[i])
		}
		else if (stcmp(colNames[i], 'READ?') == 0) {
			returnData->READ = atoi(colFields[i])
		}
	}
	if(dbVector){
		dbVector.push_back(returnData);
	}
	return 0;
}
int dbQuery(sqlite3* DB, std::string query, void* dbData, std::vector<dbStruct>* dbVector) {
	int status = 0;
	char* messageError;

	try {
		status = sqlite3_exec(DB, query.c_str(), callBack(), &dbData, &messageError);
		if (status != SQLITE_OK) {
			std::cerr << "Query Error" << std::endl;
			sqlite3_free(messageError);
		}
		else {
			std::cout << "Query Successfully passed!" << std::endl;
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
sqlite3* initiateDB() {
	sqlite3* DB;
	createDB(&DB);
	createTable(&DB);
	
	return DB;
}
void finalizeDB(sqlite3* DB) {
	deleteDB(DB)
}
void insertBook(sqlite3* DB, dbStruct data) {
	std::string insertQuery = "INSERT INTO BOOKS(NAME, AUTHOR, DESCRIPTION, NOTES, READ?, PAGES) VALUES(";		
	insertQuery += data.NAME + ', ';
	insertQuery += data.AUTHOR + ', ';
	insertQuery += data.DESCRIPTION + ', ';
	insertQuery += data.NOTES + ', ';
	insertQuery += data.READ + ', ';
	insertQuery += data.PAGES + ');';

	dbQuery(DB, insertQuery);

}
void deleteBook(sqlite3* DB, int ID, std::string bookName) {
	std::string deleteQuery = "DELETE FROM BOOKS WHERE ";
	if (ID) { deleteQuery += "ID = " + ID; }
	else if (bookName) { deleteQuery += "NAME = bookName" + ID; }

	dbQuery(DB, deleteQuery);
}
void updateBook(sqlite3* DB, dbStruct data, std::string tempName) {
	int idValue = 0;
	std::string updateSearch = "";

	//Need to get id of bookname location then use that value for WHERE
	dbQuery(DB, updateSearch, NULL, NULL);

	std::string updateQuery = "UPDATE BOOKS SET(NAME, AUTHOR, DESCRIPTION, NOTES, READ?, PAGES) WHERE(";
	updateQuery += "NAME = " + data.NAME;
	updateQuery += "AUTHOR = " + data.AUTHOR;
	updateQuery += "NOTES = " + data.NOTES;
	updateQuery += "READ? = " + data.READ;
	updateQuery += "PAGES = " + data.PAGES;
	updateQuery += ") WHERE ID = " + idValue;

	dbQuery(DB, updateQuery, NULL, NULL);

}
std::vector<dbStruct> getBook(sqlite3* DB, int ID, std::string bookName) {
	dbStruct returnData;
	std::string getQuery = "SELECT * FROM BOOKS WHERE ";
	if (ID) { getQuery += "ID = " + ID; }
	else if (bookName) { getQuery += "NAME = " + bookName; }
	
	dbQuery(DB, getQuery, &returnData);


}
std::vector<dbStruct> getAllBooks(sqlite3* DB) {
	dbStruct returnData;
	std::vector<dbStruct> dbVector;
	std::string getAllQuery = "SELECT * FROM BOOKS";

	dbQuery(DB, getAllQuery, &returnData, &dbVector);

}