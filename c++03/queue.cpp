/**
 *  queue.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ queue.cpp
// refeerence : https://cpprefjp.github.io/reference/queue/queue.html

#include <iostream>
#include <queue>


/**
 *  main
 */
int main()
{
  std::queue<int> que;

  // add element
  que.push(1);
  que.push(2);
  que.push(3);

  while (!que.empty()) 
{
// refer to the first element
    std::cout << que.front() << " ";
// remove first element
    que.pop();
  } // while
    std::cout << std::endl;

    return 0;
}

// 1 2 3 


