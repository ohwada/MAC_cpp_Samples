/**
 *  assert.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ assert.cpp
//reference : https://cpprefjp.github.io/reference/cassert/assert.html

#include <cassert>


/**
 *  f
 */
void f(int x)
{
// parameter x must be positive
  assert(x >= 0);

  // …processing with x…
}


/**
 *  main
 */
int main()
{
    f(3);  // OK

// program terminates abnormally
    f(-1); 

	return 0;
}

// Assertion failed: (x >= 0), function f, file assert.cpp, line 18.


