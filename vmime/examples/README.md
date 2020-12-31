examples - vmail
===============

vmail Sample <br/>

the files in this directory were downloaded from below <br/>
- https://github.com/kisli/vmime/blob/master/examples/ <br/>


### sample code 
- example1.cpp <br/>
 This sample program demonstrate the use of the messageBuilder component <br/>
to build a simple message. <br/>

- example2.cpp <br/>
This sample program demonstrate the use of the messageBuilder component <br/>
to build a simple message with an attachment. <br/>

- example3.cpp <br/>
This sample program demonstrate the use of the messageBuilder component <br/>
to build a complex message (HTML content, plain text and embedded image). <br/>

- example4.cpp <br/>
This sample program demonstrate the use of the messageParser component <br/>
// to enumerate the text parts in a message.<br/>

- example5.cpp <br/>
This sample program demonstrate the use of the messageParser component. <br/>
// to enumerate the attachments in a message. .<br/>

- example6.cpp <br/>
Connect to a message store with pop3 <br/>
or Send a message with smtp <br/>

- example7.cpp <br/>
This sample program demonstrates how to enumerate encoders and
messaging services in VMime. <br/>

- viewer.cpp <br/>
// A simple MIME viewer to show all the components of a message. <br/>


build code <br/>
  % g++ example1.cpp -std=c++11 `pkg-config --cflags --libs vmime`  <br/>  

run code <br/>
% ./a.out

display as below <br/>
> Generated message: <br/>
> Subject: My first message generated with vmime::messageBuilder <br/>
> From: me@somewhere.com <br/>

viewer.cpp <br/>
<image src="https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/vmime/screenshot/viewer.png" width="300" /><br/>

### Reference <br/>
- https://github.com/kisli/vmime

