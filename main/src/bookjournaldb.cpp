#include "bookjournaldb.h"

const char DIR = "../rsc/";

int main() {


}

static int bookjournaldb::createDB(const char s) {
	sqlite3* DB;
	int exit = 0;

	exit = sqlite3_open(s, &DB);
	sqlite3_close(DB);

	return 0;
}
static int bookjounaldb::createTable(const char s) {
	sqlite3* DB;
	string sql = "CREATE TABLE IF NOT EXISTS BOOKS("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"NAME			TEXT NOT NULL, "
		"AUTHOR			TEXT NOT NULL, "
		"DESCRIPTION	TEXT, "
		"NOTES			TEXT, "
		"PAGES			INT NOT NULL);";

}