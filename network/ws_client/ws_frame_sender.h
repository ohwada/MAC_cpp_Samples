#pragma once
/**
 * ws_frame_sender.h
 * 2022-10-01 K.OHWADA
 */

#include <stdbool.h>
#include "tcp.h"


// prototype
bool frame_write(int sockfd, char* write_data, size_t data_size);


/** 
 *   frame_write
 */
bool frame_write(int sockfd, char* write_data, size_t data_size)
{

    const size_t DATA_SIZE = 100; 
    char error[DATA_SIZE];

    dump_frame_write_data(write_data, data_size);

   bool ret = tcp_write( sockfd, (char *)write_data, data_size, error);

    if(!ret){
        printf("error: %s \n", error);
        close(sockfd );
        return false;
    }

    return true;
}

