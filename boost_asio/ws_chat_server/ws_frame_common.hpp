#pragma once
/**
 * ws_frame_common.hpp
 * 2022-10-01 K.OHWADA
 */

#include <iostream>
#include <vector>
#include <boost/format.hpp>
#include "ws_frame.h"
#include "ws_frame_common.h"


// prototype
void dump_write_vec(std::vector<char> vec);
void dump_read_vec(std::vector<char> vec);
std::string str_vec_size(std::string name, std::vector<char> vec);
void dump_vec(std::vector<char> vec);
void print_close(std::string name, int code, std::string reason);
std::string  close_to_string(int code, std::string reason);


/**
 * dump_write_vec
 */
void dump_write_vec( std::vector<char> vec)
{
    std::cout << str_vec_size("write", vec);
    dump_vec(vec);
}


/**
 * dump_read_vec
 */
void dump_read_vec( std::vector<char> vec)
{
    std::cout << str_vec_size("read", vec);
    dump_vec(vec);
}


/**
 * str_vec_size
 */
std::string str_vec_size(std::string name, std::vector<char> vec)
{
    const std::string FORMAT("%s (%d) : ");
    return boost::str( boost::format(FORMAT) % name % vec.size() );
}


/**
 * dump_vec
 */
void dump_vec(std::vector<char> vec)
{
    dump_frame_data( (char *)vec.data(), vec.size());
}


/**
 * print_close
 */
void print_close(std::string name, int code, std::string reason)
{
    std::cout << name << ": " << close_to_string(code, reason) << std::endl;
}


/**
 *  close_to_string
 */
std::string  close_to_string(int code, std::string reason)
{
    const std::string FORMAT("%s(%d) reason: %s");

    return boost::str( boost::format(FORMAT) %  closecode_to_string(code) % code % reason);
}
