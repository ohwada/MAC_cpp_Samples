/**
 *  weak_ptr.cpp
 * 2022-06-01 K.OHWADA
 */

// http://www.kmonos.net/alang/boost/classes/weak_ptr.html

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>


/**
 *  struct test
 */
struct test {
	test(const char* name) : name_(name) {}
	~test() { std::cout << name_ << " destructed." << std::endl; }
	void showName() { std::cout << "Name: " << name_ << std::endl; }
	const char* name_;
};

using namespace std;


/**
 *  main
 */
int main()
{
	boost::shared_ptr<test> sp( new test("ABC") );
	boost::weak_ptr<test> wp( sp );

	// ポインタが有効なら処理を実行
	if( boost::shared_ptr<test> tmp = wp.lock() )
		tmp->showName();
	else
		cout << "already deleted." << endl;

	// ここでdeleteされる
	sp.reset();

	// ポインタが有効なら処理を実行
	if( boost::shared_ptr<test> tmp = wp.lock() )
		tmp->showName();
	else
		cout << "already deleted." << endl;
	return 0;
}
