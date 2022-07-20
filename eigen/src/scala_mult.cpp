 /**
 * scala_mult.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://qiita.com/yohm/items/a03006790dc1e54a87be

// g++ scala_mult.cpp -o scala  -I /usr/local/include/eigen3

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;


 /**
 * main
 */
int main()
{
Matrix2d a;
  a << 1, 2,
       3, 4;
  Vector3d v(1,2,3);
  std::cout << "a * 2.5 =\n" << a * 2.5 << std::endl;

    return 0;
}

/*
a * 2.5 =
2.5   5
7.5  10
*/

