/**
 * show_db_test.cpp
 * 2022-06-01 K.OHWADA
 */

// show records in db_test, tb_test using X DevAPI
// reference : https://github.com/mysql/mysql-connector-cpp
// https://dev.mysql.com/doc/x-devapi-userguide/en/

#include <iostream>
#include <string>
#include <mysqlx/xdevapi.h>

using namespace std;
// using namespace ::mysqlx;


/**
 * main
 */
int main(int argc, const char* argv[])
{

    string url("mysqlx://root@127.0.0.1");
    string db_name("db_test");
    string table_name("tb_test");

try {

// connect
  mysqlx::Session sess(url);

// get Schema(DB)
  mysqlx::Schema sch= sess.getSchema(db_name);

// get Table
    mysqlx::Table table = sch.getTable(table_name);

// execute select
    mysqlx::RowResult res = table.select().execute();

// get row list
    std::list<mysqlx::Row> list = res.fetchAll();

    cout << db_name << ", " << table_name << endl;

    for(auto row: list)
    {
        auto id = row.get(0);
        auto name = row.get(1);
        cout << id << " : " << name << endl;
    }

  mysqlx::Collection coll = sch.getCollection(table_name);
// TODO: 
// ERROR: CDK Error: Unknown column 'doc' in collection
  //DocResult docs = coll.find().execute();

}  
catch (const mysqlx::Error &err)
{
  cout <<"ERROR: " <<err <<endl;
  return EXIT_FAILURE;
}
catch (std::exception &ex)
{
  cout <<"STD EXCEPTION: " <<ex.what() <<endl;
  return EXIT_FAILURE;
}
catch (const char *ex)
{
  cout <<"EXCEPTION: " <<ex <<endl;
  return EXIT_FAILURE;
}

  return EXIT_SUCCESS;
}

// db_test, tb_test
// 1 : aaa
// 2 : bbb
// 3 : ccc




