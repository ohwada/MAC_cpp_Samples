## 2022-10-01 K.OHWADA

#  echo_client.pl
# Messages to be sent and received 
# are separated by newline code
# https://perlzemi.com/blog/20090406123890.html

# remove the trailing newline code
sub rtrim {
	my $val = shift;
	$val =~ s/\s*$//;
	return $val;
}

# use strict;
# use warnings;
use Socket;

# Host name to connect to
my $host = 'localhost';
# port number to connect to
my $port = 5000;

# Client
# 1. Create Socket
my $sock;
socket($sock, PF_INET, SOCK_STREAM, getprotobyname('tcp' ))
  or die "Cannot create socket: $!";

# 2. Create socket information
my $packed_remote_host = inet_aton($host)
  or die "Cannot pack $host: $!";

# Pack hostname and port number
my $sock_addr = sockaddr_in($port, $packed_remote_host)
  or die "Cannot pack $host:$port: $!";

# 3. Connect using socket
connect($sock, $sock_addr)
  or die "Cannot connect $host:$port: $!";

# 4. Write data
# Don't do write buffering.
my $old_handle = select $sock;
$| = 1; 
select $old_handle;

# the server does not receive without a linefeed code
my $format = "%03d\n";

my $data;

my $count;

# for loop ---
for($count = 0; $count < 10; $count++) {
    my $msg = sprintf( $format, $count );

    print $sock $msg;

# 5. read data
    if(my $rcv_data = <$sock> ) {
        my $data = rtrim($rcv_data);
        print "r: $data \n";
    }

# wait 1 sec
    sleep 1;
}
# for ---

# 6. Close socket
close $sock;

1;
