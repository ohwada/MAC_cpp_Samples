csv - berkeley-db
===============

berkeley-db exsamples <br/>

### csv

Comma separated values <br/>
The csv directory contains application helpers for dealing with comma separated values. <br/>
The program csv_code compiles a text description of the CSV fields into the corresponding C structure definition, while also generating C functions to read, print, and search for records based on the named fields. <br/>
The program csv_load can then load a CSV file of that format into a database. <br/>
Once the data has been loaded, csv_query can interactively query the database. <br/>


make code <br/>

> % make  <br/>

created files <br/>
- csv_code <br/>
- csv_load <br/>
- csv_query <br/>


run code <br/>

(1) You can load now load the csv file into a Berkeley DB <br/>

> ％ ./csv_load -h TESTDIR < sample.csv <br/>

created files in TESTDIR <br/>
- primary : primary database <br/>
- Age : secondary index on Age field <br/>
- Color : secondary index on Color field <br/>
- Fruit : secondary index on Fruit field <br/>


(2) You can then query the database <br/>

	> ％ ./csv_query -h TESTDIR <br/>
> Query: id=1 <br/>
> Record: 1: <br/>
> LastName: Adams <br/>
> FirstName: Bob <br/>
> Color: green <br/>
> Fruit: apple <br/>
> Age: 37 <br/>



### Reference
- https://github.com/berkeleydb/libdb <br/>

