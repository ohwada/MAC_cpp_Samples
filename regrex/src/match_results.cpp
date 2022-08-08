/**
 * match_results.cpp 
 * 2022-06-01 K.OHWADA
 */

// g++ match_results.cpp -std=c++11

// reference : https://cpprefjp.github.io/reference/regex/match_results.html

#include <iostream>
#include <regex>


/**
 * main
 */
int main()
{
  const char s[] = "The C++11 is very cool!!";
  const std::regex re("(\\w+) is (\\w+)");

  std::cmatch m;
  if (std::regex_search(s, m, re)) {
    std::cout << "ready = " << std::boolalpha << m.ready() << ", empty = " << m.empty() << std::endl << std::endl;
    std::cout << "prefix:'" << m.prefix() << '\'' << std::endl;
    for (std::size_t i = 0, n = m.size(); i < n; ++i) {
      std::cout << i << ":'" << m.str(i) << "\', position = " << m.position(i) << ", length = " << m.length(i) << std::endl;
    }
    std::cout << "suffix:'" << m.suffix() << '\'' << std::endl << std::endl;
    std::cout << m.format("$`14 is $2$'") << std::endl;
  } else {
    std::cout << "not match" << std::endl;
  }
}


// ready = true, empty = false
// prefix:'The C++'
// 0:'11 is very', position = 7, length = 10
// 1:'11', position = 7, length = 2
// 2:'very', position = 13, length = 4
// suffix:' cool!!'
// The C++14 is very cool!!


