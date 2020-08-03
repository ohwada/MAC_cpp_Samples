/**
 * bind sample
 * 2020-03-01 K.OHWADA
 */

// example : binding a member function of a class
// https://kaworu.jpn.org/cpp/std::bind

#include <iostream>
#include <functional>

using namespace std;


/**
 *  class Foo
 */
class Foo {
        private:
        public:
                int     data;
                Foo () :data(7) {}
                Foo (int _x) :data(_x) {}
                void display_hello () {
                        cout << "Hello" << endl;
                }
                void display_number(int i) {
                        cout << "Number: " << i << endl;
                }
};


/**
 *  main
 */
int main(int argc, char *argv[])
{
        Foo     foo1(123);

// bind member of class
        auto f1 = std::bind(&Foo::display_number, foo1, 456);

// excute
// Number: 456
        f1();

        return 0;
}
