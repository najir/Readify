#pragma once

#include <iostream>
#include "../dep/sqlite3.h"


//DataBase interaction Functions
static int createDB(const char dir);
static int createTable(const char dir);
static int insert(const char dir);
static int get(const char dir, int ID, std::string bookName);
static int getAll(const char dir);


//Helper Functions for GUI
void initiateDB();
void insertBook();
void deleteBook();
void editBook();
void getBook(int ID, std::string bookName);
void getAllBooks();
