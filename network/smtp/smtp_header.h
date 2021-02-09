/**
 *  smtp client sample
 * 2021-02-01 K.OHWADA
 */


// header file for SMTP Client 


#include <stdio.h>
#include <stdlib.h>
 #include "smtp_client.h"
#include "msg_builder.h"

// constant
// dummy email address for mail message
// NOT real email address
const char DUMMY_TO[] = "taro@example.com";
const char DUMMY_FROM[] = "jiro@example.com";
