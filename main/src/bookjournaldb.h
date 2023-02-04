#pragma once

#include <iostream>
#include "../dep/sqlite3.h"

static int createDB(const char dir);
static int createTable(const char dir);
static int insert(const char dir);
void initiateDB();
void insertBook();
void deleteBook();
void editBook();
