json-c: src
===============

j
### samples
- test2.cpp <br/>
parse JSON from string <br/>

- parse_from_file.c <br/>
psrse JSON from file <br/>


- parse_from_string.c <br/>
psrse JSON from string <br/>

- parse_mail.c <br/>
parse mail json file <br/>

Build and Run: <br/>
% make string  <br/>
or  <br/>
% gcc parse_string.c -o string `pkg-config --cflags --libs json-c` <br/>

% ./string <br/>
> Name : xxxxx  <br/>
> Id : 101  <br/>
> Voting_eligible : true  <br/>


