#pragma once
/**
 * ws_frame_common.h
 * 2022-10-01 K.OHWADA
 */

// prototype
void int_to_bytes(int val, char *byte1, char *byte2);
int bytes_to_int(char byte1, char byte2);
void dump_frame_write_data(char* data, size_t data_size);
void dump_frame_read_data(char* data, ssize_t data_size);
void dump_frame_data(char* data, size_t data_size);


/**
 * int_to_bytes
 */
void int_to_bytes(int val, char *byte1, char *byte2)
{
    *byte1 = (val & 0xff00) >> 8;

    *byte2 = (val & 0x00ffff);
}


/**
 * bytes_to_int
 */
int bytes_to_int(char byte1, char byte2)
{
    int i = ( byte1 << 8 )+ (unsigned char)byte2;
    return i;
}


/**
 * dump_frame_write_data
 */
void dump_frame_write_data(char* data, size_t data_size)
{
    printf("write(%zu) : ", data_size);
    dump_frame_data(data, data_size);
}


/**
 * dump_frame_read_data
 */
void dump_frame_read_data(char* data, ssize_t data_size)
{
    if(data_size <= 0){
        return;
    }

    printf("read(%zu) : ", data_size);
    dump_frame_data(data, data_size);
}


/**
 * dump_frame_data
 */
void dump_frame_data(char* data, size_t data_size)
{
    for(int i=0; i<data_size; i++){
        printf("%02x ", (unsigned char)data[i] );
    } // for
        printf("\n");
}
