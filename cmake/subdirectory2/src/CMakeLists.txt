# src CMakeLists.txt
# 2022-06-01 K.OHWADA
# reference : ://qiita.com/shohirose/items/45fb49c6b429e8b204ac

cmake_minimum_required(VERSION 3.13)
set(lib "libgreetings")

# create shared library libgreetings.so
add_library(${lib} SHARED hello.cpp good_morning.cpp)

# specify the library path
# PROJECT_SOURCE_DIR: Absolute path to 
# the root directory of this project
target_include_directories( ${lib}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
