# CMakeLists.txt
# 2022-06-01 K.OHWADA
# 
cmake_minimum_required(VERSION 3.13)
set(target "hello")
project( ${target}  C)

# load the module to use pkg-config
find_package(PkgConfig)

# search library with pkg-config 
# and name its results "LIBX11"
pkg_check_modules(LIBX11 REQUIRED  x11)

# display search result
message( "include: " ${LIBX11_INCLUDE_DIRS} )
message( "lib path: " ${LIBX11_LIBRARY_DIRS} )
message( "lib: " ${LIBX11_LIBRARIES} )

# specify include path
include_directories(${LIBX11_INCLUDE_DIRS} )

# create excutable file target hello
add_executable( ${target} hello.c )

# specify libraly 
target_link_libraries(  ${target} 
${LIBX11_LIBRARIES}
)

# specify libraly path
target_link_directories( ${target} BEFORE PUBLIC
${LIBX11_LIBRARY_DIRS} )