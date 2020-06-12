/**
 * glm samples
 * 2020-03-01 K.OHWADA
 */

// Simplex noise
// reference : https://qiita.com/usagi/items/f34976a3d3011506ff7d


#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

using namespace std;


/**
 * main
 */
int main(int argc, char **argv)
{

   char * filepath =(char *) "simplex.pgm";

  ofstream out(filepath);
  out << "P2\n256 256\n255\n";
  for ( auto y = 0; y < 256; ++y )
  {
    for ( auto x = 0; x < 256; ++x )
    {
        out << glm::roundEven( ( glm::simplex( glm::vec2( x / 64., y / 64. ) ) + 1.0f) * 255 / 2 ) << " ";
    } // for x
    out << endl;
  } // for y

    cout << "saved: " << filepath << endl;
    return EXIT_SUCCESS;
}

