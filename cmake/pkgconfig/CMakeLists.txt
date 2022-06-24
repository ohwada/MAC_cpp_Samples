# CMakeLists.txt
# 2022-06-01 K.OHWADA
# reference : https://qiita.com/janus_wel/items/e70695670c22a0331451

cmake_minimum_required(VERSION 3.13)
project(test_cmake C)
set(target "json")

# load the module to use pkg-config
find_package(PkgConfig)

# search library with pkg-config 
# and name its results "LIBJSON"
pkg_check_modules(LIBJSON REQUIRED  json-c)

# display search result
message( "include: " ${LIBJSON_INCLUDE_DIRS} )
message( "lib path: " ${LIBJSON_LIBRARY_DIRS} )
message( "lib: " ${LIBJSON_LIBRARIES} )

# specify include path
include_directories(${LIBJSON_INCLUDE_DIRS})

# create excutable file target json
add_executable( ${target}
    parse_from_string.c
    )

# specify libraly 
target_link_libraries(  ${target} 
${LIBJSON_LIBRARIES}
    )

# specify libraly path
target_link_directories( ${target} BEFORE PUBLIC
${LIBJSON_LIBRARY_DIRS} )
