/**
 * C++ Class Sample
 * 2020-03-01 K.OHWADA
 */

// simple sample for C++ Class
// reference : http://www7b.biglobe.ne.jp/~robe/cpphtml/html02/cpp02001.html


 #include "Student.hpp"

#define ELEM(array)  (sizeof (array) / sizeof *(array))

using namespace std;


/**
 * main
 */
int main()
{
    Student students[] = {
        { "Akai",   73, 98, 86, },
        { "Kasai", 64, 45, 40, },
        { "Yoshida",   76, 78, 69, },
    };

    cout << "Exam Scores : "<< endl;
    for(int i = 0; i < ELEM(students); i++){
        students[i].dispScore();
    }

    return 0;
}
