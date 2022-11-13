#!perl

my $str = "Hello World cgi";
my $length = length $str;
print "Content-Type: text/plain \r\n";
printf "Content-Length: %d \r\n",  $length;
print "\r\n";
print $str;
