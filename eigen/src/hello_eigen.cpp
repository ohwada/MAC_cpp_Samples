/**
 * hello_eigen.cpp
 * 2022-06-01 K.OHWADA
 */

// reference : https://qiita.com/yohm/items/a03006790dc1e54a87be

// g++ hello_eigen.cpp -o hello  -I /usr/local/include/eigen3

#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;


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
  std::cout << m << std::endl;

    return 0;
}

//  3  -1  
// 2.5 1.5 