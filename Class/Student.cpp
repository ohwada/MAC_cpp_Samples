/**
 * C++ Class Sample
 * 2020-03-01 K.OHWADA
 */

// simple sample for C++ Class
// reference : http://www7b.biglobe.ne.jp/~robe/cpphtml/html02/cpp02001.html

 #include "Student.hpp"

using namespace std;


/**
 * dispScore
 */
void Student::dispScore()
{
    cout << "Name : " << szName << endl
        << "Math : " << nMath<< " points, "
        << "Science : " << nScience  << " points, "
        << "History : " << nHistory << " points" << endl;
}
