/**
 * matrix_access.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://qiita.com/yohm/items/a03006790dc1e54a87be

// g++ matrix_access.cpp -o access  -I /usr/local/include/eigen3

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;


/**
 * main
 */
int main()
{
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << "Here is the matrix m:\n" << m << std::endl;
  VectorXd v(2);
  v(0) = 4;
  v(1) = v(0) - 1;
  std::cout << "Here is the vector v:\n" << v << std::endl;

    return 0;
}

// Here is the matrix m:
//  3  -1
// 2.5 1.5
// Here is the vector v:
// 4
// 3