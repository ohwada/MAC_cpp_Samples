jsoncpp:src
===============


### samples
- parse_string.cpp <br/>
parse JSON string <br/>

- parse_file.cpp <br/>
parse JSON file <br/>

- parse_parson.cpp <br/>
parse parson JSON file <br/>

- to_json.cpp <br/>
convert  Json::Value object to JSON string <br/>


Build and Run:  <br/>
% make string <br/>
or <br/>
% g++ parse_string.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp` <br/>

% ./string <br/>
> jsoncpp version: 1.9.3 
> Json:  
> {"Age": 20, "Name": "colin"} 
> name: colin 
> age: 20 

