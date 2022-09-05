/**
 *  stack.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ stack.cpp
// reference : https://cpprefjp.github.io/reference/stack/stack.html

#include <iostream>
#include <stack>


/**
 *  main
 */
int main ()
{
  std::stack<int> st;


// add element
  st.push(1);
  st.push(2);
  st.push(3);

  while (!st.empty()) 
{
// refers to the trailing element
    std::cout << st.top() << " ";
// remove trailing element
    st.pop();
  } // while
    std::cout << std::endl;

    return 0;
}

// 3 2 1 

