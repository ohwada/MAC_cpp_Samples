setup - postfix
===============

###  install postfix
postfix is pre-installed on macOS <br/>
% postconf mail_version <br/>
mail_version = 3.2.2 <br/>

### send mail to host in the local net

#### /etc/hosts
add hostname and ip address
> 192.168.99.100 ubuntu

#### postfix main.cf
enable to reference the hosts file when resolving hostname 
> smtp_host_lookup = native

restart
> postfix reload


### Library required for mail
- json-c <br/>
https://github.com/ohwada/MAC_cpp_Samples/tree/master/json-c <br/>


### ubuntu.json
create gmail.json including Your account and Your password <br/>
and place on Your home directory <br/>

template <br/>
gmail.json <br/>
- https://raw.githubusercontent.com/ohwada/MAC_cpp_Samples/master/libcurl/setup/ubuntu.json <br/>

Note: <br/>
this samples don't use account and password <br/>
 so you don't use this file <br/>
use this file for unification with other email apps  <br/>

### view log
% /usr/bin/log stream --predicate  '(process == "smtpd") || (process == "postfix") || (process == "smtp")' --info <br/>

### Reference <br/>
- http://www.postfix.org/

