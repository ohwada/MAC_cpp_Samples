keyboard - ConsoleUtil
===============

C++ keyboard sample <br/>
emulater for kbhit function of Windows <br />

### test_kbhit.c
get the event of whether a key was pressed <br/>

build code  <br/>
% gcc test_kbhit.c keyboard.c -o kbhit  <br/>

run code <br/>
% ./kbhit <br/>

display as below  <br/>
quit when press any key <br/> 

when press ESC key  <br/>
display as below  <br/>
press: 27 ( ESC )   <br/>

### test_getKey.c
get typed key code  <br/>
display typed key character <br/>

build code  <br/>
% gcc test_getKey.c keyboard.c -o getkey  <br/>

run code  <br/>
% ./getkey  <br/>

display as below  <br/>
quit when press any key <br/>

when press 'a' key  <br/>
display as below  <br/>
press: 'a'  <br/>

### test_waitPressESC.c
 wait press ESC key  <br/>

build code  <br/>
% gcc test_waitPressESC.c  keyboard.c -o wait  <br/>

run code  <br/>
% ./wait  <br/>

display as below <br/>
quit when press ESC key <br/>

when press ESC key <br/>
display quit <br/>
and new command prompt <br/>
quit  <br/>
 %  <br/>

### test_get_password_without_echo.c
enter password without echo <br/>

build code  <br/>
% gcc test_get_password_without_echo.c keyboard.c -o password <br/>

run code  <br/>
% ./password   <br/>

display as below  <br/>
enter password   <br/>
 \>   <br/>

when enter 1234 <br/>
display nothng <br/>
 \> <br/>

when press enter key <br/>
display entered password  <br/>
 password: 1234 <br/>

### test_get_password_with_echo_star.c
enter password with echo star '*' <br/>

build code  <br/>
% gcc  test_get_password_with_echo_star.c keyboard.c -o star <br/>

run code  <br/>
% ./star   <br/>

display as below  <br/>
enter password  <br/>
 \><br/>

when enter 1234 <br/>
display star '*' <br/>
 \> **** <br/>

when press enter key <br/>
display entered password <br/>
password: 1234 <br/>

### reference: 
- https://hotnews8.net/programming/tricky-code/c-code03

