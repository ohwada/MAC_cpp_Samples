# CMakeLists.txt
# 2022-06-01 K.OHWADA

cmake_minimum_required(VERSION 3.13)
set(target "3dpong")
project( ${target} C)

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
include_directories(${LIBX11_INCLUDE_DIRS} 
${PROJECT_SOURCE_DIR}/src )

# souce files 
file(GLOB files src/*.c )

# create excutable file target 3dpong
add_executable( ${target} ${files} )

# specify libraly 
target_link_libraries(  ${target} 
${LIBX11_LIBRARIES} )

# specify libraly path
target_link_directories( ${target} BEFORE PUBLIC
${LIBX11_LIBRARY_DIRS} )

# custom_target "man"
set(MAN6_PREFIX "/usr/local/share/man/man6")
add_custom_target("man" COMMAND mkdir 
${MAN6_PREFIX} && cp ${PROJECT_SOURCE_DIR}/src/3dpong.6 ${MAN6_PREFIX}/ )
add_custom_target("man_clean" COMMAND rm ${MAN6_PREFIX}/3dpong.6 )

