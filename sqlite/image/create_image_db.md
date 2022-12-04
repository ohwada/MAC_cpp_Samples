sqlite: create image.db
===============

###  create image.db

% sqlite3 image.db  
sqlite> create table image_table(id integer primary key, name text, data blob);
sqlite> .schema
sqlite> .quit  

