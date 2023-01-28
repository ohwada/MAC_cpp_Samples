/**
 * 2022-10-01 K.OHWADA
 */

// EchoServerWorker.java
// https://www.coins.tsukuba.ac.jp/~syspro/2020/2020-06-13/echo-server-java.html

/*
   	  EchoServerWorker.java
-- A server/worker that sends and receives strings 
(TCP/IP, Java version)
   	  ~yas/syspro/ipc/EchoServerWorker.java
   	*/
   
   	import java.net.*;
   	import java.io.*;
  

/**
 * class EchoServerWorker
 */
public class EchoServerWorker implements Runnable
{
         Socket com ;
        EchoServerWorker( Socket com )
         {
                this.com = com ;
        }

/**
 * run
 */
public void run() 
// echo_receive_request_and_send_reply()
{
        try
        {
                InputStream in = com.getInputStream();
                OutputStream out = com.getOutputStream();
                String line;
                while( (line = echo_receive_request(in))!= null )
                {
// stdout.printf("received (com hash==%s) %d characters, [%s]\n", com.hashCode(), line.length(),line );

                        EchoUtil.print_recv_data(line);

                        echo_send_reply( line, out );
                } // while

                stdout.printf("connection (com hash==%s) closed.\n", com.hashCode());
                in.close();
                out.close();
                com.close();
        }
        catch( IOException e )
        {
                stderr.printf("%s \n", e );
        }
}


/**
 * echo_receive_request
 */
public static String echo_receive_request( InputStream is ) 
    throws IOException
{
        // return( readLineIS(is) );
        return( EchoUtil.readIS(is) );

}


/**
 * echo_send_reply
 */
public static void echo_send_reply( String line, OutputStream out )
    throws IOException
    {
            EchoUtil.printfOS( out, "%s", line );
    }


/**
 * difinition
 * defined to resemble a C language program
 */
static java.io.PrintStream stdout = System.out;
static java.io.PrintStream stderr = System.err; 

}
// class
