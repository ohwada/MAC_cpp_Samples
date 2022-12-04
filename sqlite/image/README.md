sqlite: image
===============


insert and select image data


## samples
- create_image_table.c  
create_image_table in image.db  

- insert_image.c  
insert image data into sqlite  
by loading from file  

- select_image.c  
select imaga data from sqlite  
and save into file  


Build and Run:  
% make create
% bin/create
> sql : CREATE TABLE image_table(id INTEGER PRIMARY KEY, name TEXT, data BLOB)


