# test/CMakeLists.txt
# 2022-06-01 K.OHWADA
# reference : ://qiita.com/shohirose/items/45fb49c6b429e8b204ac

cmake_minimum_required(VERSION 3.13)
set(target "hello")
set(lib "libgreetings")

# create excutable file target hello
add_executable( ${target} main.cpp )

# specify include path
# PROJECT_SOURCE_DIR: Absolute path to 
# the root directory of this project
target_include_directories( ${target}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )

# link greetings.so to hello
target_link_libraries( ${target}  ${lib} )
