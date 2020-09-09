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
% g++ readFromString.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp` -o readFromString <br/>

run code <br/>
% ./readFromString <br/>

display as below  <br/>
jsoncpp version: 1.9.3 <br/>
Json:  <br/>
{"Age": 20, "Name": "colin"} <br/>
name: colin <br/>
age: 20 <br/>


### stringWrite.cpp
convert  Json::Value object to JSON string <br/>

build code  <br/>
% g++ stringWrite.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp` -o stringWrite <br/>

run code <br/>
% ./stringWrite <br/>

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
% g++ readFromStream.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp` -o readFromStream <br/>

run code <br/>
Usage: ./readFromStream \< jsonFile \> <br/>
ex) <br/>
% ./readFromStream assets/withComment.json <br/>

display as below  <br/>
open: assets/withComment.json <br/>
"value" <br/>
"python" <br/>
"c++" <br/>
"ruby" <br/>

### parse_sample.cpp
// parse sample JSON file <br/>

build code  <br/>
% g++ parse_sample.cpp -std=c++11 `pkg-config --cflags --libs jsoncpp` -o parse_sample <br/>

run code <br/>
% ./parse_sample  <br/>

display as below  <br/>
encoding: UTF-8 <br/>
indentLength: 3 <br/>
indentUseSpace: true <br/>
plugins:  <br/>
python <br/>
c++ <br/>
ruby <br/>

### Reference <br/>
- https://github.com/open-source-parsers/jsoncpp
- http://open-source-parsers.github.io/jsoncpp-docs/doxygen/index.html

