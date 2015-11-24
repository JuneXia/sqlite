#include <stdio.h>
#include <sqlite3.h>

int main()
{
	sqlite3 *db;
	int rc = sqlite3_open("./employees.db", &db);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}

	sqlite3_stmt *stmt;
	const char * tail = NULL;
	const char * sql = "select id from emp where id = ?;select name from emp where id = ?;";
	//const char * sql = "select * from emp where name = ?;";

	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail);
	printf("after sqlite3_prepare_v2() called, rc = %d, tail = |%s|, tail = %p, *tail = %d\n", rc, tail, tail, *tail);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
	}
	sqlite3_bind_int(stmt, 1, 3);
	//sqlite3_bind_text(stmt, 1, "tom", -1, SQLITE_STATIC);
	
	rc = sqlite3_step(stmt);
	int cols = sqlite3_column_count(stmt);
	printf("rc = %d\n", rc);
	while(rc == SQLITE_ROW)
	{
		int i;
		for (i = 0; i < cols; i++)
		{
			printf("%s    ", sqlite3_column_text(stmt, i));
			//printf("%d    ", sqlite3_column_int(stmt, i));
		}
		printf("step once\n");
		rc = sqlite3_step(stmt);
		printf("rc = %d\n", rc);
	}
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
