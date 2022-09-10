/**
 * select.cpp
 * 2022-06-01 K.OHWADA
 */


#include <iostream>
#include <string>
#include "sqlite_modern_cpp.h"
 

/**
 * main
 */
int main(void)
{
    try
   {
    sqlite::database db(R"(test.db)");

     db << "select id,name from testtable"
    >> [&](int id, std::string name) {
            std::cout << id << ' ' << name << std::endl;
      };


   }
   catch (sqlite::sqlite_exception const & e)
   {
      std::cerr << e.get_code() << ": " << e.what() << " during "
                << e.get_sql() << std::endl;
   }
   catch (std::exception const & e)
   {
      std::cerr << e.what() << std::endl;
   }

    return 0;
}

// 1 aaa
// 2 bbb
// 3 ccc

