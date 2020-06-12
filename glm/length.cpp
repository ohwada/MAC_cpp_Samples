/**
 * glm samples
 * 2020-03-01 K.OHWADA
 */


// vector length
// reference : https://qiita.com/usagi/items/f34976a3d3011506ff7d

#include <iostream>
#include <glm/glm.hpp>

using namespace std;


/**
 * main
 */
int main(int argc, char **argv)
{
    cout << "glm version: " << GLM_VERSION_MESSAGE << endl;

    auto a = glm::vec2( 3, 4 );
    auto len = glm::length( a );
    cout
        << "a: " << a.x << " , " << a.y << "\n"
        << "length(a): " << len << endl;

    return EXIT_SUCCESS;

}

