#pragma once

#include <iostream>
#include <vector>
#include "../dep/sqlite3.h"


//DataBase interaction Functions
static int createDB(sqlite3* DB);
static int deleteDB();
static int createTable(sqlite3* DB);
static int callBack(void* notUsed, int colNumber, char** rowFields, char** colNames);
static int insert(sqlite3* DB, std::string insertValues);
static int update(sqlite3* DB, int ID, std::string bookName);
static int get(sqlite3* DB, void* dbData, int ID, std::string bookName);
static int getAll(sqlite3* DB, void* dbData);
static int deleteBookDB(sqlite3* DB, int ID, std::string bookName);
static int dbQuery(sqlite3* db, std::string query);


//Helper Functions for GUI
void initiateDB(sqlite3* DB);
void finalizeDB(sqlite3* DB);
void insertBook(sqlite3* DB, std::string bookName, std::string author, std::string bookNotes, bool readValue, int pageNumber);
void deleteBook(int ID, std::string bookName);
void updateBook(int ID, std::string bookName);
void getBook(int ID, std::string bookName);
void getAllBooks(sqlite3* DB);
