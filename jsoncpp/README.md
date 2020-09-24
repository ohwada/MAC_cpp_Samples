jsoncpp
===============

jsoncpp sample <br/>
parse JSON using jsoncpp <br/>

jsoncpp : <br/>
C++ library for interacting with JSON. <br/>
https://github.com/open-source-parsers/jsoncpp <br/>


### install jsoncpp
% brew install jsoncpp <br/>
https://formulae.brew.sh/formula/jsoncpp <br/>


### readFromString.cpp
parse JSON string <br/>

build code  <br/>
% g++ readFromString.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp` <br/>

run code <br/>
% ./a.out <br/>

display as below  <br/>
> jsoncpp version: 1.9.3 
> Json:  
> {"Age": 20, "Name": "colin"} 
> name: colin 
> age: 20 


### stringWrite.cpp
convert  Json::Value object to JSON string <br/>

build code  <br/>
% g++ stringWrite.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp`  <br/>

run code <br/>
% ./a.out <br/>

display as below  <br/>
> {
> 	"action" : "run",
> 	"data" : 
>	{
>		"number" : 1
>	}
> }

### readFromStream.cpp
parse JSON file <br/>

build code  <br/>
% g++ readFromStream.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp` <br/>

run code <br/>
Usage: ./a.out \< jsonFile \> <br/>
ex) <br/>
% ./a.out assets/withComment.json <br/>

display as below  <br/>
> open: assets/withComment.json 
> "value" 
> "python" 
> "c++" 
> "ruby" 


### parse_sample.cpp
parse sample JSON file <br/>

build code  <br/>
% g++ parse_sample.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp` <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
> encoding: UTF-8 
> indentLength: 3 
> indentUseSpace: true 
> plugins:  
> python 
> c++ 
> ruby 


### parse_parson.cpp
parse parson JSON file <br/>

build code  <br/>
% g++ parse_parson.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp` <br/>

run code <br/>
Usage: ./a.out \< jsonFile \> <br/>
% ./a.out  <br/>

display as below  <br/>
> open: assets/taro.json
> {
>	"age" : 30,
>	"name" : "taro"
> }
> name: taro
> age: 30


### Reference <br/>
- https://github.com/open-source-parsers/jsoncpp
- http://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html

