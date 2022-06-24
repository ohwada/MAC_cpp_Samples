# CMakeLists.txt
# 2022-06-01 K.OHWADA

cmake_minimum_required(VERSION 3.13)
project("brickout" C)

# command option
option(SDL "sound")
message( "SDL: " ${SDL} )

if( ${SDL} )
	set(target "brickout_sound")
	set(CMAKE_C_FLAGS "-DSDL")
else()
	set(target "brickout")
endif()

# load the module to use pkg-config
find_package(PkgConfig)

# search library with pkg-config 
# and name its results "LIBX11"
pkg_check_modules(LIBX11 REQUIRED  x11)
pkg_check_modules(LIBXPM REQUIRED  xpm)

# display search result
message( "include: " ${LIBX11_INCLUDE_DIRS} )
message( "lib path: " ${LIBX11_LIBRARY_DIRS} )
message( "lib: " ${LIBX11_LIBRARIES} )

# specify include path
include_directories(${LIBX11_INCLUDE_DIRS} ${LIBXPM_INCLUDE_DIRS} )

# create excutable file target brickout
add_executable( ${target} brickout.c )

# specify libraly 
target_link_libraries(  ${target} 
${LIBX11_LIBRARIES}
${LIBXPM_LIBRARIES} )

# specify libraly path
target_link_directories( ${target} BEFORE PUBLIC
${LIBX11_LIBRARY_DIRS} 
${LIBXPM_LIBRARY_DIRS} )

if( ${SDL} ) 
	pkg_check_modules(LIBSDL REQUIRED  SDL_mixer)
	include_directories( ${LIBSDL_INCLUDE_DIRS} )
	target_link_libraries(  ${target} ${LIBSDL_LIBRARIES} )
	target_link_directories( ${target} BEFORE PUBLIC
${LIBSDL_LIBRARY_DIRS} )
endif()

