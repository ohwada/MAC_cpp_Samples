/**
 * sqlitecpp sample
 * 2020-07-01 K.OHWADA
 */


// select records from databese

// reference : https://srombauts.github.io/SQLiteCpp/



// Preparation
// Prepare sample record in database
// % sqlite3 test.db
// sqlite> create table test (id integer primary key, message text);
// sqlite> insert into test (message) values ('Sierra');
// sqlite> insert into test (message) values ('Mojave');
// sqlite> insert into test (message) values ('Catalina');
// sqlite> select * from test;
// sqlite> .exit

// g++ select_record.cpp -std=c++11 `pkg-config --cflags --libs sqlitecpp`

#include <iostream>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>

using namespace std;



int main(void)
{

    string db_name("test.db");
    string tbl_name("test");

try
{
    // Open a database file
   SQLite::Database    db(db_name);

    // Compile a SQL query, containing one parameter (index 1)
    string sql = string("SELECT * FROM ") + tbl_name;
    cout << sql << endl;

    SQLite::Statement   query(db, sql);
    
    // Bind the integer value 6 to the first parameter of the SQL query
    //query.bind(1, 6);
    
    // Loop to execute the query step by step, to get rows of result
    while (query.executeStep())
    {
        // Demonstrate how to get some typed column value
        int id = query.getColumn(0);
        const char* message   = query.getColumn(1);
        //int         size    = query.getColumn(2);
        
        std::cout << "row: " << id << ", " << message << std::endl;
    }

}
catch (std::exception& e)
{
    std::cout << "exception: " << e.what() << std::endl;
    return EXIT_FAILURE;
}

    return EXIT_SUCCESS;
}


// SELECT * FROM test
// row: 1, Sierra
// row: 2, Mojave
// row: 3, Catalina

