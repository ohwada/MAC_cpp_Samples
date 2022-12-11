/**
 * soci_sqlite.cpp
 * 2022-06-01 K.OHWADA
 */


// reference : http://soci.sourceforge.net/doc/master/backends/sqlite3/


#include <iostream>
#include <string>
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>
#include <soci/version.h>

using namespace std;


/**
 * main
 */
int main()
{

    cout << "SOCI_LIB_VERSION : " << SOCI_LIB_VERSION << endl;

     soci::session sql( soci::sqlite3, "test.db");

    int count;
    string query1("select count(*) from testtable");

    sql <<  query1, soci::into(count);

    cout <<  query1 << endl;
    cout << "count: " << count << endl;

    string name;
    string query2("select name from  testtable where id = :id");

    cout <<  query2 << endl;

for(int id=1; id<=count; id++)
{
    sql << query2, soci::use(id, "id"), soci::into(name);

    cout << "id: " << id<< ", name: " << name << endl;
} // for

    return 0;
}

// select count(*) from testtable
// count: 3
// select name from  testtable where id = :id
// id: 1, name: aaa
// id: 2, name: bbb
// id: 3, name: ccc

