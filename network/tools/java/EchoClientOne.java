/**
 * 2022-10-01 K.OHWADA
 */

// https://www.coins.tsukuba.ac.jp/~syspro/2020/2020-06-10/echo-client-java.html

   	/*
     EchoClientOne.java
    Client for sending and receiving character strings 
    (TCP/IP version)
     ~yas/syspro/ipc/EchoClientOne.java
     Created on 2004/02/14 21:09:17
   */
   
import java.net.*;
import java.io.*;


/**
 * class EchoClientOne
 */
class EchoClientOne
{
/**
 * main
 */
public static void main(String argv[]) 
    throws IOException 
{

        String server = "localhost";
  	    int portno = 1234;
  	    String message = "Hello";

        if( argv.length == 3 ) {
  	              server = argv[0];
  	              portno = Integer.parseInt( argv[1] );
  	              message = argv[2];
        } else {
  	              stdout.println("Usage: % java EchoClientOne host port 'message'");
  	      }

        stdout.printf("server: %s \n", server);
        stdout.printf("portno: %d \n", portno);
        stdout.printf("message: %s \n", message);

  	      echo_client_one( server, portno, message );
  }


/**
 *  echo_client_one
 */
final static int LOOP = 10;
final static long SLEEP = 1000; // 1 SEC
public static void echo_client_one( String server, int portno, 
                                              String message )
    throws IOException
{

                Socket sock = new Socket( server, portno );
                 InputStream in = sock.getInputStream();
                OutputStream out = sock.getOutputStream();
  
    for (int i = 0; i < LOOP; i++)
    {
// echo_send_request( out, message );               
// stdout.printf("sent: %d bytes [%s\n]\n", message.length()+1,message );
  	          
            String send_msg = String.format("%03d", i);

// stdout.printf("msg: %s\n", send_msg);

    // stdout.printf("received: %d bytes [%s]\n",rline.length(), rline);
            echo_send_request( out, send_msg );

            String rline = echo_receive_reply( in );

    // stdout.printf("received: %d bytes [%s]\n",rline.length(), rline);

            EchoUtil.print_recv_data(rline);

// wait 1 sec
                    EchoUtil.thread_sleep(SLEEP); 
    } // for

// close
        stdout.println("close");
        in.close();
  	    out.close();
  	    sock.close();
}


/**
 *  echo_send_request
 */
public static void echo_send_request( OutputStream out, String message )
    throws IOException
  {
// send with new line code
        // printfOS( out, "%s\n", message );

// send without new line code
        EchoUtil.printfOS( out, "%s", message );

  }


/**
 *  echo_receive_reply
 */
public static String echo_receive_reply( InputStream in )
    throws java.io.IOException
  {
       //  String rline = readLineIS( in );
        String rline = EchoUtil.readIS( in );

  	    return( rline );
  }


/**
 * difinition
 * defined to resemble a C language program
 */
static java.io.PrintStream stdout = System.out;

}
// class
