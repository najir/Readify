/************************************************************
* Book Journal DataBase Functions
* 
* Insert/Edit/Delete, DB creation
* and initialization.
************************************************************/
#include "bookjournaldb.h"

const char* DIR = "./db/bookDB.db";
std::vector<dbStruct> databaseObject::dbCallData;

/******************************
*  Internal DB Calls
******************************/
int databaseObject::createDB(sqlite3* DB) {
	int status = 0;

	try {
		status = sqlite3_open(DIR, &DB);
		if (status != SQLITE_OK) {
			std::cerr << "Error Open DB" << std::endl;
		}
		else {
			std::cout << "DB Opened successfully" << std::endl;
		}
	}
	catch (std::exception& e) {
		std::cerr << e.what();
	}
	sqlite3_close(DB);
	createTable(DB);
	return 0;
}
int databaseObject::deleteDB(sqlite3* DB) {
	sqlite3_close(DB);
	return 0;
}
int databaseObject::createTable(sqlite3* DB) {
	int status = 0;
	char* messageError;
	sqlite3_open(DIR, &DB);
	const char* sql = "CREATE TABLE IF NOT EXISTS BOOKS ("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"NAME			TEXT, "
		"AUTHOR			TEXT, "
		"DESCRIPTION	TEXT, "
		"NOTES			TEXT, "
		"READ			INT, "	
		"PAGES			INT);";

	try {
		status = sqlite3_exec(DB, sql, NULL, NULL, &messageError);

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
	sqlite3_close(DB);
	return 0;
}
int databaseObject::callBack(void* dbData, int colNumber, char** colFields, char** colNames) {
	int i;
	dbStruct* data = (dbStruct*)dbData;

	for (i = 0; i < colNumber; i++) {
		if (strcmp(colNames[i], "PAGES") == 0) {
			data->PAGES = atoi(colFields[i]);
		}
		//else if (strcmp(colNames[i], "ID") == 0) {
			//data->ID = atoi(colFields[i]);
		//}
		else if (strcmp(colNames[i], "READ?") == 0) {
			data->READ = atoi(colFields[i]);
		}
		else if (strcmp(colNames[i], "NAME") == 0) {
			data->NAME = colFields[i];
		}
		else if (strcmp(colNames[i], "AUTHOR") == 0) {
			data->AUTHOR = colFields[i];
		}
		else if (strcmp(colNames[i], "NAME") == 0) {
			data->DESCRIPTION = colFields[i];
		}
		else if (strcmp(colNames[i], "AUTHOR") == 0) {
			data->NOTES = colFields[i];
		}
	}
	return 0;
}
int databaseObject::callBackGetAll(void* dbData, int colNumber, char** colFields, char** colNames) {
	int i;
	dbStruct* data = (dbStruct*)dbData;

	for (i = 0; i < colNumber; i++) {
		if (strcmp(colNames[i], "PAGES") == 0) {
			data->PAGES = atoi(colFields[i]);
		}
		else if (strcmp(colNames[i], "ID") == 0) {
			data->ID = atoi(colFields[i]);
		}
		else if (strcmp(colNames[i], "READ") == 0) {
			data->READ = atoi(colFields[i]);
		}
		else if (strcmp(colNames[i], "NAME") == 0) {
			data->NAME = colFields[i];
		}
		else if (strcmp(colNames[i], "AUTHOR") == 0) {
			data->AUTHOR = colFields[i];
		}
	}
	dbCallData.push_back(*data);
	return 0;
}
int databaseObject::dbQuery(sqlite3* DB, std::string query, void* dbData) {
	int status = 0;
	char* messageError;

	try {
		status = sqlite3_open(DIR, &DB);
		if (status != SQLITE_OK) {
			std::cerr << "Query Error" << std::endl;
		}
		else {
			std::cout << "Query Successfully passed!" << std::endl;
		}

		status = sqlite3_exec(DB, query.c_str(), callBack, dbData, &messageError);
		if (status != SQLITE_OK) {
			std::cerr << "Query Error" << std::endl;
			sqlite3_free(messageError);
		}
		else {
			std::cout << "Query Successfully passed!" << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
	sqlite3_close(DB);
	return 0;
}

/******************************
* Helper Functions
* 
* Abstraction Layer that processes query info and manages returned data if needed.
******************************/
void databaseObject::insertBook(sqlite3* DB, dbStruct data) {
	std::string insertQuery = "INSERT INTO BOOKS(NAME, AUTHOR, DESCRIPTION, NOTES, READ, PAGES) VALUES(";
	insertQuery += "'" + data.NAME + "', ";
	insertQuery += "'" + data.AUTHOR + "', ";
	insertQuery += "'" + data.DESCRIPTION + "', ";
	insertQuery += "'" + data.NOTES + "', ";	
	insertQuery += "'" + std::to_string(data.READ) + "', ";
	insertQuery += "'" + std::to_string(data.PAGES) + "');";

	dbQuery(DB, insertQuery, NULL);
}
void databaseObject::deleteBook(sqlite3* DB, int ID, std::string bookName) {
	std::string deleteQuery = "DELETE FROM BOOKS WHERE ";
	if (ID) { deleteQuery += "ID = " + ID; }
	else if (!bookName.empty()) { deleteQuery += "NAME = bookName" + ID; }

	dbQuery(DB, deleteQuery, NULL);
}
void databaseObject::updateBook(sqlite3* DB, dbStruct data, std::string tempName) {
	int idValue = 0;
	std::string updateSearch = "";

	//Need to get id of bookname location then use that value for WHERE
	dbQuery(DB, updateSearch, NULL);

	std::string updateQuery = "UPDATE BOOKS SET(NAME, AUTHOR, DESCRIPTION, NOTES, READ?, PAGES) WHERE(";
	updateQuery += "NAME = " + data.NAME;
	updateQuery += "AUTHOR = " + data.AUTHOR;
	updateQuery += "NOTES = " + data.NOTES;
	updateQuery += "READ? = " + data.READ;
	updateQuery += "PAGES = " + data.PAGES;
	updateQuery += ") WHERE ID = " + idValue;

	dbQuery(DB, updateQuery, NULL);

}
dbStruct databaseObject::getBook(sqlite3* DB, int ID, std::string bookName) {
	dbStruct returnData;
	std::string getQuery = "SELECT * FROM BOOKS WHERE ID = " + bookName + ";";

	dbQuery(DB, getQuery, &returnData);
	return returnData;
}
std::vector<dbStruct> databaseObject::getAllBooks(sqlite3* DB) {
	int status = 0;
	char* messageError;
	dbStruct returnData;
	std::vector<dbStruct> returnVector;
	dbStruct dbData;
	std::string query = "SELECT * FROM BOOKS";

	try {
		status = sqlite3_open(DIR, &DB);
		if (status != SQLITE_OK) {
			std::cerr << "Query Error" << std::endl;
		}
		else {
			std::cout << "Query Successfully passed!" << std::endl;
		}
		status = sqlite3_exec(DB, query.c_str(), callBackGetAll, &dbData, &messageError);
		if (status != SQLITE_OK) {
			std::cerr << "Query Error" << std::endl;
			sqlite3_free(messageError);
		}
		else {
			std::cout << "Query Successfully passed!" << std::endl;
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}
	returnVector = dbCallData;
	dbCallData.clear();
	sqlite3_close(DB);

	return returnVector;
}