# CMakeLists.txt
# 2022-06-01 K.OHWADA

cmake_minimum_required(VERSION 3.13)
project(test_cmake CXX)

# command option
option(MORNING "morning")
message( "MORNING: " ${MORNING} )

if( ${MORNING} )
	set(target "morning")
	set(CMAKE_CXX_FLAGS "-DMORNING")
	add_executable( ${target} main.cpp good_morning.cpp)
else()
	set(target "hello")
	add_executable( ${target} main.cpp hello.cpp)
endif()

