/**
 * mysqlx.cpp
 * 2022-06-01 K.OHWADA
 */

// create table "c"
// insert records
// https://github.com/mysql/mysql-connector-cpp

#include <iostream>
#include <mysqlx/xdevapi.h>

using ::std::cout;
using ::std::endl;
using namespace ::mysqlx;


/**
 * main
 */
int main(int argc, const char* argv[])
{

try {

  const char   *url = (argc > 1 ? argv[1] : "mysqlx://root@127.0.0.1");

  cout << "Creating session on " << url
       << " ..." << endl;

  Session sess(url);

  cout <<"Session accepted, creating collection..." <<endl;

  Schema sch= sess.getSchema("db_mysqlx");
  Collection coll= sch.createCollection("c1", true);

  cout <<"Inserting documents..." <<endl;

  coll.remove("true").execute();

  {
    DbDoc doc(R"({ "name": "foo", "age": 1 })");

    Result add =
      coll.add(doc)
          .add(R"({ "name": "bar", "age": 2, "toys": [ "car", "ball" ] })")
          .add(R"({ "name": "bar", "age": 2, "toys": [ "car", "ball" ] })")
          .add(R"({
                 "name": "baz",
                  "age": 3,
                 "date": { "day": 20, "month": "Apr" }
              })")
          .add(R"({ "_id": "myuuid-1", "name": "foo", "age": 7 })")
          .execute();

    std::list<string> ids = add.getGeneratedIds();
    for (string id : ids)
      cout <<"- added doc with id: " << id <<endl;
  }

  cout <<"Fetching documents..." <<endl;

  DocResult docs = coll.find("age > 1 and name like 'ba%'").execute();

  int i = 0;
  for (DbDoc doc : docs)
  {
    cout <<"doc#" <<i++ <<": " <<doc <<endl;

    for (Field fld : doc)
    {
      cout << " field `" << fld << "`: " <<doc[fld] << endl;
    }

    string name = doc["name"];
    cout << " name: " << name << endl;

    if (doc.hasField("date") && Value::DOCUMENT == doc.fieldType("date"))
    {
      cout << "- date field" << endl;
      DbDoc date = doc["date"];
      for (Field fld : date)
      {
        cout << "  date `" << fld << "`: " << date[fld] << endl;
      }
      string month = doc["date"]["month"];
      int day = date["day"];
      cout << "  month: " << month << endl;
      cout << "  day: " << day << endl;
    }

    if (doc.hasField("toys") && Value::ARRAY == doc.fieldType("toys"))
    {
      cout << "- toys:" << endl;
      for (auto toy : doc["toys"])
      {
        cout << "  " << toy << endl;
      }
    }

    cout << endl;
  }
  cout <<"Done!" <<endl;
}
catch (const mysqlx::Error &err)
{
  cout <<"ERROR: " <<err <<endl;
  return EXIT_FAILURE;
}
catch (std::exception &ex)
{
  cout <<"STD EXCEPTION: " <<ex.what() <<endl;
  return EXIT_FAILURE;
}
catch (const char *ex)
{
  cout <<"EXCEPTION: " <<ex <<endl;
  return EXIT_FAILURE;
}

  return EXIT_SUCCESS;
}

// Creating session on mysqlx://root@127.0.0.1 ...
// Session accepted, creating collection...
// Done!

