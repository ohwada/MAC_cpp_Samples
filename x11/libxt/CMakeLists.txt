# CMakeLists.txt
# 2022-06-01 K.OHWADA

cmake_minimum_required(VERSION 3.13)
set(target "alloc")
project( ${target} C)


# load the module to use pkg-config
find_package(PkgConfig)

# search library with pkg-config 
# and name its results "LIBXT"
pkg_check_modules(LIBXT REQUIRED  xt)
pkg_check_modules(LIBGLIB REQUIRED   glib-2.0)

# display search result
message( "include: " ${LIBXT_INCLUDE_DIRS} )
message( "lib path: " ${LIBXT_LIBRARY_DIRS} )
message( "lib: " ${LIBXT_LIBRARIES} )

# specify include path
include_directories(${LIBXT_INCLUDE_DIRS} 
${LIBGLIB_INCLUDE_DIRS} )

# create excutable file target alloc
add_executable( ${target} alloc.c )

# specify libraly 
target_link_libraries(  ${target} 
${LIBXT_LIBRARIES}
${LIBGLIB_LIBRARIES}
    )

# specify libraly path
target_link_directories( ${target} BEFORE PUBLIC
${LIBXT_LIBRARY_DIRS} 
${LIBGLIB_LIBRARY_DIRS} )
