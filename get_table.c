#include <stdio.h>
#include <sqlite3.h>

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

	char **result = NULL;
	int rows;
	int cols;

	//rc = sqlite3_get_table(db, "create table emp(id, name);", &result, &rows, &cols, &err_msg);
	rc = sqlite3_get_table(db, "create table emp(id, name);", &result, &rows, &cols, &err_msg);
	if (result)
		printf("result[0] = %s, rows = %d, cols = %d\n", result[0], rows, cols);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
	}

	//rc = sqlite3_get_table(db, "select * from emp;", &result, &rows, &cols, &err_msg);
	rc = sqlite3_get_table(db, "insert into emp(id, name) values(1, 'lily');select * from emp;", &result, &rows, &cols, &err_msg);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", err_msg);
		sqlite3_free(err_msg);
	}
	else
	{
		int i, j;	
		printf("rows = %d, cols = %d\n", rows, cols);
		for (i = 0; i < rows; i++)
		{
			for (j = 0; j < cols; j++)
			{
				int n = i*cols + j;
				printf("result[%d] = %s    ", n, result[n]);
			}
			printf("\n");
		}
	}
	sqlite3_close(db);
	return 0;
}
