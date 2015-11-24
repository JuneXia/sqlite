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

	int cols;
	sqlite3_stmt *stmt;
	const char* tail = NULL;
	const char* sql = "select * from emp;";

	printf("sql = %s\n", sql);
	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail);
	printf("after sqlite3_prepare_v2() called, rc = %d, tail = |%s|, tail = %p, *tail = %d\n", rc, tail, tail, *tail);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
	}
	
	printf("name = %d\n", sqlite3_column_type(stmt, 0));
	printf("name = %d\n", sqlite3_column_type(stmt, 1));
	printf("name = %d\n", sqlite3_column_type(stmt, 2));
	cols = sqlite3_column_count(stmt);
	rc = sqlite3_step(stmt);
	while(rc == SQLITE_ROW)
	{
		int i;
		for (i = 0; i < cols; i++)
		{
			printf("%s    ", sqlite3_column_text(stmt, i));
		}
		printf("\n");
		rc = sqlite3_step(stmt);
	}
	





	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	rc = sqlite3_step(stmt);
	while(rc == SQLITE_ROW)
	{
		int i;
		for (i = 0; i < cols; i++)
		{
			printf("%s    ", sqlite3_column_text(stmt, i));
		}
		printf("\n");
		rc = sqlite3_step(stmt);
	}




	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return 0;
}

int main2()
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

	int cols;
	sqlite3_stmt *stmt;
	const char* tail = NULL;
	//const char* sql = "create table emp(id, name);select * from emp;";
	const char* sql = "select * from emp;select * from emp where name like 'm%';";

	while (sqlite3_complete(sql))
	{
		printf("sql = %s\n", sql);
		rc = sqlite3_prepare_v2(db, sql, -1, &stmt, &tail);
		printf("after sqlite3_prepare_v2() called, rc = %d, tail = |%s|, tail = %p, *tail = %d\n", rc, tail, tail, *tail);
		if( rc != SQLITE_OK )
		{
			fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
		}
		
		cols = sqlite3_column_count(stmt);
		rc = sqlite3_step(stmt);
		while(rc == SQLITE_ROW)
		{
			int i;
			for (i = 0; i < cols; i++)
			{
				printf("%s    ", sqlite3_column_text(stmt, i));
			}
			printf("\n");
			rc = sqlite3_step(stmt);
		}
		if (sql == tail)
		{
			printf("please check you sql!\n");
			break;
		}
		else
		{
			sql = tail;
		}
		printf("\n\n");
	}
	
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return 0;
}

int main_()
{
	printf("%d\n", sqlite3_complete("select * from emp;")); // output 1
	printf("%d\n", sqlite3_complete(";")); // output 1
	printf("%d\n", sqlite3_complete("fuck you;")); // output 1
	printf("%d\n", sqlite3_complete("select * from emp")); // output 0
	printf("%d\n", sqlite3_complete("select * from emp\0;")); // output 0
	
	return 0;
}
