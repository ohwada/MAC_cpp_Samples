/**
 * 2022-10-01 K.OHWADA
 * EchoUtil.java
 */

// https://www.coins.tsukuba.ac.jp/~syspro/2020/2020-06-10/echo-client-java.html

import java.io.*;


/**
 * class EchoUtil
 */
class EchoUtil
{
/**
 *  EchoUtil
 */
public EchoUtil()
{
    // none
}


/**
 *  print_recv_data
 */
public static void print_recv_data(String line)
{
// remove the trailing newline code
        String data = line.trim();

        stdout.printf("r(%d) %s \n", data.length(), data);
}


/**
 *  printfOS
 */
public static int printfOS( OutputStream out, String format, Object ... args )
    throws IOException
  {
        String s = String.format( format, args );
  	    return( putStringOS( out, s ) );
  }


/**
 *  putStringOS
 */
public static int putStringOS( OutputStream out, String message )
    throws IOException
{
        byte b[] = message.getBytes();
  	     out.write( b );
  	     out.flush();
        return( b.length );
  }


/**
 *  readLineIS
 */
final static int  READ_LINE_MAX_LINE = 1024;
final static int  EOF = -1;
final static byte  LF = '\n';
public static String readLineIS( InputStream is ) 
    throws IOException
  {
        byte line[] = new byte[ READ_LINE_MAX_LINE];

  	     int c, len = 0 ;

  	      while( (c=is.read()) != EOF )
  	      {
  	          line[len++] = (byte) c;

  	             if( len == line.length || c== LF ) {
  	                      break;
                    }
  	        } // while

  	        if( len == 0 ) {
  	              return null;
            }
  	        
            String str = new String( line, 0, len );

  	         return( str );
  }


/**
 *  readIS
 */
public static String readIS( InputStream is ) 
    throws IOException
  {
        byte line[] = new byte[ READ_LINE_MAX_LINE];

        int len = is.read(line);

// stdout.printf("len: %d \n", len);

  	        if( len <= 0 ) {
  	              return null;
            }

            String str = new String( line, 0, len );

// stdout.printf("str: %s \n", str);

  	         return( str );
  }


/**
 *  thread_sleep
 */
public static void thread_sleep(long millis) 
{
    try {
	    Thread.sleep(millis);    
    } catch (InterruptedException e) {
        stderr.printf("%s \n", e );
    }
}


/**
 * difinition
 * defined to resemble a C language program
 */
static java.io.PrintStream stdout = System.out;
static java.io.PrintStream stderr = System.err;

}
// class