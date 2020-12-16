/**
 * boost Samples
 * 2020-07-01 K.OHWADA
 */

// BankAccount
// From time to time, the bankAgent will deposit $500 in JoesAccount. 
// Joe will similarly withdraw $100 from his account. 
// These sentences describe that the bankAgent and Joe are executed concurrently.'

// https://www.boost.org/doc/libs/1_75_0/doc/html/thread/synchronization.html#thread.synchronization.tutorial

#include <iostream>
#include <boost/thread.hpp>


/**
 * class BankAccount
 */
class BankAccount {
    boost::mutex mtx_;
    int balance_;
public:
    int Deposit(int amount) {
        mtx_.lock();
        balance_ += amount;
        int b = balance_;
        mtx_.unlock();
       return b;
    }
    int Withdraw(int amount) {
        mtx_.lock();
        balance_ -= amount;
        int b = balance_;
        mtx_.unlock();
       return b;
    }
    int GetBalance() {
        mtx_.lock();
        int b = balance_;
        mtx_.unlock();
        return b;
    }
};


BankAccount JoesAccount;


/**
 * bankAgent
 */
void bankAgent(void)
{
    for (int i =10; i>0; --i) {
         int joePocket = JoesAccount.Deposit(500);
        std::cout << "\n bankAgent: " << joePocket << std::endl;
    }

}


/**
 *  Joe
 */
void Joe(void) 
{
    for (int i =10; i>0; --i) {
        int myPocket = JoesAccount.Withdraw(100);
        std::cout << "\n Joe: " << myPocket << std::endl;
    }

}


 using namespace std;


/**
 * main
 */
int main(void) 
{
    
    boost::thread thread1(bankAgent); // start concurrent execution of bankAgent
    boost::thread thread2(Joe); // start concurrent execution of Joe

    thread1.join();
    thread2.join();

    return EXIT_SUCCESS;
}


 // bankAgent: 4900
 // Joe: 4800

