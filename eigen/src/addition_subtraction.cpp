/**
 * addition_subtraction.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://qiita.com/yohm/items/a03006790dc1e54a87be

// g++ addition_subtraction.cpp -o addition  -I /usr/local/include/eigen3

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
  MatrixXd b(2,2);
  b << 2, 3,
       1, 4;
  std::cout << "a + b =\n" << a + b << std::endl;
  std::cout << "a - b =\n" << a - b << std::endl;
  std::cout << "Doing a += b;" << std::endl;
  a += b;
  std::cout << "Now a =\n" << a << std::endl;
  Vector3d v(1,2,3);
  Vector3d w(1,0,0);
  std::cout << "-v + w - v =\n" << -v + w - v << std::endl;

    return 0;
}

// a + b =
// 3 5
// 4 8
// a - b =
// -1 -1
 // 2  0
// Doing a += b;
// Now a =
// 3 5
// 4 8
// -v + w - v =
// -1
// -4
// -6


