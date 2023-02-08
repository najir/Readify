#pragma once

#include <iostream>
#include <vector>
#include "../dep/sqlite3.h"

struct dbStruct {
	int ID;
	std::string NAME;
	std::string AUTHOR;
	std::string DESCRIPTION;
	std::string NOTES;
	bool READ;
	int PAGES;
};

//DataBase interaction Functions
int createDB(sqlite3* DB);
int deleteDB(sqlite3* DB);
int createTable(sqlite3* DB);
int callBack(void* notUsed, int colNumber, char** rowFields, char** colNames, std::vector<dbStruct>* dbVector);
int dbQuery(sqlite3* DB, std::string query, void* dbData, std::vector<dbStruct>* dbVector);


//Helper Functions for GUI
void initiateDB();
void finalizeDB(sqlite3* DB);
void insertBook(sqlite3* DB, dbStruct data);
void deleteBook(sqlite3* DB, int ID, std::string bookName);
void updateBook(sqlite3* DB, dbStruct data);
void getBook(sqlite3* DB, int ID, std::string bookName);
void getAllBooks(sqlite3* DB);
