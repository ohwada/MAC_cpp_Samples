#
# CMake configuration file for bio_new_connect.c
# 2020-07-01 K.OHWADA
#

cmake_minimum_required(VERSION 3.1)
project(bio_new)

# find OpenSSL
    find_package(OpenSSL REQUIRED)

    if(NOT OPENSSL_FOUND)
        message(FATAL_ERROR "Fail to find OpenSSL") # exit
    endif()

    message(STATUS "OPENSSL_INCLUDE_DIR: ${OPENSSL_INCLUDE_DIR}")
    message(STATUS "OPENSSL_LIBRARIES: ${OPENSSL_LIBRARIES}")

    include_directories(${OPENSSL_INCLUDE_DIR})

    add_executable( bio_new bio_new_connect.c )

    target_link_libraries(bio_new ${OPENSSL_LIBRARIES})

