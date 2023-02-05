#pragma once

#include <iostream>
#include "../dep/sqlite3.h"


//DataBase interaction Functions
static int createDB(const char dir);
static int finalizeDB();
static int createTable(const char dir);
static int callBack(void* notUsed, int colNumber, char** rowFields, char** colNames);
static int insert(const char dir);
static int update(const char dir);
static int get(const char dir, int ID, std::string bookName);
static int getAll(const char dir);


//Helper Functions for GUI
void initiateDB();
void finalizeDB();
void insertBook();
void deleteBook();
void updateBook();
void getBook(int ID, std::string bookName);
void getAllBooks();
