# CMakeLists.txt
# 2022-06-01 K.OHWADA
# 
cmake_minimum_required(VERSION 3.13)
set(target "octagon")
project( ${target}  C)

# load the module to use pkg-config
find_package(PkgConfig)

# search library with pkg-config 
# and name its results "LIBXPM"
pkg_check_modules(LIBXPM REQUIRED  xpm)
pkg_check_modules(LIBXT REQUIRED  xt)
pkg_check_modules(LIBXEXT REQUIRED  xext)

# display search result
message( "include: " ${LIBXPM_INCLUDE_DIRS} )
message( "lib path: " ${LIBXPM_LIBRARY_DIRS} )
message( "lib: " ${LIBXPM_LIBRARIES} )

# specify include path
include_directories(${LIBXPM_INCLUDE_DIRS}
${LIBXT_INCLUDE_DIRS}
${LIBXEXT_INCLUDE_DIRS}
 )

# create excutable file target octagon
add_executable( ${target} octagon.c )

# specify libraly 
target_link_libraries(  ${target} 
${LIBXPM_LIBRARIES}
${LIBXT_LIBRARIES}
${LIBXEXT_LIBRARIES}
)

# specify libraly path
target_link_directories( ${target} BEFORE PUBLIC
${LIBXPM_LIBRARY_DIRS} 
${LIBXT_LIBRARY_DIRS} 
${LIBXEXT_LIBRARY_DIRS} )
