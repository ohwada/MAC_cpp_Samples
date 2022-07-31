/**
 *  lambda.cpp
 * 2022-06-01 K.OHWADA
 */

// g++ lambda.cpp =std=c++11

// reference : https://qiita.com/YukiMiyatake/items/8d10bca26246f4f7a9c8

#include<iostream>


/**
 *  main
 */
int main()
{

// Lambda expressions
// it can be executed with () since it is a function
    [](int n){ std::cout << "lambda " << n << std::endl; }(0);     

    auto hoge = [](int x) {
        std::cout << "hoge " << x << std::endl;
    };

    hoge(1);
    hoge(10);

    return 0;
}


// lambda 0
// hoge 1
// hoge 10

