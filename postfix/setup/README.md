setup - postfix
===============

###  install postfix
postfix is pre-installed on macOS <br/>
% postconf mail_version <br/>
mail_version = 3.2.2 <br/>

### send mail to host in the local net

#### /etc/hosts

add hostname and ip address <br/>

> 192.168.99.100 ubuntu <br/>

#### postfix main.cf

enable to reference the hosts file when resolving IP address <br/>

> smtp_host_lookup = native <br/>

restart <br/>
> postfix reload <br/>

reference : Postfix Configuration Parameters <br/>
smtp_host_lookup : what mechanisms the Postfix SMTP client uses to look up a host's IP address <br/>
native : use the native naming service only <br/>
http://www.postfix.org/postconf.5.html <br/>

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

reference : Max OSX Server 5.2 Postfix missing SMTP Logs <br/>
http://blog.windhoek24.com/max-osx-server-5-2-postfix-missing-smtp-logs/ <br/>

### Reference <br/>
- http://www.postfix.org/
- http://www.postfix.org/postconf.5.html

