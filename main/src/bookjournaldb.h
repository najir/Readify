#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../dep/sqlite3.h"

struct dbStruct {
	int ID = 0;
	std::string NAME;
	std::string AUTHOR;
	std::string DESCRIPTION;
	std::string NOTES;
	int READ = 0;
	int PAGES = 1;
};

class databaseObject {
private:
	static std::vector<dbStruct> dbCallData;

	int createTable(sqlite3* DB);
	int dbQuery(sqlite3* DB, std::string query, void* dbData);
	static int callBack(void* notUsed, int colNumber, char** rowFields, char** colNames);
	static int callBackGetAll(void* notUsed, int colNumber, char** rowFields, char** colNames);
public:
	int createDB(sqlite3* DB);
	int deleteDB(sqlite3* DB);
	void insertBook(sqlite3* DB, dbStruct data);
	void deleteBook(sqlite3* DB, int ID, std::string bookName);
	void updateBook(sqlite3* DB, dbStruct data, std::string tempName);
	dbStruct getBook(sqlite3* DB, int ID, std::string bookName);
	std::vector<dbStruct> getAllBooks(sqlite3* DB);

};
