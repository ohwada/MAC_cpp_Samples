# CMakeLists.txt
# 2022-06-01 K.OHWADA
# reference : ://qiita.com/shohirose/items/45fb49c6b429e8b204ac

cmake_minimum_required(VERSION 3.13)
project(test_cmake CXX)
set(target "hello")
set(lib "libgreetings")

# create static shared library libgreetings.a
add_library( ${lib} STATIC hello.cpp good_morning.cpp)

# create excutable file target hello
add_executable( ${target} main.cpp)

# link libgreetings.a to target hello
target_link_libraries( ${target} ${lib} )

