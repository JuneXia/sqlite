#include <stdio.h>
#include <sqlite3.h>

int main()
{
	sqlite3 *db;
	int rc;

	rc = sqlite3_open("./employees.db", &db);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}

	sqlite3_stmt *stmt;
	const char* tail = NULL;
	const char* sql = "insert into emp values(?,?);";
	//const char* sql = "insert into emp(name, id) values(?,?);";

	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail);
	printf("after sqlite3_prepare_v2() called, rc = %d, tail = |%s|, tail = %p, *tail = %d\n", rc, tail, tail, *tail);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
	}
	
	sqlite3_bind_int(stmt, 1, 8);
	sqlite3_bind_text(stmt, 2, "toma", -1, SQLITE_STATIC);
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
