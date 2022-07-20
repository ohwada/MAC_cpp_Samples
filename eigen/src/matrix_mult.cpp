  /**
 * matrix_mult.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://qiita.com/yohm/items/a03006790dc1e54a87be

// g++ matrix_mult.cpp -o matrix_mult  -I /usr/local/include/eigen3


#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;


 /**
 * main
 */
int main()
{
Matrix2d mat;
  mat << 1, 2,
         3, 4;
  std::cout << "Here is mat*mat:\n" << mat*mat << std::endl;

    return 0;
}

  /*
Here is mat*mat:
 7 10
15 22
*/
