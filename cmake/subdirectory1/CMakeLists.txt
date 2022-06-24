# CMakeLists.txt
# 2022-06-01 K.OHWADA

cmake_minimum_required(VERSION 3.13)
project(test_cmake CXX)
set(target "hello")

# souce files 
file(GLOB files src/*.cpp )

# create excutable file target hello
add_executable( ${target} ${files} )

# specify the library path
# PROJECT_SOURCE_DIR: Absolute path to 
# the root directory of this project
target_include_directories( ${target}
  PUBLIC ${PROJECT_SOURCE_DIR}/src
  )
