/**
 * boost Samples
 * 2020-07-01 K.OHWADA
 */

// serialization
// save class to archive file
// load class from archive file

// reference : https://img.atwikiimg.com/www31.atwiki.jp/lafe/pub/boost_serialization/boost_serialization.html



#include <iostream>
#include <fstream>
#include <string>
#include <boost/serialization/string.hpp>
 #include <boost/archive/text_oarchive.hpp>
 #include <boost/archive/text_iarchive.hpp>


/**
 * class Student
 */
class Student {
 public:
   std::string name_;
   int age_;
   
   friend class boost::serialization::access;
   template<class Archive>
     void serialize(Archive& ar, const unsigned int version)
     {
       ar & name_;
       ar & age_;
     }
 };


using namespace std;

 
/**
 * main
 */
 int main(void) 
{

    string file("output.txt");

   Student student1;
   Student student2;

// set param value
      student1.name_ = "taro";
      student1.age_ = 20;

// create an output archive
   std::ofstream ofs(file);
   boost::archive::text_oarchive oa(ofs);
   
   // export to file
   oa << student1;
   
   // close output stream
   ofs.close();
   
    cout << "saved to: " << file << endl;

// create an intput archive
   std::ifstream ifs(file);
   boost::archive::text_iarchive ia(ifs);
   
    // import from file
   ia >> student2;
   
// get param value
      string name = student2.name_;
      int age = student2.age_;
 
// close input stream
   ifs.close();

// display param value
    cout << "name: " << name << endl;
    cout << "age: " << age << endl;

    return EXIT_SUCCESS;
}


// name: taro
// age: 20

