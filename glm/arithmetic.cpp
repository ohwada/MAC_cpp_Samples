/**
 * glm samples
 * 2020-03-01 K.OHWADA
 */

// arithmetic operations
// reference : https://qiita.com/usagi/items/f34976a3d3011506ff7d

#include <iostream>
#include <glm/glm.hpp>

using namespace std;


/**
 * printVector4
 */
void printVector4(string label, glm::vec4 v)
{
    cout << label << v.x << " , " << v.y << " , " << v.z << " , " << v.w << endl;
}


/**
 * main
 */
int main(int argc, char **argv)
{
  auto p = glm::vec4( 2, 3, 4, 5 );
  auto q = glm::vec4( 3, 4, 5, 6 );

  // scalar addition of  vector
  auto n = p + q;

  // scalar multiplication of  vector
  auto m = p * q;

    printVector4("p: ", p);
    printVector4("q: ", q);
    printVector4("n ( operator+ ): ", n);
    printVector4("m ( operator* ): ", m);

    return EXIT_SUCCESS;
}

