#include <stdio.h>
#include <sqlite3.h>

static int callback(void *data, int cols, char **vals, char **headers)
{
	int i;  
	printf("callback : ");
	for(i = 0; i < cols; i++)
	{
		printf("%s = %s    ", headers[i], vals[i]);
	}
	printf("\n");
	return 0;
}

int main()
{
	sqlite3 *db;
	char *err_msg = NULL;
	int rc;

	rc = sqlite3_open("./employees.db", &db);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}

	rc = sqlite3_exec(db, "create table emp(id, name);", NULL, NULL, &err_msg);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
	}
	
	rc = sqlite3_exec(db, "insert into emp(id, name) values(1, 'lily');select * from emp;", NULL, NULL, &err_msg);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
	}
	sqlite3_close(db);
	return 0;
}
