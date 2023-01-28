/**
 * 2022-10-01 K.OHWADA
 */

// EchoServerSingle.java
// https://www.coins.tsukuba.ac.jp/~syspro/2020/2020-06-13/echo-server-java.html

/*
  EchoServerSingle.java
  Server for sending and receiving strings (TCP/IP, Java version, no threads)
  ~yas/syspro/ipc/EchoServerSingle.java
   	  Created on 2004/05/09 20:00:24
   	*/

import java.net.*;
import java.io.*;
   	
/**
 * class EchoServerSingle
 */
  class EchoServerSingle
  {
/**
 * main
 */
public static void main(String argv[]) 
    throws IOException
{
  	    int portno = 1234;

        if( argv.length == 1 ) {
            portno = Integer.parseInt( argv[0] );
        } else {
                stdout.printf("Usage: %% java EchoServerSingle port\n");
        }
        
        System.out.printf("portno: %d \n", portno);

        echo_server_single( portno );
}


/**
 *  echo_server_single
 * argument: port number
 */
public static void echo_server_single( int portno ) 
throws IOException
  {
        ServerSocket acc = new ServerSocket( portno );
        print_my_host_port( portno );
        while( true )
        {
                stdout.printf("accepting incoming connections (hash== %s) ...\n", 
                acc.hashCode());
                Socket com = acc.accept();
                tcp_peeraddr_print( com );
                EchoServerWorker esw = new EchoServerWorker(com);
                esw.run();
        } // while
}

/**
 *  print_my_host_port
 *  works the same as the C function of the same name
 */
public static void print_my_host_port( int portno )
throws UnknownHostException
{
        InetAddress ia = java.net.InetAddress.getLocalHost();
        String hostname = ia.getHostName();
        stdout.printf("run telnet %s %d\n", hostname, portno );
}


/**
 *  tcp_peeraddr_print
 *  works the same as the C function of the same name
 */
public static void tcp_peeraddr_print( Socket com )
{
        InetSocketAddress isa = 
        (InetSocketAddress)com.getRemoteSocketAddress();
        InetAddress ia = isa.getAddress();
        String peerhostaddr = ia.getHostAddress();
        int peerportno = isa.getPort();
        stdout.printf("connection (hash== %s) from %s:%d\n", 
        com.hashCode(), peerhostaddr, peerportno );
}


/**
 * difinition
 * defined to resemble a C language program
 */
static java.io.BufferedReader stdin = 
    new java.io.BufferedReader( new java.io.InputStreamReader(System.in) );
static java.io.PrintStream stdout = System.out;
static java.io.PrintStream stderr = System.err; 

}
// class

// run telnet MacBook-Air.local 1234