/**
 * soci_mysql.cpp
 * 2022-06-01 K.OHWADA
 */


// reference : http://soci.sourceforge.net/doc/master/backends/mysql/


#include <iostream>
#include <string>
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>
#include <soci/version.h>

using namespace std;


/**
 * main
 */
int main()
{
    cout << "SOCI_LIB_VERSION : " << SOCI_LIB_VERSION << endl;

    string str_conn("db='db_test' user='root' password='' ");

    soci::session sql( soci::mysql, str_conn);

    int count;
    string query1("select count(*) from tb_test");

    sql <<  query1, soci::into(count);

    cout <<  query1 << endl;
    cout << "count: " << count << endl;

    string name;
    string query2("select name from  tb_test where id = :id");

    cout <<  query2 << endl;

for(int id=1; id<=count; id++)
{
    sql << query2, soci::use(id, "id"), soci::into(name);
    cout << id<< " : " << name << endl;
} // for

    return 0;
}

// select count(*) from tb_test
// count: 3
// select name from  tb_test where id = :id
// 1 : aaa
// 2 : bbb
// 3 : ccc

