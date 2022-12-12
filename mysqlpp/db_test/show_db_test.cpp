/**
 * show_db_test.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://github.com/tangentsoft/mysqlpp/blob/trunk/examples/simple1.cpp

#include <iostream>
#include <iomanip>
#include <mysql++.h>


using namespace std;


/**
 * main
 */
int main(int argc, char *argv[])
{
	// Get database access parameters from command line
	// mysqlpp::examples::CommandLine cmdline(argc, argv);

	// Connect to the sample database.
	mysqlpp::Connection conn(false);
    string db_name("db_test");
	string server("localhost");
    string user("root");
    string pass("");

	string str_query("select id, name from tb_test");

	auto ret1 = conn.connect (db_name.c_str(), server.c_str(), user.c_str(), pass.c_str() );

	if ( ret1 ) {
		// Retrieve a subset of the sample stock table set up by resetdb
		// and display it.
		mysqlpp::Query query = conn.query(str_query);

		mysqlpp::StoreQueryResult res = query.store();

		if (res) {
			cout << "show " << db_name << ", tb_test" << endl;
			mysqlpp::StoreQueryResult::const_iterator it;
			for (it = res.begin(); it != res.end(); ++it) {
				mysqlpp::Row row = *it;
// id : name
				cout << row[0] << " : "<< row[1] << endl;
			}
		}
		else {
			cerr << "Failed to get item list: " << query.error() << endl;
			return EXIT_FAILURE;
		}

	}
	else {
		cerr << "DB connection failed: " << conn.error() << endl;
		 return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}


// 1 : aaa
// 2 : bbb
// 3 : ccc

