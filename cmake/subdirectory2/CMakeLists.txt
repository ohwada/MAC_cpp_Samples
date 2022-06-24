# CMakeLists.txt
# 2022-06-01 K.OHWADA
# reference : ://qiita.com/shohirose/items/45fb49c6b429e8b204ac

cmake_minimum_required(VERSION 3.13)
project(test_cmake CXX)

# register a subdirectory
add_subdirectory(src)
add_subdirectory(test)
