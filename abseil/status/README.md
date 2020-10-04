status - abseil
===============

abseil Sample <br/>

Abseil status library <br/>
status library containing an absl::Status class for holding error handling information, a set of canonical absl::StatusCode error codes, and associated utilities for generating and propagating status codes. <br/>

## sample code
- status.cpp <br/>
return status code <br/>

build code <br/>
% g++ status.cpp `pkg-config --cflags --libs abseil_status`  <br/>

run code <br/>
% ./a.out <br/>

display as below <br/>
Usage: ./a.out \<filename\> \<mode\> <br/>
 
% ./a.out abc w <br/>
> INVALID_ARGUMENT: bad mode: w <br/>

% ./a.out abc r <br/>
> NOT_FOUND: abc is missing <br/>

% ./a.out status.cpp r <br/>
> Ok <br/>

### Reference <br/>
- https://abseil.io/docs/cpp/guides/
- https://github.com/abseil/abseil-cpp

